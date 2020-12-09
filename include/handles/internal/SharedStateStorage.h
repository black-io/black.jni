#pragma once


namespace Black
{
inline namespace Jni
{
inline namespace VirtualMachine
{
namespace Internal
{
	/**
		@brief	The shared state entity.
		The regular entity of arbitrary shared state.

		The instance of this type is common to be used inside of shared state cache.
		The type implements common interface for any concrete shared state.
		It not supposed for instance of type to be copied, moved or even constructed.
		The instance may be used only by pointer or reference.
	*/
	class SharedStateEntity : private Black::NonTransferable
	{
	public:
		virtual ~SharedStateEntity() = default;


		// Check that the entity is currently allocated.
		virtual const bool IsAllocated() const = 0;

	protected:
		SharedStateEntity() = default;
	};

	// The shared state storage.
	template< typename TState >
	class SharedStateStorage final : public SharedStateEntity
	{
	public:
		virtual ~SharedStateStorage();


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

	private:
		// Create the state.
		inline void CreateState();

		// Delete the state.
		inline void DeleteState();

	private:
		static constexpr size_t	STORAGE_LENGTH	= Black::GetAlignedSize( sizeof( TState ), alignof( TState ) );

		TState*		m_state						= nullptr;	// Pointer to existent state, when constructed.
		int32_t		m_presence					= 0;		// The number of current references to this state.
		uint8_t		m_storage[ STORAGE_LENGTH ]	= {};		// The storage for state to construct.
		bool		m_is_persistent				= false;	// if `true`, once the state constructed, it stays even after all references dropped.
	};
}
}
}
}
