#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace Handles
{
namespace Internal
{
	/**
		@brief	Object state holder.

		This template implements the Lightweight pattern for the JNI objects. Using this template one can access the same instance of the state
		between all instances of JNI object.

		@tparam	TState			Type of object state to share.
		@tparam	IS_PERSISTENT	Whether the state should be kept alive after all references released.
	*/
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
		inline const TState& GetState() const		{ return *GetBuffer().GetState(); };


		inline const TState* operator -> () const	{ return GetBuffer().GetState(); };

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
