#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	/**
		@brief		Thread-local JNI environment.
		@warning	The instance of this class may not be used in other thread than the instance allocated.
		@note		Its not recommended to store `JniEnvironment` instances in global memory.

		This class is only wrap, there are may be no needs to store instances of one.
		The instance is supposed to be allocated only on stack and only in short scope of function.
		There are no copying or moving of instances allowed.
	*/
	class JniEnvironment final : private Black::NonTransferable
	{
	public:
		JniEnvironment() = default;


		// Read the value into storage from given field of given JNI object.
		template< typename TValue >
		inline const bool GetValue( const Black::JniObject& objct_handle, const Black::JniMemberField<TValue>& field_hanle, TValue& value_storage ) const;

		// Read the value into storage from given static field.
		template< typename TValue >
		inline const bool GetValue( const Black::JniStaticField<TValue>& field_hanle, TValue& value_storage ) const;

		// Write the value from storage into given field of given object.
		template< typename TValue >
		inline const bool SetValue( const Black::JniObject& objct_handle, const Black::JniMemberField<TValue>& field_hanle, const TValue& value_storage ) const;

		// Write the value from storage into given static field.
		template< typename TValue >
		inline const bool SetValue( const Black::JniStaticField<TValue>& field_hanle, const TValue& value_storage ) const;


		// Call the member-function using given arguments.
		template< typename TResult, typename... TArguments >
		inline TResult Call(
			const Black::JniObject& objct_handle,
			const Black::JniMemberFunction<TResult, TArguments...>& function_handle,
			const TArguments&... arguments
		) const;

		// Call the member-function using given arguments.
		template< typename TResult, typename... TArguments >
		inline TResult Call(
			const Black::JniStaticFunction<TResult, TArguments...>& function_handle,
			const TArguments&... arguments
		) const;


		// Check that the instance is valid.
		inline const bool IsValid() const				{ return m_local_env != nullptr; };

		// Check that the instance is used in its own thread.
		inline const bool IsThreadLocal() const			{ return m_owner_id == std::this_thread::get_id(); };


		inline JNIEnv* operator -> () const				{ ENSURES_DEBUG( IsThreadLocal() ); return m_local_env; };
		inline explicit operator const bool () const	{ return IsValid(); };

	private:
		JNIEnv* const			m_local_env	= JniConnection::GetLocalEnvironment();	// Thread-local JNI environment.
		const std::thread::id	m_owner_id	= std::this_thread::get_id();			// Id of thread owning the environment.
	};
}
}
}
