#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
inline namespace Objects
{
	/**
		@brief	JNI class handle.

		This type wraps the `jclass` objects. It always store only global references of `jclass` instance.
		It is required hue to the class handle has thread-agnostic design and could be freely stored and moved across the threads.
		To just locally interact with class reference, it would be better not to create the class handle, but only use the given local value of `jclass`.
	*/
	class JniClass final
	{
	// Friendship declarations.
	public:
		// Grant access to `AcquireClassReference` function.
		friend class JniObject;

		// Custom JNI converter for class handles.
		friend Internal::ClassHandleJniConverter GetJniConverter( JniClass );

	// Public static interface.
	public:
		// Produce class handle for given type of object handle.
		template< typename THandle >
		static inline JniClass FromHandleType();

	// Construction and assignment.
	public:
		JniClass()					= default;
		JniClass( const JniClass& )	= default;
		JniClass( JniClass&& )		= default;
		JniClass( std::string_view class_name );
		explicit JniClass( jclass class_ref );


		inline JniClass& operator = ( const JniClass& )					= default;
		inline JniClass& operator = ( JniClass&& )						= default;
		inline JniClass& operator = ( std::string_view class_name )		{ return Black::CopyAndSwap( *this, class_name ); };
		inline JniClass& operator = ( jclass class_ref )				{ return Black::CopyAndSwap( *this, class_ref ); };

	// Public interface.
	public:
		// Invalidate the handle.
		void Invalidate();


		// Get the canonical name of class. Empty string will be returned for invalid class.
		const std::string GetCanonicalName() const;

		// Get the name of class. Empty string will be returned for invalid class.
		const std::string GetName() const;

		// Get the simple name for class. Empty string will be returned for invalid class.
		const std::string GetSimpleName() const;

		// Get the parent class handle, if available.
		JniClass GetParentClass() const;


		// Check the class handle carries valid value.
		inline const bool IsValid() const				{ return m_class_ref != nullptr; };

		// Get the JNI representation of Java class reference.
		inline jclass GetJniReference() const			{ return m_class_ref.get(); };


		inline jclass operator * () const				{ return GetJniReference(); };

		inline explicit operator const bool () const	{ return IsValid(); };
		inline const bool operator ! () const			{ return !IsValid(); };

	// Private interface.
	private:
		// Acquire the reference of class via its name.
		void AcquireClassReference( std::string_view class_name );

		// Acquire the reference of class via reference of its object.
		void AcquireClassReference( jobject object_ref );

	// Private static fields.
	private:
		static constexpr const char* LOG_CHANNEL = "Black/Jni/Class";

	// Private state.
	private:
		std::shared_ptr<_jclass> m_class_ref; // Shared JNI representation of Java class global reference.
	};


	const bool operator == ( const JniClass& left, const JniClass& right );
	const bool operator != ( const JniClass& left, const JniClass& right );
}
}
}
}
