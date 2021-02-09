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
		@brief	Class registry.

		This registry manages the shared `jclass` references. It is crucial for Java side and C++ performance to share the global class references.
	*/
	class ClassRegistry final : private Black::NonTransferable
	{
	// Friendship declarations.
	public:
		// Grant access to initialization and finalization.
		friend class Black::JniConnection;

	// Public static interface.
	public:
		// Get the class reference for JNI object by given JNI reference.
		static std::shared_ptr<_jclass> GetClassReference( jobject object_ref );

		// Get the shared global reference for JNI class using another reference.
		static std::shared_ptr<_jclass> GetClassReference( jclass class_ref );

		// Get the class reference by its name.
		static std::shared_ptr<_jclass> GetClassReference( std::string_view class_name );

		// Get the class reference by its name.
		static jclass GetLocalClassReference( std::string_view class_name );


		// Call the `java.lang.Class.getName()`.
		static std::string GetClassName( Black::NotNull<jclass> class_ref );

		// Call the `java.lang.Class.getSimpleName()`.
		static std::string GetSimpleClassName( Black::NotNull<jclass> class_ref );

		// Call the `java.lang.Class.getCanonicalName()`.
		static std::string GetCanonicalClassName( Black::NotNull<jclass> class_ref );

		// Call the `java.lang.Class.getSuperClass()`.
		static JniClass GetParentClass( Black::NotNull<jclass> class_ref );


		// Get the synchronization mutex for storage.
		static inline const Black::Mutex& GetMutex() { return GetInstance().m_lock; };

	// Private inner types.
	private:
		// Stored global `jclass` references.
		using SharedClassMap = std::unordered_map<std::string, std::weak_ptr<_jclass>>;

	// Private static interface.
	private:
		// Get the global instance of connection.
		static ClassRegistry& GetInstance();


		// Shared class deletion routine.
		static void DeleteSharedClass( jclass value );

	// Private interface.
	private:
		// Initialize the registry.
		const bool Initialize();

		// Perform the finalization.
		const bool Finalize();


		// Capture the global handle to JNI class loader.
		const bool AcquireClassLoader();

		// Acquire the helper functions for JNI class handle.
		const bool AcquireClassInterface();


		// Create shared global reference to JNI class from local one.
		std::shared_ptr<_jclass> MakeGlobalRef( Black::NotNull<jclass> local_ref, JNIEnv* local_env );

		// Load the JNI class by given class name.
		std::shared_ptr<_jclass> LoadClass( std::string_view class_name );

		// Load the JNI class by given class name.
		jclass LoadClass( std::string_view class_name, JNIEnv* local_env );

		// Returns local reference. Perform the loading of class from main JNI thread.
		jclass LoadClassFromMainThread( std::string_view class_name, JNIEnv* local_env );

		// Returns local reference. Perform the loading of class by means of class loader instance.
		jclass LoadClassUsingClassLoader( std::string_view class_name, JNIEnv* local_env );

	// Private state.
	private:
		Black::SpinLock	m_lock;				// Storage synchronization lock.
		SharedClassMap	m_class_storage;	// Storage for referenced classes.

	// Persistently cached handles.
	private:
		Black::JniMemberFunction<Black::JniClass ()>	m_get_super_class;		// `java.lang.Class java.lang.Class.getSuperClass()`
		Black::JniMemberFunction<std::string ()>		m_get_canonical_name;	// `java.lang.String java.lang.Class.getCanonicalName()`
		Black::JniMemberFunction<std::string ()>		m_get_name;				// `java.lang.String java.lang.Class.getName()`
		Black::JniMemberFunction<std::string ()>		m_get_simple_name;		// `java.lang.String java.lang.Class.getSimpleName()`

		Black::JniObject											m_class_loader;	// Instance of `java.lang.ClassLoader`.
		Black::JniMemberFunction<Black::JniClass ( std::string )>	m_load_class;	// `java.lang.Class java.lang.ClassLoader.loadClass( java.lang.String )`
	};
}
}
}
}
