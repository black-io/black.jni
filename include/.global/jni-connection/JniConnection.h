#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace JniConnections
{
	/**
		@brief	Global connection to topside virtual machine.
		This class is the most major and most crucial part of interaction with JNI.
	*/
	class JniConnection final : private Black::NonTransferable
	{
	// Friendship declarations.
	public:
		// Grant access to internal state for purposes of initialization and finalization.
		friend class Internal::JniConnectionInitializer;

	// Public inner types.
	public:
		// Binding table for object native interfaces.
		using NativeBindingTable = Internal::NativeBindingTable;

	// Public static interface.
	public:
		// Register the native function handlers for JNI class.
		static const bool RegisterClassNatives( const NativeBindingTable& bindings );

		// Register the native function handlers for list of JNI classes.
		static const bool RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings );


		// Get the thread-local JNI environment.
		static Black::NotNull<JNIEnv*> GetLocalEnvironment();


		// Check that the current thread is the main (for JNI connection) one.
		static const bool IsMainThread();

		// Check that the connection is properly initialized.
		static inline const bool IsValid()		{ return GetConnection() != nullptr; };

		// Get the connection to virtual machine.
		static inline JavaVM* GetConnection()	{ return GetInstance().m_connection; };

	// Private static interface.
	private:
		// Get the global instance of connection.
		static JniConnection& GetInstance();

	// Private construction.
	private:
		JniConnection() = default;

	// Private interface.
	private:
		// Thread-local JNI environment termination routine.
		static void DetachLocalEnvironment( void* local_environment );


		// Initialize the thread-local environment detaching entity.
		const bool InitEnvironmentDetacher();

		// Acquire the helper functions for JNI class handle.
		const bool AcquireClassInterface();

		// Acquire the helper functions for JNI object handle.
		const bool AcquireObjctInterface();

	// Private state.
	private:
		JavaVM*	m_connection		= nullptr;	// Current connection to virtual machine.
		JNIEnv*	m_main_environment	= nullptr;	// Thread-local environment for main thread.
		int64_t	m_main_thread_id	= 0;		// Id of main thread.
		int64_t	m_thread_detach_key	= 0;		// Thread-local environment detach key.
	};
}
}
}
}
