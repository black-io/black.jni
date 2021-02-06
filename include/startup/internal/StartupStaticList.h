#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
namespace Internal
{
	/**
		@breif	Static list for JNI startup entities.

		Any JNI startup entity will be linked into this startup list. It makes possible to execute the code of entities from inside of JNI library.
	*/
	using StartupStaticList = Black::StaticList<BasicStartupNode>;
}
}
}
}
