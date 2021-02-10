#include <black/jni/handles.h>
#include <black/jni/startup.h>

#include <black/jni/java/lang/Thread.h>
#include <black/jni/java/lang/ClassLoader.h>


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
namespace
{
	static constexpr const char* LOG_CHANNEL = "Black/Jni/ClassRegistry";
}


	std::shared_ptr<_jclass> ClassRegistry::GetClassReference( jobject object_ref )
	{
		CRETD( object_ref == nullptr, {}, LOG_CHANNEL, "Attempt to get JNI class via null object." );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		jclass class_ref	= local_env->GetObjectClass( object_ref );
		CRETW( class_ref == nullptr, {}, LOG_CHANNEL, "Unable to get Java class for object." );

		return GetInstance().MakeGlobalRef( class_ref, local_env );
	}

	std::shared_ptr<_jclass> ClassRegistry::GetClassReference( jclass class_ref )
	{
		CRETD( class_ref == nullptr, {}, LOG_CHANNEL, "Attempt to get reference for null class." );

		return GetInstance().MakeGlobalRef( class_ref, Black::JniConnection::GetLocalEnvironment() );
	}

	std::shared_ptr<_jclass> ClassRegistry::GetClassReference( std::string_view class_name )
	{
		CRETD( class_name.empty(), {}, LOG_CHANNEL, "Attempt to get class reference using null class name." );

		ClassRegistry& registry = GetInstance();

		Black::MutexLock lock{ registry.m_lock };
		auto& weak_class_ref = registry.m_class_storage[ std::string{ class_name } ];
		CRET( !weak_class_ref.expired(), weak_class_ref.lock() );

		// If shared class already lost or never been found, ask JNI to lookup it.
		auto shared_class_ref	= registry.LoadClass( class_name );
		weak_class_ref			= shared_class_ref;

		return shared_class_ref;
	}

	jclass ClassRegistry::GetLocalClassReference( std::string_view class_name )
	{
		CRETD( class_name.empty(), {}, LOG_CHANNEL, "Attempt to get class reference using null class name." );

		ClassRegistry& registry	= GetInstance();
		::JNIEnv* local_env		= Black::JniConnection::GetLocalEnvironment();

		Black::MutexLock lock{ registry.m_lock };
		auto& weak_class_ref = registry.m_class_storage[ std::string{ class_name } ];
		CRET( weak_class_ref.expired(), registry.LoadClass( class_name, local_env ) );

		auto shared_class_ref = weak_class_ref.lock();
		return static_cast<jclass>( local_env->NewLocalRef( shared_class_ref.get() ) );
	}

	std::string ClassRegistry::GetClassName( Black::NotNull<jclass> class_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		std::string name{ GetInstance().m_get_name.Call( class_ref ) };

		std::transform( name.begin(), name.end(), name.begin(), []( char& ch ){ return ( ch == '.' )? '/' : ch; } );
		return name;
	}

	std::string ClassRegistry::GetSimpleClassName( Black::NotNull<jclass> class_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		return GetInstance().m_get_simple_name.Call( class_ref );
	}

	std::string ClassRegistry::GetCanonicalClassName( Black::NotNull<jclass> class_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		return GetInstance().m_get_canonical_name.Call( class_ref );
	}

	JniClass ClassRegistry::GetParentClass( Black::NotNull<jclass> class_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		return GetInstance().m_get_super_class.Call( class_ref );
	}

	ClassRegistry& ClassRegistry::GetInstance()
	{
		return Black::JniSessionStorage::Get<ClassRegistry>();
	}

	void ClassRegistry::DeleteSharedClass( jclass value )
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		CRET( value == nullptr );

		Black::JniConnection::GetLocalEnvironment()->DeleteGlobalRef( value );
	}

	const bool ClassRegistry::Initialize()
	{
		CRETE( !AcquireClassLoader(), false, LOG_CHANNEL, "Failed to acquire JNI class loader." );
		CRETE( !AcquireClassInterface(), false, LOG_CHANNEL, "Failed to acquire JNI common class interface." );

		return true;
	}

	const bool ClassRegistry::Finalize()
	{
		m_get_simple_name		= {};
		m_get_name				= {};
		m_get_canonical_name	= {};
		m_get_super_class		= {};

		m_load_class			= {};
		m_class_loader			= {};

		EXPECTS_DEBUG( m_class_storage.empty() );
		return true;
	}

	const bool ClassRegistry::AcquireClassLoader()
	{
		const Black::JniClass loader_class{ Black::JniClass::FromHandleType<::Jni::ClassLoader>() };
		CRETE( !loader_class, false, LOG_CHANNEL, "Failed to locate `java.lang.ClassLoader` class." );

		m_load_class = { loader_class, "loadClass" };
		CRETE( !m_load_class, false, LOG_CHANNEL, "Failed to locate `Class java.lang.ClassLoader.findClass( String )` function." );

		const Black::JniClass thread_class{ Black::JniClass::FromHandleType<::Jni::Thread>() };
		CRETE( !thread_class, false, LOG_CHANNEL, "Failed to locate `java.lang.Thread` class." );

		const Black::JniStaticFunction<::Jni::Thread ()> current_thread_func{ thread_class, "currentThread" };
		CRETE( !current_thread_func, false, LOG_CHANNEL, "Failed to locate `Thread java.lang.Thread.currentThread()` function." );

		const ::Jni::Thread current_thread{ current_thread_func.Call() };
		CRETE( !current_thread, false, LOG_CHANNEL, "Failed to get object of current thread." );

		const Black::JniMemberFunction<::Jni::ClassLoader ()> get_class_loader_func{ thread_class, "getContextClassLoader" };
		CRETE( !get_class_loader_func, false, LOG_CHANNEL, "Failed to locate `ClassLoader java.lang.Thread.getContextClassLoader()` function." );

		m_class_loader = get_class_loader_func.Call( current_thread );
		CRETE( !m_class_loader, false, LOG_CHANNEL, "Failed to get class loader object." );

		return true;
	}

	const bool ClassRegistry::AcquireClassInterface()
	{
		const Black::JniClass class_handle{ "java/lang/Class" };
		CRETE( !class_handle, false, LOG_CHANNEL, "Failed to locate `java.lang.Class` class." );

		m_get_super_class = { class_handle, "getSuperclass" };
		CRETE( !m_get_super_class, false, LOG_CHANNEL, "Failed to locate `Class java.lang.Class.getSuperclass()` function." );

		m_get_canonical_name = { class_handle, "getCanonicalName" };
		CRETE( !m_get_canonical_name, false, LOG_CHANNEL, "Failed to locate `String java.lang.Class.getCanonicalName()` function." );

		m_get_name = { class_handle, "getName" };
		CRETE( !m_get_name, false, LOG_CHANNEL, "Failed to locate `String java.lang.Class.getName()` function." );

		m_get_simple_name = { class_handle, "getSimpleName" };
		CRETE( !m_get_simple_name, false, LOG_CHANNEL, "Failed to locate `String java.lang.Class.getSimpleName()` function." );

		return true;
	}

	std::shared_ptr<_jclass> ClassRegistry::MakeGlobalRef( Black::NotNull<jclass> local_ref, JNIEnv* local_env )
	{
		EXPECTS_DEBUG( local_ref != nullptr );
		return { static_cast<jclass>( local_env->NewGlobalRef( local_ref ) ), ClassRegistry::DeleteSharedClass };
	}

	std::shared_ptr<_jclass> ClassRegistry::LoadClass( std::string_view class_name )
	{
		JNIEnv* local_env = Black::JniConnection::GetLocalEnvironment();

		jclass local_class_ref = LoadClass( class_name, local_env );
		CRET( local_class_ref == nullptr, {} );

		return MakeGlobalRef( local_class_ref, local_env );
	}

	jclass ClassRegistry::LoadClass( std::string_view class_name, JNIEnv* local_env )
	{
		jclass local_class_ref = nullptr;

		if( Black::JniConnection::IsMainThread() )
		{
			local_class_ref = LoadClassFromMainThread( class_name, local_env );
		}
		else
		{
			local_class_ref = LoadClassUsingClassLoader( class_name, local_env );
		}

		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
			local_env->ExceptionClear();
			local_class_ref = nullptr;
		}

		CRETW( local_class_ref == nullptr, {}, LOG_CHANNEL, "No class was found with name `{}`.", class_name );
		return local_class_ref;
	}

	jclass ClassRegistry::LoadClassFromMainThread( std::string_view class_name, JNIEnv* local_env )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsMainThread() );

		char* name_buffer = static_cast<char*>( alloca( class_name.length() + 1 ) );
		Black::CopyMemory( name_buffer, class_name.data(), class_name.length() );
		name_buffer[ class_name.length() ] = 0;

		// For the main thread we may use `FindClass` function from `JNIEnv` object.
		return local_env->FindClass( name_buffer );
	}

	jclass ClassRegistry::LoadClassUsingClassLoader( std::string_view class_name, JNIEnv* local_env )
	{
		// Since JNI can't return class reference from native threads,
		// according to next article the best way is using the cached `ClassLoader` instance.
		// https://developer.android.com/training/articles/perf-jni.html#faq_FindClass

		// The name of class must be converted into Java-style package name.
		char* name_buffer = static_cast<char*>( alloca( class_name.length() ) );
		std::transform( class_name.begin(), class_name.end(), name_buffer, []( const char symbol ) { return ( symbol == '.' )? '/' : symbol; } );

		std::string_view jni_class_name{ name_buffer, class_name.length() };

		// For any other thread only captured `ClassLoader` instance may be used.
		return static_cast<jclass>(
			local_env->CallObjectMethod( *m_class_loader, *m_load_class, Black::ConvertToJni( jni_class_name ) )
		);
	}
}
}
}
}
