#include <black/jni/handles.h>
#include <black/jni/startup.h>


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


	void ObjectStateRegistry::NotifyFromObject( Black::NotNull<jobject> object_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		GetInstance().m_notify.Call( object_ref );
	}

	void ObjectStateRegistry::NotifyAllFromObject( Black::NotNull<jobject> object_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		GetInstance().m_notify_all.Call( object_ref );
	}

	void ObjectStateRegistry::WaitFromObject( Black::NotNull<jobject> object_ref )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		GetInstance().m_wait.Call( object_ref );
	}

	void ObjectStateRegistry::WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		GetInstance().m_wait_msec.Call( object_ref, milliseconds );
	}

	void ObjectStateRegistry::WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds, const int32_t nanoseconds )
	{
		EXPECTS_DEBUG( Black::JniConnection::IsValid() );

		GetInstance().m_wait_msec_nsec.Call( object_ref, milliseconds, nanoseconds );
	}

	ObjectStateRegistry& ObjectStateRegistry::GetInstance()
	{
		return Black::JniSessionStorage::Get<ObjectStateRegistry>();
	}

	const bool ObjectStateRegistry::Initialize()
	{
		CRETE( !AcquireObjctInterface(), false, LOG_CHANNEL, "Failed to acquire the common JNI object functions." );

		return true;
	}

	template< Black::BuildMode >
	void ObjectStateRegistry::EnsureStorageReleased()
	{
		auto storage_check = []( const StateStorage::value_type& buffer_slot ) -> bool
		{
			return !buffer_slot.second->IsAllocated();
		};

		EXPECTS( std::all_of( m_storage.begin(), m_storage.end(), storage_check ) );
	}

	template<>
	void ObjectStateRegistry::EnsureStorageReleased<Black::BuildMode::Release>()
	{
		// In release configuration such checks not needed.
	}

	const bool ObjectStateRegistry::Finalize()
	{
		m_wait_msec_nsec	= {};
		m_wait_msec			= {};
		m_wait				= {};
		m_notify_all		= {};
		m_notify			= {};

		EnsureStorageReleased<Black::BUILD_CONFIGURATION>();
		return true;
	}

	const bool ObjectStateRegistry::AcquireObjctInterface()
	{
		const Black::JniClass class_handle{ "java/lang/Object" };
		CRETE( !class_handle, false, LOG_CHANNEL, "Failed to locate `java.lang.Object` class." );

		m_notify = { class_handle, "notify" };
		CRETE( !m_notify, false, LOG_CHANNEL, "Failed to locate `void Object::notify()` function." );

		m_notify_all = { class_handle, "notifyAll" };
		CRETE( !m_notify_all, false, LOG_CHANNEL, "Failed to locate `void Object::notifyAll()` function." );

		m_wait = { class_handle, "wait" };
		CRETE( !m_wait, false, LOG_CHANNEL, "Failed to locate `void Object::wait()` function." );

		m_wait_msec = { class_handle, "wait" };
		CRETE( !m_wait_msec, false, LOG_CHANNEL, "Failed to locate `void Object::wait( long millis )` function." );

		m_wait_msec_nsec = { class_handle, "wait" };
		CRETE( !m_wait_msec_nsec, false, LOG_CHANNEL, "Failed to locate `void Object::wait( long millis, int nanos )` function." );

		return true;
	}
}
}
}
}
