#pragma once


namespace Jni
{
inline namespace android
{
inline namespace context
{
inline namespace res
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
		AssetManager( jobject object_ref );
		AssetManager( const AssetManager& other );
		AssetManager( AssetManager&& other );


		const AssetManager& operator = ( jobject object_ref );
		const AssetManager& operator = ( const AssetManager& other );
		const AssetManager& operator = ( AssetManager&& other );

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

			Black::JniMemberFunction<std::vector<std::string>, std::string>	list_path	{ class_handle,	"list" };
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
namespace Internal
{
	// JNI context specification for handles to `android.content.res.AssetManager` class.
	template<>
	struct NativeContext<::Jni::android::context::res::AssetManager> : public Black::NativeObjectContext<::Jni::android::context::res::AssetManager>
	{

	};
}
}
}
}
