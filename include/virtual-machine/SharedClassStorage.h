#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	//
	class SharedClassStorage final : private Black::NonTransferable
	{
	public:
		// Get the synchronization mutex for storage.
		inline const Black::Mutex& GetMutex() const		{ return m_latch; };

	private:
		// Shared class deletion routine.
		static void DeleteSharedClass( jclass value );

	private:
		using Storage = std::unordered_map<std::string, std::weak_ptr<_jclass>>;

		Black::CriticalSection	m_latch;
		Storage					m_storage;
	};
}
}
}
}
