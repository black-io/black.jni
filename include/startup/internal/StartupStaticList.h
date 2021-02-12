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
		@breif	Static list for entries of JNI startup and JNI shutdown process.

		This list collects the parts of JNI startup and JNI shutdown processes.
		The list does not define any kind of order between nodes.

		Instances of this list may be used to access the stored collection of nodes.
	*/
	using StartupStaticList = Black::StaticList<BasicStartupNode>;
}
}
}
}
