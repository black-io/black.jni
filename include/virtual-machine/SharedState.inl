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
		Black::MutexLock lock{ Black::JniConnection::GetSharedStateStorage().GetMutex() };
		RetainStorage();
	}

	template< typename TState, bool IS_PERSISTENT >
	SharedState<TState, IS_PERSISTENT>::SharedState( SharedState<TState, IS_PERSISTENT>&& other )
		: m_storage{ other.m_storage }
	{
		other.m_storage = nullptr;
	}

	template< typename TState, bool IS_PERSISTENT >
	SharedState<TState, IS_PERSISTENT>::~SharedState()
	{
		CRET( m_storage == nullptr );

		Black::MutexLock lock{ Black::JniConnection::GetSharedStateStorage().GetMutex() };
		m_storage->Release();
	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedState<TState, IS_PERSISTENT>& SharedState<TState, IS_PERSISTENT>::operator=( const SharedState<TState, IS_PERSISTENT>& other )
	{
		Black::MutexLock lock{ Black::JniConnection::GetSharedStateStorage().GetMutex() };

		ReleaseStorage();
		m_storage = other.m_storage;
		RetainStorage();

		return *this;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedState<TState, IS_PERSISTENT>& SharedState<TState, IS_PERSISTENT>::operator=( SharedState<TState, IS_PERSISTENT>&& other )
	{
		if( m_storage != nullptr )
		{
			Black::MutexLock lock{ Black::JniConnection::GetSharedStateStorage().GetMutex() };
			ReleaseStorage();
		}

		std::swap( m_storage, other.m_storage );
		return *this;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline SharedStateStorage<TState>& SharedState<TState, IS_PERSISTENT>::GetStorage() const
	{
		CRET( m_storage != nullptr, *m_storage );

		Black::MutexLock lock{ Black::JniConnection::GetSharedStateStorage().GetMutex() };
		m_storage = Black::JniConnection::GetSharedStateStorage().GetCachedStorage<TState>();
		ENSURES_DEBUG( m_storage != nullptr );

		RetainStorage();
		MakeStoragePersistent();
		return *m_storage;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::RetainStorage() const
	{
		CRET( m_storage == nullptr );
		m_storage->Retain();
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::ReleaseStorage() const
	{
		CRET( m_storage == nullptr );
		m_storage->Release();
		m_storage = nullptr;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void SharedState<TState, IS_PERSISTENT>::MakeStoragePersistent() const
	{
		CRET( !IS_PERSISTENT );
		m_storage->MakePersistent();
	}
}
}
}
}
