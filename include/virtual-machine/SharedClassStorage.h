#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
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


		// Get the synchronization mutex for storage.
		inline const Black::Mutex& GetMutex() const		{ return m_latch; };

	// Private interface.
	private:
		// Shared class deletion routine.
		static void DeleteSharedClass( jclass value );


		//
		const bool CaptureClassLoader();

		//
		const bool AcquireClassInterface();

		//
		std::shared_ptr<_jclass> MakeGlobalRef( Black::NotNull<_jclass> local_ref, JNIEnv* local_env );

		//
		std::shared_ptr<_jclass> LoadClass( Black::StringView class_name );

	// Private state.
	private:
		using Storage = std::unordered_map<std::string, std::weak_ptr<_jclass>>;

		Black::CriticalSection	m_latch;
		Storage					m_storage;

	// Persistently cached handles.
	private:
		Black::JniObject										m_class_loader;				// Instance of `java.lang.ClassLoader`.

		Black::JniMemberFunction<Black::JniClass, std::string>	m_load_class_func;			// `java.lang.Class java.lang.ClassLoader.loadClass( java.lang.String )`

		Black::JniMemberFunction<Black::JniClass>				m_get_super_class_func;		// `java.lang.Class java.lang.Class.getSuperClass()`
		Black::JniMemberFunction<std::string>					m_get_canonical_name_func;	// `java.lang.String java.lang.Class.getCanonicalName()`
		Black::JniMemberFunction<std::string>					m_get_name_func;			// `java.lang.String java.lang.Class.getName()`
		Black::JniMemberFunction<std::string>					m_get_simple_name_func;		// `java.lang.String java.lang.Class.getSimpleName()`
	};
}
}
}
}
