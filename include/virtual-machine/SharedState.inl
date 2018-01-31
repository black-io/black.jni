#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	template< typename TState, bool IS_PERSISTENT >
	SharedState<TState, IS_PERSISTENT>::SharedState( const SharedState<TState, IS_PERSISTENT>& other )
		: m_storage{ other.m_storage }
	{
		SharedStateCache& cache = Black::JniConnection::GetInstance().m_cached_states;
		Black::MutexLock lock{ cache.GetMutex() };
	}

	template< typename TState, bool IS_PERSISTENT >
	SharedState<TState, IS_PERSISTENT>::SharedState( SharedState<TState, IS_PERSISTENT>&& other )
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	SharedState<TState, IS_PERSISTENT>::~SharedState()
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedState<TState, IS_PERSISTENT>& SharedState<TState, IS_PERSISTENT>::operator=( const SharedState<TState, IS_PERSISTENT>& other )
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedState<TState, IS_PERSISTENT>& SharedState<TState, IS_PERSISTENT>::operator=( SharedState<TState, IS_PERSISTENT>&& other )
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedStateStorage<TState>& SharedState<TState, IS_PERSISTENT>::GetStorage() const
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::RetainStorage() const
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::ReleaseStorage() const
	{

	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::MakeStoragePersistent() const
	{

	}
}
}
}
}
