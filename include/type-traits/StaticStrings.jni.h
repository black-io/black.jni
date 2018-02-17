#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace TypeTraits
{
namespace Traits
{
	// Class path extractor for class signatures.
	template< typename TClassSignature >
	struct ClassPathExtractor;

	// Extract the class path from class signature.
	template< char... CHARS >
	struct ClassPathExtractor<Black::StaticString<'L', CHARS...>> final
	{
		// JNI signature.
		using Signature = Black::StaticStrings::RemoveSuffix<1, Black::StaticString<CHARS...>>;
	};

	// Extract the class path from array signature.
	template< char... CHARS >
	struct ClassPathExtractor<Black::StaticString<'[', CHARS...>> final
	{
		// JNI signature.
		using Signature = Black::StaticString<CHARS...>;
	};
}


	// Transform the class path into JNI-consumable class signature.
	template< char... CHARS >
	using JniClassSignature		= Black::StaticString<'L', CHARS..., ';'>;

	// Transform the type signature into JNI-consumable array signature.
	template< typename TValueSignature >
	using JniArraySignature		= Black::StaticStrings::Join<Black::StaticString<'['>, TValueSignature>;

	// Get the JNI-consumable function signature.
	template< typename TResultSignature, typename... TArgumentSignatures >
	using JniFunctionSignatureBase	= Black::StaticStrings::Join<Black::StaticString<'('>, TArgumentSignatures..., Black::StaticString<')'>, TResultSignature>;

	// Get the class path from class signature.
	template< typename TClassSignature >
	using JniClassPath			= typename Traits::ClassPathExtractor<TClassSignature>::Signature;
}
}
}
