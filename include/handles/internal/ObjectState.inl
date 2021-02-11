#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	template< typename TState, bool IS_PERSISTENT >
	ObjectState<TState, IS_PERSISTENT>::ObjectState( const ObjectState<TState, IS_PERSISTENT>& other )
		: m_buffer{ other.m_buffer }
	{
		Black::MutexLock lock{ ObjectStateRegistry::GetMutex() };
		RetainBuffer();
	}

	template< typename TState, bool IS_PERSISTENT >
	ObjectState<TState, IS_PERSISTENT>::ObjectState( ObjectState<TState, IS_PERSISTENT>&& other )
		: m_buffer{ std::exchange( other.m_buffer, nullptr ) }
	{
	}

	template< typename TState, bool IS_PERSISTENT >
	ObjectState<TState, IS_PERSISTENT>::~ObjectState()
	{
		CRET( m_buffer == nullptr );

		Black::MutexLock lock{ ObjectStateRegistry::GetMutex() };
		ReleaseBuffer();
	}

	template< typename TState, bool IS_PERSISTENT >
	inline ObjectState<TState, IS_PERSISTENT>& ObjectState<TState, IS_PERSISTENT>::operator=( const ObjectState<TState, IS_PERSISTENT>& other )
	{
		Black::MutexLock lock{ ObjectStateRegistry::GetMutex() };

		ReleaseBuffer();
		m_buffer = other.m_buffer;
		RetainBuffer();

		return *this;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline ObjectState<TState, IS_PERSISTENT>& ObjectState<TState, IS_PERSISTENT>::operator=( ObjectState<TState, IS_PERSISTENT>&& other )
	{
		Black::MutexLock lock{ ObjectStateRegistry::GetMutex() };

		ReleaseBuffer();
		m_buffer = std::exchange( other.m_buffer, nullptr );

		return *this;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline ObjectStateBuffer<TState>& ObjectState<TState, IS_PERSISTENT>::GetBuffer() const
	{
		CRET( m_buffer != nullptr, *m_buffer );

		Black::MutexLock lock{ ObjectStateRegistry::GetMutex() };
		m_buffer = ObjectStateRegistry::GetStateBuffer<TState>();
		ENSURES_DEBUG( m_buffer != nullptr );

		RetainBuffer();
		MakeBufferPersistent();
		return *m_buffer;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void ObjectState<TState, IS_PERSISTENT>::RetainBuffer() const
	{
		CRET( m_buffer == nullptr );
		m_buffer->Retain();
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void ObjectState<TState, IS_PERSISTENT>::ReleaseBuffer() const
	{
		CRET( m_buffer == nullptr );
		m_buffer->Release();
		m_buffer = nullptr;
	}

	template< typename TState, bool IS_PERSISTENT >
	inline void ObjectState<TState, IS_PERSISTENT>::MakeBufferPersistent() const
	{
		CRET( !IS_PERSISTENT );
		m_buffer->MakePersistent();
	}
}
}
}
}
