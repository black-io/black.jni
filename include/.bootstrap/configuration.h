#pragma once


// Cut off the compilation in case of target platform is not Android.
#if( !BLACK_ANDROID_PLATFORM )
	#error Black::Jni was designed for Android OS only! Be sure to exclude it from build for other target platforms.
#endif
