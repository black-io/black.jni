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
	SharedStateStorage<TState>::~SharedStateStorage()
	{
		DeleteState();
	}

	template< typename TState >
	inline void SharedStateStorage<TState>::Retain()
	{
		++m_presence;
		ENSURES_DEBUG( m_presence > 0 );

		CRET( m_presence > 1 );
		CreateState();
	}

	template< typename TState >
	inline void SharedStateStorage<TState>::Release()
	{
		EXPECTS_DEBUG( m_presence > 0 );
		--m_presence;

		CRET( m_presence > 0 );
		DeleteState();
	}

	template< typename TState >
	inline void SharedStateStorage<TState>::CreateState()
	{
		EXPECTS_DEBUG( m_state == nullptr );

		uint8_t* state_memory	= Black::GetAlignedPointer( m_storage, alignof( TState ) );
		m_state					= new( state_memory ) TState{};
	}

	template< typename TState >
	inline void SharedStateStorage<TState>::DeleteState()
	{
		CRET( m_state == nullptr );
		m_state->~TState();
		m_state = nullptr;
	}
}
}
}
}
