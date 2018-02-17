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


		JniObject()									= default;
		JniObject( const JniObject& other )			= default;
		JniObject( JniObject&& other )				= default;
		JniObject( const JniClass& class_handle );
		JniObject( JniClass&& class_handle );
		explicit JniObject( jobject object_ref );


		inline JniObject& operator = ( const JniObject& other )			= default;
		inline JniObject& operator = ( JniObject&& other )				= default;
		inline JniObject& operator = ( jobject object_ref )				{ return Black::CopyAndSwap( *this, object_ref ); };
		inline JniObject& operator = ( const JniClass& class_handle )	{ return Black::CopyAndSwap( *this, class_handle ); };
		inline JniObject& operator = ( JniClass&& class_handle )		{ return Black::CopyAndSwap( *this, std::move( class_handle ) ); };

	// Public interface.
	public:
		// Invalidate the handle.
		void Invalidate();


		// Check that the object is instance of given class.
		const bool IsInstanceOf( const JniClass& base_class ) const;

		// Check the object handle carries valid value.
		inline const bool IsValid() const					{ return m_object_ref != nullptr; };

		// Get the handle to class of stored object.
		inline const JniClass& GetClass() const				{ EnsureClassHandle(); return m_class_handle; };

		// Get the JNI representation of Java object reference.
		inline jobject GetJniReference() const				{ return m_object_ref.get(); };


		inline explicit operator const bool () const		{ return IsValid(); };
		inline jobject operator * () const					{ return GetJniReference(); };

	// Private interface.
	private:
		// Delete the object reference.
		static void DeleteObjectRef( jobject object_ref );


		// Lazy initialization of `m_class_handle`.
		void EnsureClassHandle() const;

		// Acquire the global ref to object.
		void AcquireObjectRef( jobject object_ref );

	private:
		static constexpr const char*	LOG_CHANNEL	= "Black/Jni/Object";

		std::shared_ptr<_jobject>	m_object_ref;	// Shared JNI representation of Java object global reference.
		mutable JniClass			m_class_handle;	// Handle to class of stored object.
	};


	inline const bool operator == ( const JniObject& left, const JniObject& right );
	inline const bool operator != ( const JniObject& left, const JniObject& right );
}
}
}
