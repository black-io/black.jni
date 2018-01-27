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
		friend class Black::Jni::Handles::JniClass;	// Intensively uses `m_stored_classes`.

	// Public interface.
	public:
		// Initialize the JNI connection. Expected to be used only at `JNI_OnLoad` function.
		static const bool Initialize( JavaVM* connection );

		// Finalize the JNI connection. Expected to be used only at `JNI_OnUnload` function.
		static const bool Finalize();


		// Register the native function handlers for JNI class.
		static const bool RegisterClassNatives( const Black::NativeBindingTable& bindings );

		// Register the native function handlers for list of JNI classes.
		static const bool RegisterClassNatives( std::initializer_list<Black::NativeBindingTable> bindings );


		// Get the thread-local JNI environment.
		static JNIEnv* GetLocalEnvironment();


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


		JniConnection() = default;


		// Retrieve the instance of class loader.
		const bool CaptureClassLoader();

	// Private state.
	private:
		JavaVM*						m_connection		= nullptr;	// Current connection to virtual machine.
		JNIEnv*						m_main_env			= nullptr;	// Thread-local environment for main thread.
		int64_t						m_main_thread_id	= 0;		// Id of main thread.
		int64_t						m_thread_detach_key	= 0;		// Thread-local environment detach key.

		Traits::SharedClassStorage	m_stored_classes;				// Storage for shared classes.

	// Persistently cached handles.
	private:
		Black::JniObject										m_class_loader;				// Instance of `java.lang.ClassLoader`.

		Black::JniMemberFunction<Black::JniClass, std::string>	m_load_class_func;			// `java.lang.Class java.lang.ClassLoader.loadClass( java.lang.String )`

		Black::JniMemberFunction<Black::JniClass>				m_get_super_class_func;		// `java.lang.Class java.lang.Class.getSuperClass()`
		Black::JniMemberFunction<std::string>					m_get_canonical_name_func;	// `java.lang.String java.lang.Class.getCanonicalName()`
		Black::JniMemberFunction<std::string>					m_get_name_func;			// `java.lang.String java.lang.Class.getName()`
		Black::JniMemberFunction<std::string>					m_get_simple_name_func;		// `java.lang.String java.lang.Class.getSimpleName()`

	// Persistent cache.
	private:
		Traits::SharedStateCache	m_cached_states;	// Cache for shared states.
	};
}
}
}
