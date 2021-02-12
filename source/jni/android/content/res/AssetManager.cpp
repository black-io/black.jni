#include <black/jni.h>
#include <black/jni/android/content/res/AssetManager.h>

#include <android/asset_manager_jni.h>


namespace
{
	class ScopedAsset final
	{
	public:
		inline ScopedAsset( AAsset* asset ) : m_asset{ asset } {};
		inline ~ScopedAsset() { if( m_asset ){ AAsset_close( m_asset ); } };


		inline AAsset* Get() const	{ return m_asset; };

	private:
		AAsset*	m_asset = nullptr;
	};

	class ScopedAssetFolder final
	{
	public:
		inline ScopedAssetFolder( AAssetDir* asset_dir ) : m_asset_dir{ asset_dir } {};
		inline ~ScopedAssetFolder() { if( m_asset_dir ){ AAssetDir_close( m_asset_dir ); } };

		inline AAssetDir* Get() const	{ return m_asset_dir; };

	private:
		AAssetDir*	m_asset_dir = nullptr;
	};
}


namespace Jni
{
inline namespace android
{
inline namespace content
{
inline namespace res
{
	AssetManager::AssetManager( jobject object_ref )
		: Black::JniObject{ object_ref }
	{
		AcquireAssets();
	}

	AssetManager::AssetManager( const AssetManager& other )
		: Black::JniObject( other )
	{
		AcquireAssets();
	}

	AssetManager::AssetManager( AssetManager&& other )
		: Black::JniObject( std::move( other ) )
	{
		AcquireAssets();
	}

	const AssetManager& AssetManager::operator=( jobject object_ref )
	{
		Black::JniObject::operator=( object_ref );

		AcquireAssets(); return
		*this;
	}

	const AssetManager& AssetManager::operator=( const AssetManager& other )
	{
		Black::JniObject::operator=( other );

		AcquireAssets();
		return *this;
	}

	const AssetManager& AssetManager::operator=( AssetManager&& other )
	{
		Black::JniObject::operator=( std::move( other ) );

		AcquireAssets();
		return *this;
	}

	const bool AssetManager::IsValidFolder( const std::string& path ) const
	{
		ScopedAssetFolder folder{ AAssetManager_openDir( m_assets, path.data() ) };
		return AAssetDir_getNextFileName( folder.Get() ) != nullptr;
	}

	const bool AssetManager::IsValidFile( const std::string& path ) const
	{
		ScopedAsset asset{ AAssetManager_open( m_assets, path.data(), Black::GetEnumValue( AssetOpenMode::Default ) ) };
		return asset.Get() != nullptr;
	}

	std::shared_ptr<AAsset> AssetManager::OpenAsset( const std::string& path, const AssetOpenMode open_mode ) const
	{
		return {
			AAssetManager_open( m_assets, path.data(), Black::GetEnumValue( open_mode ) ),
			[]( AAsset* asset )
			{
				CRET( asset == nullptr );
				AAsset_close( asset );
			}
		};
	}

	void AssetManager::ListFolder( std::deque<std::string>* files, std::deque<std::string>* folders, const std::string& path ) const
	{
		CRET( ( files == nullptr ) && ( folders == nullptr ) );

		auto found_assets = m_handles->list_path.Call( *this, path );
		for( auto& found_asset : found_assets )
		{
			const std::string asset_path{ path + '/' + found_asset };
			if( IsValidFile( asset_path ) )
			{
				CCON( files == nullptr );
				files->push_back( std::move( found_asset ) );
			}
			else
			{
				CCON( folders == nullptr );
				folders->push_back( std::move( found_asset ) );
			}
		}
	}

	void AssetManager::AcquireAssets()
	{
		m_assets = nullptr;
		CRET( !IsValid() );
		EXPECTS( IsInstanceOf( m_handles->class_handle ) );

		JNIEnv* local_env	= Black::JniConnection::GetLocalEnvironment();
		m_assets			= AAssetManager_fromJava( local_env, GetJniReference() );
		ENSURES( m_assets != nullptr );
	}
}
}
}
}
