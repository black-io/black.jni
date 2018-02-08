#include <black.jni.h>


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	const bool SharedStateCache::Initialize()
	{

	}

	const bool SharedStateCache::Finalize()
	{
		EnsureStorageReleased<Black::BUILD_CONFIGURATION>();
	}

	template< Black::BuildMode >
	void SharedStateCache::EnsureStorageReleased()
	{
		auto storage_check = []( const Storage::value_type& storage ) -> bool
		{
			//return storage.second->
		};

		EXPECTS( std::all_of( m_storage.begin(), m_storage.end(),  ) );
	}

	template<>
	void SharedStateCache::EnsureStorageReleased<Black::BuildMode::Release>()
	{

	}
}
}
}
}
