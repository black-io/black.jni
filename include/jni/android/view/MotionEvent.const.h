#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	// Translation of motion actions.
	enum class MotionActionType : int32_t
	{
		Down		= AMOTION_EVENT_ACTION_DOWN,			// android.view.MotionEvent.ACTION_DOWN
		Up			= AMOTION_EVENT_ACTION_UP,				// android.view.MotionEvent.ACTION_UP
		Move		= AMOTION_EVENT_ACTION_MOVE,			// android.view.MotionEvent.ACTION_MOVE
		Cancel		= AMOTION_EVENT_ACTION_CANCEL,			// android.view.MotionEvent.ACTION_CANCEL
		Outside		= AMOTION_EVENT_ACTION_OUTSIDE,			// android.view.MotionEvent.ACTION_OUTSIDE
		PointerDown	= AMOTION_EVENT_ACTION_POINTER_DOWN,	// android.view.MotionEvent.ACTION_POINTER_DOWN
		PointerUp	= AMOTION_EVENT_ACTION_POINTER_UP,		// android.view.MotionEvent.ACTION_POINTER_UP
		HoverMve	= AMOTION_EVENT_ACTION_HOVER_MOVE,		// android.view.MotionEvent.ACTION_HOVER_MOVE
		Scroll		= AMOTION_EVENT_ACTION_SCROLL,			// android.view.MotionEvent.ACTION_SCROLL
		HoverEnter	= AMOTION_EVENT_ACTION_HOVER_ENTER,		// android.view.MotionEvent.ACTION_HOVER_ENTER
		HoverExit	= AMOTION_EVENT_ACTION_HOVER_EXIT,		// android.view.MotionEvent.ACTION_HOVER_EXIT
	};
}
}
}
