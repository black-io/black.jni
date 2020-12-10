#include <jni.android.view.Surface.h>
#include <android/native_window_jni.h>


namespace Jni
{
inline namespace android
{
inline namespace view
{
	Surface::Surface( jobject object_ref )
		: Black::JniObject{ object_ref }
	{
		AcquireNativeWindow();
	}

	Surface::Surface( const Surface& other )
		: Black::JniObject( other )
	{
		AcquireNativeWindow();
	}

	Surface::Surface( Surface&& other )
		: Black::JniObject( std::move( other ) )
	{
		AcquireNativeWindow();
	}


	const Surface& Surface::operator=( jobject object_ref )
	{
		Black::JniObject::operator=( object_ref );
		AcquireNativeWindow();
		return *this;
	}

	const Surface& Surface::operator=( const Surface& other )
	{
		Black::JniObject::operator=( other );
		AcquireNativeWindow();
		return *this;
	}

	const Surface& Surface::operator=( Surface&& other )
	{
		Black::JniObject::operator=( std::move( other ) );
		AcquireNativeWindow();
		return *this;
	}

	void Surface::AcquireNativeWindow()
	{
		m_window = nullptr;
		CRET( !IsValid() );
		EXPECTS( IsInstanceOf( m_handles->class_handle ) );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		m_window			= ANativeWindow_fromSurface( local_env, GetJniReference() );
		ENSURES( m_window != nullptr );
	}
}
}
}
