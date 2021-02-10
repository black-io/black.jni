#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	/**
		@breif	Registry for JNI object states.

		This registry implements the `Lightweight` pattern for any type derived from `JniObject`.
		The registry implements the management of state buffers and guaranties that there only one instance of each required state in runtime.
	*/
	class ObjectStateRegistry final : private Black::NonTransferable
	{
	// Friendship declarations.
	public:
		// Grant access to initialization and finalization.
		friend class Black::JniConnection;

	// Public static interface.
	public:
		// Call the `java.lang.Object.notify()`.
		static void NotifyFromObject( Black::NotNull<jobject> object_ref );

		// Call the `java.lang.Object.notifyAll()`.
		static void NotifyAllFromObject( Black::NotNull<jobject> object_ref );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( Black::NotNull<jobject> object_ref );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( Black::NotNull<jobject> object_ref, const int64_t milliseconds, const int32_t nanoseconds );


		// Get the cached storage for shared state.
		template< typename TState >
		static inline ObjectStateBuffer<TState>* GetStateBuffer();


		// Get the synchronization mutex for storage.
		static inline const Black::Mutex& GetMutex() { return GetInstance().m_lock; };

	// Private inner types.
	private:
		// Storage for object state instances.
		using StateStorage = std::unordered_map<std::type_index, std::unique_ptr<ObjectStateInterface>>;

	// Private static interface.
	private:
		// Get the global instance of connection.
		static ObjectStateRegistry& GetInstance();

	// Private interface.
	private:
		// Initialize the registry.
		const bool Initialize();

		// Perform the finalization.
		const bool Finalize();


		// Acquire the helper functions for JNI object handle.
		const bool AcquireObjctInterface();


		// Ensure there all buffers released already.
		template< Black::BuildMode >
		void EnsureStorageReleased();

	// Private state.
	private:
		Black::SpinLock	m_lock;				// Storage synchronization lock.
		StateStorage	m_storage;			// Permanent storage for object states.

	// Persistently cached handles.
	private:
		Black::JniMemberFunction<void ()>					m_notify;			// `java.lang.Object.notify()`
		Black::JniMemberFunction<void ()>					m_notify_all;		// `java.lang.Object.notifyAll()`
		Black::JniMemberFunction<void ()>					m_wait;				// `java.lang.Object.wait()`
		Black::JniMemberFunction<void ( int64_t )>			m_wait_msec;		// `java.lang.Object.wait(long millis)`
		Black::JniMemberFunction<void ( int64_t, int32_t )>	m_wait_msec_nsec;	// `java.lang.Object.wait(long millis, int nanos)`
	};
}
}
}
}
