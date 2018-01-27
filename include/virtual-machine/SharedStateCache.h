#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	/**
		@brief	Cache for shared states.
		This class implements the cache for shared states, which may be used in any place of 'Black::Jni' library.

		The cache provides retrieving of state storage by the type of state.
		It means, there only one instance of some state type may exists in program.
		Each time the state is retrieved, the same shared instance of state will be returned.
		Once the state storage is retrieved via `GetCachedStorage` function, it becomes persistent and will be deleted only on program termination.

		The cache is not thread-safe inside, but it supplies the `Black::Mutex` interface to implement thread-safety on higher levels of execution.
		It will be more efficient to lock the mutex when the storage is actually used by consumer.
	*/
	class SharedStateCache final : private Black::NonTransferable
	{
	public:
		// Get the cached storage for shared state.
		template< typename TState >
		inline SharedStateStorage<TState>* GetCachedStorage();


		// Get the synchronization mutex for storage.
		inline const Black::Mutex& GetMutex() const		{ return m_latch; };

	private:
		using Storage = std::unordered_map<std::type_index, std::unique_ptr<SharedStateEntity>>;

		Black::CriticalSection	m_latch;	// Synchronization latch.
		Storage					m_storage;	// Permanent storage for shared states.
	};
}
}
}
}
