#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	// Cache for shared states, which may be used in any place of 'Black::Jni' library.
	class SharedStateCache final
	{
	public:
		// Get the cached storage for shared state.
		template< typename TState >
		inline SharedStateStorage<TState>* GetCachedStorage();

	private:
		std::unordered_map<std::type_index, std::unique_ptr<SharedStateEntity>>	m_storage;
	};
}
}
}
}
