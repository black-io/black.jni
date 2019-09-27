#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
	/**
		@brief	Storage for shared JNI class instances.
	*/
	class SharedClassStorage final : private Black::NonTransferable
	{
	// Public interface.
	public:
		// Init the storage.
		const bool Initialize();

		// Finalize.
		const bool Finalize();


		// Get the class reference for JNI object by given JNI reference.
		std::shared_ptr<_jclass> GetClassReference( jobject object_ref );

		// Get the shared global reference for JNI class using another reference.
		std::shared_ptr<_jclass> GetClassReference( jclass class_ref );

		// Get the class reference by its name.
		std::shared_ptr<_jclass> GetClassReference( Black::StringView class_name );


		// Get the synchronization mutex for storage.
		inline const Black::Mutex& GetMutex() const		{ return m_latch; };

	// Private interface.
	private:
		// Shared class deletion routine.
		static void DeleteSharedClass( jclass value );


		// Capture the global handle to JNI class loader.
		const bool CaptureClassLoader();


		// Create shared global reference to JNI class from local one.
		std::shared_ptr<_jclass> MakeGlobalRef( Black::NotNull<jclass> local_ref, JNIEnv* local_env );

		// Load the JNI class by given class name.
		std::shared_ptr<_jclass> LoadClass( Black::StringView class_name );

	// Private state.
	private:
		using Storage = std::unordered_map<std::string, std::weak_ptr<_jclass>>;

		Black::CriticalSection	m_latch;
		Storage					m_storage;

	// Persistently cached handles.
	private:
		Black::JniObject										m_class_loader;		// Instance of `java.lang.ClassLoader`.

		Black::JniMemberFunction<Black::JniClass, std::string>	m_load_class_func;	// `java.lang.Class java.lang.ClassLoader.loadClass( java.lang.String )`
	};
}
}
}
}
