#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
	// The shared state entity.
	template< typename TState, bool IS_PERSISTENT = false >
	class SharedState final
	{
	// Construction and assignment.
	public:
		SharedState() = default;
		SharedState( const SharedState& other );
		SharedState( SharedState&& other );
		~SharedState();


		inline SharedState& operator = ( const SharedState& other );
		inline SharedState& operator = ( SharedState&& other );

	// Public interface.
	public:
		// Get the shared state.
		inline const TState& GetState() const		{ return *GetStorage().GetState(); };

		inline const TState* operator -> () const	{ return GetStorage().GetState(); };

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
