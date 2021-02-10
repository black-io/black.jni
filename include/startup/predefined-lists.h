#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Startup
{
	/**
		@brief	JNI life-time static storage.

		This storage will carry any hosted service from its first use and until the `JNI_OnUnload` is called.
		The storage is invalidated just at the `JNI_OnUnload`, before the all other clearings.
		This storage should be used carefully a lot. The lifetime of hosted services is more longer than even the lifetime of `Black::PersistentStorage`.

		On Android OS the main function may be executed more than once between the execution of `JNI_OnLoad` and `JNI_OnUnload`.
		So this storage should never host any sensitive to process lifetime services.

		For example, Black::Jni itself keeps JNI connection and it's services inside of this storage. This services does not sensitive to lifetime of process,
		so it can be (and should be) stored in JNI session storage.
	*/
	using JniSessionStorage = Black::StaticStorage<Internal::JniSessionStorage>;
}
}
}
