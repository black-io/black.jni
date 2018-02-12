#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace Context
{
inline namespace Res
{
	// Handle for `android.content.res.AssetManager` objects.
	class AssetManager final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'c', 'o', 'n', 't', 'e', 'n', 't', '/',
			'r', 'e', 's', '/',
			'A', 's', 's', 'e', 't', 'M', 'a', 'n', 'a', 'g', 'e', 'r'
		>;

	// Construction and assignation.
	public:
		AssetManager() = default;
		AssetManager( jobject object_ref ) : Black::JniObject{ object_ref } { AcquireAssets(); };
		AssetManager( const AssetManager& other ) : Black::JniObject( other ) { AcquireAssets(); };
		AssetManager( AssetManager&& other ) : Black::JniObject( std::move( other ) ) { AcquireAssets(); };


		const AssetManager& operator = ( jobject object_ref )			{ Black::JniObject::operator=( object_ref ); return *this; };
		const AssetManager& operator = ( const AssetManager& other )	{ Black::JniObject::operator=( other ); return *this; };
		const AssetManager& operator = ( AssetManager&& other )			{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Check that the given path leads to valid assets folder.
		const bool IsValidFolder( const std::string& path ) const;

		// Check that the given path leads to valid asset file.
		const bool IsValidFile( const std::string& path ) const;

		// Open the asset.
		std::shared_ptr<AAsset> OpenAsset( const std::string& path, const AssetOpenMode open_mode ) const;

		// Query the asset manager to get all files in given folder.
		void ListFolder( std::deque<std::string>* files, std::deque<std::string>* folders, const std::string& path ) const;

	// Private interface.
	private:
		// Acquire the low-level assets manager.
		void AcquireAssets();

	// Private state.
	private:
		struct AssetManagerState
		{
			Black::JniClass		class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<std::vector<std::string>, std::string>	list_path	= { class_handle,	"list" };
		};

		AAssetManager*							m_assets	= nullptr;	// Low-level representation of assets manager.
		SharedState<AssetManagerState, true>	m_handles;				// Shared JNI handles.
	};
}
}
}
}


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI context specification for handles to `android.content.res.AssetManager` class.
	template<>
	struct NativeContext<::Jni::Android::Context::Res::AssetManager> : public Black::NativeObjectContext<::Jni::Android::Context::Res::AssetManager>
	{

	};
}
}
}
}
