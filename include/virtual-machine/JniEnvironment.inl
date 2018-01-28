#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
	template< typename TValue >
	inline const bool JniEnvironment::GetValue(
		const Black::JniObject& object_handle,
		const Black::JniMemberField<TValue>& field_handle,
		TValue& value_storage
	) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return field_handle.GetValue( m_local_env, *object_handle, value_storage );
	}

	template< typename TValue >
	inline const bool JniEnvironment::GetValue( const Black::JniStaticField<TValue>& field_handle, TValue& value_storage ) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return field_handle.GetValue( m_local_env, value_storage );
	}

	template< typename TValue >
	inline const bool JniEnvironment::SetValue(
		const Black::JniObject& object_handle,
		const Black::JniMemberField<TValue>& field_handle,
		const TValue& value_storage
	) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return field_handle.SetValue( m_local_env, *object_handle, value_storage );
	}

	template< typename TValue >
	inline const bool JniEnvironment::SetValue( const Black::JniStaticField<TValue>& field_handle, const TValue& value_storage ) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return field_handle.SetValue( m_local_env, value_storage );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniEnvironment::Call(
		const Black::JniObject& object_handle,
		const Black::JniMemberFunction<TResult, TArguments...>& function_handle,
		const TArguments&... arguments
	) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return function_handle.Call( m_local_env, *object_handle, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniEnvironment::CallNonVirtual(
		const Black::JniObject& object_handle,
		const Black::JniMemberFunction<TResult, TArguments...>& function_handle,
		const TArguments&... arguments
	) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return function_handle.CallNonVirtual( m_local_env, *object_handle, arguments... );
	}

	template< typename TResult, typename... TArguments >
	inline TResult JniEnvironment::Call(
		const Black::JniStaticFunction<TResult, TArguments...>& function_handle,
		const TArguments&... arguments
	) const
	{
		ENSURES_DEBUG( IsThreadLocal() );
		return function_handle.Call( m_local_env, arguments... );
	}
}
}
}
