#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	// The shared state entity.
	template< typename TState, bool IS_PERSISTENT = false >
	class ObjectState final
	{
	// Construction and assignment.
	public:
		ObjectState() = default;
		ObjectState( const ObjectState& other );
		ObjectState( ObjectState&& other );
		~ObjectState();


		inline ObjectState& operator = ( const ObjectState& other );
		inline ObjectState& operator = ( ObjectState&& other );

	// Public interface.
	public:
		// Get the shared state.
		inline const TState& GetState() const		{ return *GetStorage().GetState(); };


		inline const TState* operator -> () const	{ return GetStorage().GetState(); };

	// Private interface.
	private:
		// Lazy initialization for state storage.
		inline ObjectStateBuffer<TState>& GetBuffer() const;

		// Retain the valid storage.
		inline void RetainBuffer() const;

		// Release the valid storage.
		inline void ReleaseBuffer() const;

		// Make the valid storage to be persistent.
		inline void MakeBufferPersistent() const;

	// Private state.
	private:
		mutable ObjectStateBuffer<TState>* m_buffer = nullptr; // The buffer for state of given type.
	};
}
}
}
}
