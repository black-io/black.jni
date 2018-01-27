#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Handle of arbitrary Java object.
	class JniObject
	{
	// Construction and assignation.
	public:
		// Usable shared state to optimize the owning of function/field handles.
		template< typename TState, bool IS_PERSISTENT = false >
		using SharedState	= Black::Jni::VirtualMachine::Traits::SharedState<TState, IS_PERSISTENT>;


		// Construct new object of given class and using given construction arguments.
		template< typename... TArguments >
		static JniObject Construct( const JniClass& class_handle, const TArguments&... arguments );


		JniObject() = default;
		JniObject( jobject object_ref );
		JniObject( const JniClass& class_handle );
		JniObject( JniClass&& class_handle );
		JniObject( const JniObject& other );
		JniObject( JniObject&& other );


		const JniObject& operator = ( jobject object_ref );
		const JniObject& operator = ( const JniClass& class_handle );
		const JniObject& operator = ( JniClass&& class_handle );
		const JniObject& operator = ( const JniObject& other );
		const JniObject& operator = ( JniObject&& other );

	// Public interface.
	public:
		// Invalidate the handle.
		void Invalidate();


		// Check that the object is instance of given class.
		const bool IsInstanceOf( const JniClass& base_class ) const;

		// Check the object handle carries valid value.
		inline const bool IsValid() const					{ return m_object_ref != nullptr; };

		// Get the handle to class of stored object.
		inline const JniClass& GetJniClass() const			{ RetrieveClass(); return m_class_handle; };

		// Get the JNI representation of Java object reference.
		inline jobject GetJniReference() const				{ return m_object_ref.get(); };


		inline explicit operator const bool () const		{ return IsValid(); };
		inline jobject operator * () const					{ return GetJniReference(); };

	// Private interface.
	private:
		// Delete the object reference.
		static void DeleteObjectRef( jobject object_ref );


		// Lazy initialization of `m_class_handle`.
		void RetrieveClass() const;

		// Acquire the global ref to object.
		void AcquireObjectRef( jobject object_ref );

	private:
		std::shared_ptr<_jobject>	m_object_ref;	// Shared JNI representation of Java object global reference.
		mutable JniClass			m_class_handle;	// Handle to class of stored object.
	};


	const bool operator == ( const JniObject& left, const JniObject& right );
	const bool operator != ( const JniObject& left, const JniObject& right );
}
}
}
