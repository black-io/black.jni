#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	template< typename TState >
	inline SharedStateStorage<TState>* SharedStateCache::GetCachedStorage()
	{
		SharedStateCache& cache = GetInstance();
		Black::MutexLock lock{ cache.m_latch };

		std::unique_ptr<SharedStateEntity>& entity = cache.m_storage[ { typeid( TState ) } ];
		CRET( entity, static_cast<SharedStateStorage<TState>*>( entity.get() ) );

		auto new_entity = new SharedStateStorage<TState>{};
		entity.reset( new_entity );
		return new_entity;
	}
}
}
}
}
