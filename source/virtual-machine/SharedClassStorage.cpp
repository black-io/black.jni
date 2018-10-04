#include <black.jni.h>
#include <jni.java.lang.Thread.h>
#include <jni.java.lang.ClassLoader.h>


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
namespace
{
	static constexpr const char* LOG_CHANNEL = "Black/Jni/ClassStorage";
}


	const bool SharedClassStorage::Initialize()
	{
		CRETM( !CaptureClassLoader(), false, LOG_CHANNEL, "Failed to capture JNI class loader." );

		return true;
	}

	const bool SharedClassStorage::Finalize()
	{
		m_load_class_func			= {};
		m_class_loader				= {};

		EXPECTS_DEBUG( m_storage.empty() );
		return true;
	}

	std::shared_ptr<_jclass> SharedClassStorage::GetClassReference( jobject object_ref )
	{
		CRETD( object_ref == nullptr, {}, LOG_CHANNEL, "Attempt to get JNI class via null object." );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		jclass class_ref	= local_env->GetObjectClass( object_ref );
		CRETW( class_ref == nullptr, {}, LOG_CHANNEL, "Unable to get Java class for object." );

		return MakeGlobalRef( class_ref, local_env );
	}

	std::shared_ptr<_jclass> SharedClassStorage::GetClassReference( jclass class_ref )
	{
		CRETD( class_ref == nullptr, {}, LOG_CHANNEL, "Attempt to get reference for null class." );

		return MakeGlobalRef( class_ref, Black::JniConnection::GetLocalEnvironment() );
	}

	std::shared_ptr<_jclass> SharedClassStorage::GetClassReference( Black::StringView class_name )
	{
		CRETD( class_name.empty(), {}, LOG_CHANNEL, "Attempt to get class reference using null class name." );

		Black::MutexLock lock{ m_latch };
		auto& weak_class_ref = m_storage[ class_name.data() ];
		CRET( !weak_class_ref.expired(), weak_class_ref.lock() );

		// If shared class already lost or never been found, ask JNI to lookup it.
		auto shared_class_ref	= LoadClass( class_name );
		weak_class_ref			= shared_class_ref;

		return shared_class_ref;
	}

	void SharedClassStorage::DeleteSharedClass( jclass value )
	{
		CRETD( !Black::JniConnection::IsValid(), , LOG_CHANNEL, "{}:{} - Attempt to use invalid JNI connection.", __func__, __LINE__ );
		CRET( value == nullptr );

		Black::JniConnection::GetLocalEnvironment()->DeleteGlobalRef( value );
	}

	const bool SharedClassStorage::CaptureClassLoader()
	{
		const Black::JniClass loader_class{ "java/lang/ClassLoader" };
		CRETM( !loader_class, false, LOG_CHANNEL, "Failed to locate `java.lang.ClassLoader` class." );

		m_load_class_func = { loader_class, "loadClass" };
		CRETM( !m_load_class_func, false, LOG_CHANNEL, "Failed to locate `Class ClassLoader::findClass( String )` function." );

		const Black::JniClass thread_class{ "java/lang/Thread" };
		CRETM( !thread_class, false, LOG_CHANNEL, "Failed to locate `java.lang.Thread` class." );

		const Black::JniStaticFunction<::Jni::Thread> current_thread_func{ thread_class, "currentThread" };
		CRETM( !current_thread_func, false, LOG_CHANNEL, "Failed to locate `Thread Thread::currentThread()` function." );

		const ::Jni::Thread current_thread{ current_thread_func.Call() };
		CRETM( !current_thread, false, LOG_CHANNEL, "Failed to get object of current thread." );

		const Black::JniMemberFunction<::Jni::ClassLoader> get_class_loader_func{ thread_class, "getContextClassLoader" };
		CRETM( !get_class_loader_func, false, LOG_CHANNEL, "Failed to locate `ClassLoader Thread::getContextClassLoader()` function." );

		m_class_loader = get_class_loader_func.Call( current_thread );
		CRETM( !m_class_loader, false, LOG_CHANNEL, "Failed to get class loader object." );

		return true;
	}

	std::shared_ptr<_jclass> SharedClassStorage::MakeGlobalRef( Black::NotNull<_jclass> local_ref, JNIEnv* local_env )
	{
		EXPECTS_DEBUG( local_ref != nullptr );
		return { reinterpret_cast<jclass>( local_env->NewGlobalRef( local_ref ) ), SharedClassStorage::DeleteSharedClass };
	}

	std::shared_ptr<_jclass> SharedClassStorage::LoadClass( Black::StringView class_name )
	{
		JNIEnv* local_env		= Black::JniConnection::GetLocalEnvironment();
		jclass local_class_ref	= nullptr;

		if( Black::JniConnection::IsMainThread() )
		{
			// For the main thread we may use `FindClass` function from `JNIEnv` object.
			local_class_ref = local_env->FindClass( class_name.data() );
		}
		else
		{
			// Since JNI can't return class reference from native threads,
			// according to next article the best way is using the cached `ClassLoader` instance.
			// https://developer.android.com/training/articles/perf-jni.html#faq_FindClass

			// The name of class must be converted into Java-style package name.
			std::string jni_class_name{ class_name.data() };
			for( auto& item : jni_class_name )
			{
				if( item == '/' )
				{
					item = '.';
				}
			}

			// For any other thread only captured `ClassLoader` instance may be used.
			local_class_ref = reinterpret_cast<jclass>(
				local_env->CallObjectMethod( *m_class_loader, *m_load_class_func, Black::ToJni( jni_class_name ) )
			);
		}

		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			BLACK_NON_RELEASE_CODE( local_env->ExceptionDescribe() );
			local_env->ExceptionClear();
			local_class_ref = nullptr;
		}

		CRETW( local_class_ref == nullptr, {}, LOG_CHANNEL, "No class was found with name `{}`.", class_name.data() );
		return MakeGlobalRef( local_class_ref, local_env );
	}
}
}
}
}
