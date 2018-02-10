#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
	// Handle to JNI class.
	class JniClass final
	{
		friend class Black::Jni::Handles::JniObject;	// Grant access to `AcquireClassReference` function.

	// Construction and assignment.
	public:
		JniClass()														= default;
		JniClass( const JniClass& other )								= default;
		JniClass( JniClass&& other )									= default;
		JniClass( Black::StringView class_name );


		inline JniClass& operator = ( const JniClass& other )			= default;
		inline JniClass& operator = ( JniClass&& other )				= default;
		inline JniClass& operator = ( Black::StringView class_name )	{ return Black::CopyAndSwap( *this, class_name ); };
		JniClass& operator = ( jclass class_ref );

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


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jclass operator * () const				{ return GetJniReference(); };

	// Private interface.
	private:
		// Acquire the reference of class via its name.
		void AcquireClassReference( Black::StringView class_name );

		// Acquire the reference of class via reference of its object.
		void AcquireClassReference( jobject object_ref );

	private:
		std::shared_ptr<_jclass>	m_class_ref;	// Shared JNI representation of Java class global reference.
	};


	const bool operator == ( const JniClass& left, const JniClass& right );
	const bool operator != ( const JniClass& left, const JniClass& right );
}
}
}
