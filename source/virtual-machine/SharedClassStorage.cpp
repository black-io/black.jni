#include <black.jni.h>
#include <android/java.lang.Thread.h>
#include <android/java.lang.ClassLoader.h>


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	static constexpr char LOG_CHANNEL[] = "Black/Jni/ClassStorage";

	const bool SharedClassStorage::Initialize()
	{
		CRETM( !CaptureClassLoader(), false, LOG_CHANNEL, "Failed to capture JNI class loader." );
		CRETM( !AcquireClassInterface(), false, LOG_CHANNEL, "Failed to acquire JNI common class interface." );

		return true;
	}

	const bool SharedClassStorage::Finalize()
	{
		m_get_simple_name_func		= {};
		m_get_name_func				= {};
		m_get_canonical_name_func	= {};
		m_get_super_class_func		= {};
		m_load_class_func			= {};
		m_class_loader				= {};

		EXPECTS_DEBUG( m_storage.empty() );
		return true;
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

		const Black::JniStaticFunction<::Android::Thread> current_thread_func{ thread_class, "currentThread" };
		CRETM( !current_thread_func, false, LOG_CHANNEL, "Failed to locate `Thread Thread::currentThread()` function." );

		const ::Android::Thread current_thread{ current_thread_func.Call() };
		CRETM( !current_thread, false, LOG_CHANNEL, "Failed to get object of current thread." );

		const Black::JniMemberFunction<::Android::ClassLoader> get_class_loader_func{ thread_class, "getContextClassLoader" };
		CRETM( !get_class_loader_func, false, LOG_CHANNEL, "Failed to locate `ClassLoader Thread::getContextClassLoader()` function." );

		m_class_loader = get_class_loader_func.Call( current_thread );
		CRETM( !m_class_loader, false, LOG_CHANNEL, "Failed to get class loader object." );

		return true;
	}

	const bool SharedClassStorage::AcquireClassInterface()
	{
		const Black::JniClass class_handle{ "java/lang/Class" };
		CRETM( !class_handle, false, LOG_CHANNEL, "Failed to locate `java.lang.Class` class." );

		m_get_super_class_func = { class_handle, "getSuperclass" };
		CRETM( !m_get_super_class_func, false, LOG_CHANNEL, "Failed to locate `Class Class::getSuperclass()` function." );

		m_get_canonical_name_func = { class_handle, "getCanonicalName" };
		CRETM( !m_get_canonical_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getCanonicalName()` function." );

		m_get_name_func = { class_handle, "getName" };
		CRETM( !m_get_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getName()` function." );

		m_get_simple_name_func = { class_handle, "getSimpleName" };
		CRETM( !m_get_simple_name_func, false, LOG_CHANNEL, "Failed to locate `String Class::getSimpleName()` function." );

		return true;
	}
}
}
}
}
