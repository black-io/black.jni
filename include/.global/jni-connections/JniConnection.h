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
		@brief	Implementation of global connection to JVM.

		This service helps to track the local JNI Environment for any low-level thread of process.
		It tracks the presence of local JNI Environment and performs the valid detaching of JVM on thread exit.
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
		// For debugging purposes.
		static inline Black::DebugName GetDebugName() { return "JNI Connection"; };


		// Register the native function handlers for JNI class.
		static const bool RegisterClassNatives( const NativeBindingTable& bindings );

		// Register the native function handlers for list of JNI classes.
		static const bool RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings );


		// Get the thread-local JNI environment.
		static Black::NotNull<JNIEnv*> GetLocalEnvironment();

		// Get the local reference of Java class by given class-path.
		static Black::NotNull<jclass> GetClassReference( std::string_view class_path );

		// Call the `java.lang.Class.getName()`.
		static std::string GetClassName( Black::NotNull<jclass> class_ref );

		// Call the `java.lang.Class.getSimpleName()`.
		static std::string GetSimpleClassName( Black::NotNull<jclass> class_ref );

		// Call the `java.lang.Class.getCanonicalName()`.
		static std::string GetCanonicalClassName( Black::NotNull<jclass> class_ref );

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

	// Private interface.
	private:
		// Perform the internal services initialization.
		const bool InitializeServices();

		// Finalize the internal services.
		const bool FinalizeServices();


		// Initialize the thread-local environment detaching entity.
		const bool InitializeDetachKey();


		// Thread-local JNI environment termination routine.
		static void DetachLocalEnvironment( void* local_environment );

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
