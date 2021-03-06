#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Global
{
inline namespace StaticStrings
{
namespace Internal
{
	// Class path extractor for class signatures.
	template< typename TClassSignature >
	struct ClassPathExtractor;

	// Extract the class path from class signature.
	template< char... CHARS >
	struct ClassPathExtractor<Black::StaticString<'L', CHARS...>> final
	{
		// JNI signature.
		using Signature = Black::StaticStringRemoveSuffix<1, Black::StaticString<CHARS...>>;
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
	using JniClassSignatureString		= Black::StaticString<'L', CHARS..., ';'>;

	// Transform the type signature into JNI-consumable array signature.
	template< typename TValueSignature >
	using JniArraySignatureString		= Black::StaticStringJoin<Black::StaticString<'['>, TValueSignature>;

	// Get the JNI-consumable function signature.
	template< typename TResultSignature, typename... TArgumentSignatures >
	using JniFunctionSignatureString	= Black::StaticStringJoin<Black::StaticString<'('>, TArgumentSignatures..., Black::StaticString<')'>, TResultSignature>;

	// Get the class path from class signature.
	template< typename TClassSignature >
	using JniClassPathString			= typename Internal::ClassPathExtractor<TClassSignature>::Signature;
}
}
}
}
