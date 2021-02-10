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
		@brief	Interface for all possible states of object.

		This type is base of Lightweight pattern implementation for JNI object state.
		All state buffers are derived from this interface and stored inside of `ObjectStateRegistry`.
		There is no practical reason to allow the copying or movement of object state instance, so the interface prohibits all such operations.
		All instances of this type should be owned by `ObjectStateRegistry` in order to work properly.
	*/
	class ObjectStateInterface : private Black::NonTransferable
	{
	// Construction and destruction.
	public:
		virtual ~ObjectStateInterface() = default;

	// Public interface.
	public:
		// Check that the entity is currently allocated.
		virtual const bool IsAllocated() const = 0;

	// Heirs construction.
	protected:
		ObjectStateInterface() = default;
	};


	/**
		@brief	Buffer to store the state of object.

		This type directly implements the Lightweight pattern for JNI objects. This buffer can store and properly initialize the state of particular object type.
		This type does not implement the sharing of state between the instances of particular type. The state sharing is implemented by `ObjectState` template.
		All shared states are owned and managed by `ObjectStateRegistry`. `ObjectState` tightly works with `ObjectStateRegistry`.

		The state is created on first retain of buffer and normally destructed on last release of buffer.
		But in some cases the state may be heavy to construct on the fly and the instances of object may require as quick construction as possible.
		For such cases the state may be marked as persistent. Such states constructs only once and live along the process lifetime.

		@tparam	TState	Type of object state to share.
	*/
	template< typename TState >
	class alignas( TState ) alignas( void* ) ObjectStateBuffer final : public ObjectStateInterface
	{
	// Construction and destruction.
	public:
		virtual ~ObjectStateBuffer();

	// Public interface.
	public:
		// Retain the storage.
		inline void Retain();

		// Release the storage.
		inline void Release();


		// Make the state to be persistent.
		inline void MakePersistent()					{ m_is_persistent = true; };

		// Get the state.
		inline TState* GetState() const					{ return m_state; };

		// Check that the entity is currently allocated.
		virtual const bool IsAllocated() const override	{ return m_presence > 0; };

	// Private inner types.
	private:
		// Type of raw memory buffer to store the state instance.
		struct alignas( TState ) StateBuffer final
		{
			std::byte buffer[ sizeof( TState ) ]; // Host the required size.
		};

	// Private interface.
	private:
		// Create the state.
		inline void CreateState();

		// Delete the state.
		inline void DeleteState();

	// Private state.
	private:
		TState*			m_state			= nullptr;	// Pointer to allocated state.
		int32_t			m_presence		= 0;		// The number of current references to this state.
		bool			m_is_persistent	= false;	// Whether the state should be retained even there is no reference to it.
		StateBuffer		m_buffer{};					// The buffer to host the instance of state.
	};
}
}
}
}
