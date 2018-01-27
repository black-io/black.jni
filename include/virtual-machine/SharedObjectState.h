#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Traits
{
	//
	template< typename TState, bool IS_PERSISTENT = false >
	class SharedObjectState final
	{
	// Construction and assignment.
	public:
		SharedObjectState() = default;
		SharedObjectState( const SharedObjectState& other );
		SharedObjectState( SharedObjectState&& other );
		~SharedObjectState();


		inline SharedObjectState& operator = ( const SharedObjectState& other );
		inline SharedObjectState& operator = ( SharedObjectState&& other );

	// Public interface.
	public:
		// Get the shared state.
		inline const TState& GetState() const		{ return *GetStorage().GeState(); };

		inline const TState* operator -> () const	{ return GetStorage().GeState(); };

	// Private interface.
	private:
		// Lazy initialization for state storage.
		inline SharedStateStorage<TState>& GetStorage() const;

		// Retain the valid storage.
		inline void RetainStorage() const;

		// Release the valid storage.
		inline void ReleaseStorage() const;

		// Make the valid storage to be persistent.
		inline void MakeStoragePersistent() const;

	// Private state.
	private:
		mutable SharedStateStorage<TState>*	m_storage = nullptr;
	};
}
}
}
}
