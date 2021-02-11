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
	inline ObjectStateBuffer<TState>* ObjectStateRegistry::GetStateBuffer()
	{
		using StateBuffer = ObjectStateBuffer<TState>;

		const std::type_index state_index{ typeid( TState ) };
		ObjectStateRegistry& registry = GetInstance();

		Black::MutexLock lock{ registry.m_lock };

		std::unique_ptr<ObjectStateInterface>& state_buffer = registry.m_storage[ state_index ];
		CRET( state_buffer, static_cast<StateBuffer*>( state_buffer.get() ) );

		state_buffer = std::make_unique<StateBuffer>();
		return static_cast<StateBuffer*>( state_buffer.get() );
	}
}
}
}
}
