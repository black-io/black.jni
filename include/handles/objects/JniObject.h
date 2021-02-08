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
		@brief	Common JNI object handle.

		This type implement the basic interface for all other object handles.
		Every handle to object of Java class should be derived from this type. It simplifies a lot the design of such handle.

		Each derived type should provide its own custom JNI converter through the valid declaration of `GetJniConverter` function.
		It may be easily done by means of `JniConverter` template.
	*/
	class JniObject : public Black::Mutex
	{
	// Friendship declarations.
	public:
		// Custom JNI converter for object handles.
		friend Internal::ObjectHandleJniConverter GetJniConverter( JniObject );

	// Public inner types.
	public:
		// Usable shared state to optimize the owning of function/field handles.
		template< typename TState, bool IS_PERSISTENT = false >
		using SharedState = Internal::SharedState<TState, IS_PERSISTENT>;

		// Custom JNI converter template for every derived type.
		template< typename TObjectHandle >
		using JniConverter = Internal::ObjectJniConverter<TObjectHandle>;

	// Static public interface.
	public:
		// Construct new object by given handle type.
		template< typename THandle, typename... TArguments >
		static inline THandle ConstructHandle( const TArguments&... arguments );

		// Construct new object of given class and using given construction arguments.
		template< typename... TArguments >
		static inline JniObject Construct( const JniClass& class_handle, const TArguments&... arguments );

	// Construction and assignation.
	public:
		JniObject() = default;
		JniObject( const JniObject& other );
		JniObject( JniObject&& other );
		JniObject( const JniClass& class_handle );
		JniObject( JniClass&& class_handle );
		explicit JniObject( jobject object_ref );


		inline JniObject& operator = ( const JniObject& other );
		inline JniObject& operator = ( JniObject&& other );
		inline JniObject& operator = ( jobject object_ref )				{ return Black::CopyAndSwap( *this, object_ref ); };
		inline JniObject& operator = ( const JniClass& class_handle )	{ return Black::CopyAndSwap( *this, class_handle ); };
		inline JniObject& operator = ( JniClass&& class_handle )		{ return Black::CopyAndSwap( *this, std::move( class_handle ) ); };

	// Public interface.
	public:
		// Invalidate the handle.
		void Invalidate();


		// cast the instance to another type.
		template< typename TOtherHandle >
		inline TOtherHandle ConvertTo() const;


		// @see	Mutex::Lock()
		virtual void Lock() const override;

		// @see	Mutex::Unlock()
		virtual void Unlock() const override;

		// Call the `java.lang.Object.notify` function.
		void Notify() const;

		// Call the `java.lang.Object.notifyAll` function.
		void NotifyAll() const;

		// Call the `java.lang.Object.wait` function.
		void Wait() const;

		// Call the `java.lang.Object.wait` function.
		void Wait( const std::chrono::milliseconds millis ) const;

		// Call the `java.lang.Object.wait` function.
		void Wait( const std::chrono::milliseconds millis, std::chrono::nanoseconds nanos ) const;


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

	// Private static fields.
	private:
		static constexpr const char* LOG_CHANNEL = "Black/Jni/Object";

	// Private state.
	private:
		std::shared_ptr<_jobject>	m_object_ref;	// Shared JNI representation of Java object global reference.
		mutable JniClass			m_class_handle;	// Handle to class of stored object.
	};


	inline const bool operator == ( const JniObject& left, const JniObject& right );
	inline const bool operator != ( const JniObject& left, const JniObject& right );
}
}
}
}
