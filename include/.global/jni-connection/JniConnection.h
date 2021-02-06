#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	/**
		@brief	Global connection to topside virtual machine.
		This class is the most major and most crucial part of interaction with JNI.
	*/
	class JniConnection final : private Black::NonTransferable
	{
	// Friendship declarations.
	public:
		// Intensively uses `m_stored_classes`.
		friend class Black::Jni::Handles::JniClass;

		// Uses the object synchronization functions.
		friend class Black::Jni::Handles::JniObject;

		// Instant access to `GetSharedStateStorage` function.
		template< typename TState, bool IS_PERSISTENT >
		friend class Black::Jni::Handles::Internal::SharedState;

	// Public inner types.
	public:
		// Binding table for object native interfaces.
		using NativeBindingTable	= Internal::NativeBindingTable;

	// Public static interface.
	public:
		// Initialize the JNI connection. Expected to be used only at `JNI_OnLoad` function.
		static const bool Initialize( Black::NotNull<JavaVM*> jvm );

		// Finalize the JNI connection. Expected to be used only at `JNI_OnUnload` function.
		static const bool Finalize();


		// Register the native function handlers for JNI class.
		static const bool RegisterClassNatives( const NativeBindingTable& bindings );

		// Register the native function handlers for list of JNI classes.
		static const bool RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings );

		// Build the information record for given native function.
		template< auto FUNCTION >
		static inline ::JNINativeMethod BuildNativeFunctionInfo( Black::NotNull<const char*> function_name );


		// Get the thread-local JNI environment.
		static Black::NotNull<JNIEnv*> GetLocalEnvironment();


		// Check that the current thread is the main (for JNI connection) one.
		static const bool IsMainThread();

		// Check that the connection is properly initialized.
		static inline const bool IsValid()		{ return GetConnection() != nullptr; };

		// Get the connection to virtual machine.
		static inline JavaVM* GetConnection()	{ return GetInstance().m_connection; };

	// Private interface.
	private:
		// Get the global instance of connection.
		static JniConnection& GetInstance();


		// Thread-local JNI environment termination routine.
		static void DetachLocalEnv( void* local_env );


		// Call the `java.lang.Class.getName()`.
		static std::string GetClassName( const Black::JniClass& class_handle );

		// Call the `java.lang.Class.getSimpleName()`.
		static std::string GetSimpleClassName( const Black::JniClass& class_handle );

		// Call the `java.lang.Class.getCanonicalName()`.
		static std::string GetCanonicalClassName( const Black::JniClass& class_handle );

		// Call the `java.lang.Class.getSuperClass()`.
		static JniClass GetParentClass( const Black::JniClass& class_handle );


		// Call the `java.lang.Object.notify()`.
		static void NotifyFromObject( const Black::JniObject& object_handle );

		// Call the `java.lang.Object.notifyAll()`.
		static void NotifyAllFromObject( const Black::JniObject& object_handle );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( const Black::JniObject& object_handle );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( const Black::JniObject& object_handle, const int64_t milliseconds );

		// Call the `java.lang.Object.notifyAll()`.
		static void WaitFromObject( const Black::JniObject& object_handle, const int64_t milliseconds, const int32_t nanoseconds );


		// Short path to get the storage for shared classes.
		static inline Internal::SharedClassStorage& GetClassStorage()		{ return GetInstance().m_stored_classes; };

		// Short path to get the storage for shared states.
		static inline Internal::SharedStateCache& GetSharedStateStorage()	{ return GetInstance().m_cached_states; };


		JniConnection() = default;


		// Initialize the thread-local environment detaching entity.
		const bool InitEnvDetacher();

		// Acquire the helper functions for JNI class handle.
		const bool AcquireClassInterface();

		// Acquire the helper functions for JNI object handle.
		const bool AcquireObjctInterface();

	// Private state.
	private:
		JavaVM*						m_connection		= nullptr;	// Current connection to virtual machine.
		JNIEnv*						m_main_env			= nullptr;	// Thread-local environment for main thread.
		int64_t						m_main_thread_id	= 0;		// Id of main thread.
		int64_t						m_thread_detach_key	= 0;		// Thread-local environment detach key.

		Internal::SharedClassStorage	m_stored_classes;				// Storage for shared classes.

	// Persistently captured JNI entities.
	private:
		Black::JniMemberFunction<Black::JniClass>			m_get_super_class_func;		// `java.lang.Class java.lang.Class.getSuperClass()`
		Black::JniMemberFunction<std::string>				m_get_canonical_name_func;	// `java.lang.String java.lang.Class.getCanonicalName()`
		Black::JniMemberFunction<std::string>				m_get_name_func;			// `java.lang.String java.lang.Class.getName()`
		Black::JniMemberFunction<std::string>				m_get_simple_name_func;		// `java.lang.String java.lang.Class.getSimpleName()`
		Black::JniMemberFunction<void>						m_notify_func;				// `java.lang.Object.notify()`
		Black::JniMemberFunction<void>						m_notify_all_func;			// `java.lang.Object.notifyAll()`
		Black::JniMemberFunction<void>						m_wait_func;				// `java.lang.Object.wait()`
		Black::JniMemberFunction<void, int64_t>				m_wait_msec_func;			// `java.lang.Object.wait(long millis)`
		Black::JniMemberFunction<void, int64_t, int32_t>	m_wait_msec_nsec_func;		// `java.lang.Object.wait(long millis, int nanos)`

	// Persistent cache.
	private:
		Internal::SharedStateCache	m_cached_states;	// Cache for shared states.
	};
}
}
}
