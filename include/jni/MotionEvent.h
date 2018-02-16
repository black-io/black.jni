#pragma once


namespace Jni
{
inline namespace Android
{
inline namespace View
{
	// Handle for `android.view.MotionEvent` objects.
	class MotionEvent final : public Black::JniObject
	{
	public:
		// Class path.
		using ClassPath = Black::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'v', 'i', 'e', 'w', '/',
			'M', 'o', 't', 'i', 'o', 'n', 'E', 'v', 'e', 'n', 't'
		>;

	// Construction and assignation.
	public:
		MotionEvent() = default;
		MotionEvent( jobject object_ref ) : Black::JniObject{ object_ref } {};
		MotionEvent( const MotionEvent& other ) : Black::JniObject( other ) {};
		MotionEvent( MotionEvent&& other ) : Black::JniObject( std::move( other ) ) {};


		const MotionEvent& operator = ( jobject object_ref )		{ Black::JniObject::operator=( object_ref ); return *this; };
		const MotionEvent& operator = ( const MotionEvent& other )	{ Black::JniObject::operator=( other ); return *this; };
		const MotionEvent& operator = ( MotionEvent&& other )		{ Black::JniObject::operator=( std::move( other ) ); return *this; };

	// Public interface.
	public:
		// Get the class of input device.
		inline const Jni::InputSourceClass GetSource() const				{ return m_handles->get_source_class.Call( *this ); };

		// Get the type of motion action, without pointer index information.
		inline const Jni::MotionActionType GetActionType() const			{ return m_handles->get_action_masked.Call( *this ); };

		// Get the point index associated with action.
		inline const int32_t GetPointIndex() const							{ return m_handles->get_action_index.Call( *this ); };

		// Get the number of points in event.
		inline const int32_t GetPointsCount() const							{ return m_handles->get_pointer_count.Call( *this ); };

		// Get the time (in ms) when the user originally pressed down to start a stream of position events.
		inline const int64_t GetDownTime() const							{ return m_handles->get_down_time.Call( *this ); };

		// Gets the state of all buttons that are pressed such as a mouse or stylus button.
		inline const int32_t GetButtonState() const							{ return m_handles->get_buton_state.Call( *this ); };


		// Get the id of point by given index.
		inline const int32_t GetPointId( const int32_t index ) const		{ return m_handles->get_pointer_id.Call( *this, index ); };

		// Get the X coordinate of point.
		inline const float GetPointX( const int32_t index ) const			{ return m_handles->get_pointer_x.Call( *this, index ); };

		// Get the Y coordinate of point.
		inline const float GetPointY( const int32_t index ) const			{ return m_handles->get_pointer_y.Call( *this, index ); };

		// Get the pressure of point.
		inline const float GetPointPressure( const int32_t index ) const	{ return m_handles->get_pointer_pressure.Call( *this, index ); };

	// Private state.
	private:
		struct MotionEventState final
		{
			Black::JniClass	class_handle{ ClassPath::GetData() };

			Black::JniMemberFunction<int32_t>				get_pointer_count		{ class_handle, "getPointerCount" };
			Black::JniMemberFunction<Jni::InputSourceClass>	get_source_class		{ class_handle, "getSource" };
			Black::JniMemberFunction<Jni::MotionActionType>	get_action_masked		{ class_handle, "getActionMasked" };
			Black::JniMemberFunction<int32_t>				get_action_index		{ class_handle, "getActionIndex" };
			Black::JniMemberFunction<int64_t>				get_down_time			{ class_handle, "getDownTime" };
			Black::JniMemberFunction<int32_t>				get_buton_state			{ class_handle, "getButtonState" };

			Black::JniMemberFunction<int32_t, int32_t>		get_pointer_id			{ class_handle, "getPointerId" };
			Black::JniMemberFunction<float, int32_t>		get_pointer_x			{ class_handle, "getX" };
			Black::JniMemberFunction<float, int32_t>		get_pointer_y			{ class_handle, "getY" };
			Black::JniMemberFunction<float, int32_t>		get_pointer_pressure	{ class_handle, "getPressure" };
		};

		SharedState<MotionEventState, true>	m_handles;	// Shared JNI handles.
	};
}
}
}


namespace Black
{
inline namespace Jni
{
inline namespace Marshaling
{
namespace Traits
{
	// JNI context specification for handles to `java.util.Locale` class.
	template<>
	struct NativeContext<::Jni::Android::View::MotionEvent> : public Black::NativeObjectContext<::Jni::Android::View::MotionEvent>
	{

	};
}
}
}
}
