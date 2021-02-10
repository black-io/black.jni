#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	template< typename TState >
	ObjectStateBuffer<TState>::~ObjectStateBuffer()
	{
		DeleteState();
	}

	template< typename TState >
	inline void ObjectStateBuffer<TState>::Retain()
	{
		++m_presence;
		ENSURES_DEBUG( m_presence > 0 );

		CRET( m_presence > 1 );
		CreateState();
	}

	template< typename TState >
	inline void ObjectStateBuffer<TState>::Release()
	{
		EXPECTS_DEBUG( m_presence > 0 );
		--m_presence;

		CRET( m_presence > 0 );
		DeleteState();
	}

	template< typename TState >
	inline void ObjectStateBuffer<TState>::CreateState()
	{
		EXPECTS_DEBUG( m_state == nullptr );

		m_state = new( &m_buffer ) TState{};
	}

	template< typename TState >
	inline void ObjectStateBuffer<TState>::DeleteState()
	{
		CRET( m_state == nullptr );
		m_state->~TState();
		m_state = nullptr;
	}
}
}
}
}
