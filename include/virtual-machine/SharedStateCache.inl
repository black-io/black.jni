#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
	template< typename TState >
	inline SharedStateStorage<TState>* SharedStateCache::GetCachedStorage()
	{
		Black::MutexLock lock{ m_latch };

		std::unique_ptr<SharedStateEntity>& entity = m_storage[ { typeid( TState ) } ];
		CRET( entity, static_cast<SharedStateStorage<TState>*>( entity.get() ) );

		auto new_entity = new SharedStateStorage<TState>{};
		entity.reset( new_entity );
		return new_entity;
	}
}
}
}
}
