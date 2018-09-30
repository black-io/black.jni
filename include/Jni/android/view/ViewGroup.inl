#pragma once


namespace Jni
{
inline namespace android
{
inline namespace view
{
	struct ViewGroup::ViewGroupState final
	{
		Black::JniClass	class_handle{ ClassPath::GetData() };

		Black::JniMemberFunction<void, View>						add_view_0				{ class_handle, "addView" };
		Black::JniMemberFunction<void, View, int32_t>				add_view_1				{ class_handle, "addView" };
		Black::JniMemberFunction<void, View, LayoutParams>			add_view_2				{ class_handle, "addView" };
		Black::JniMemberFunction<void, View, int32_t, LayoutParams>	add_view_3				{ class_handle, "addView" };
		Black::JniMemberFunction<void, View>						bring_child_to_front	{ class_handle, "bringChildToFront" };
		Black::JniMemberFunction<void, View>						remove_view				{ class_handle, "removeView" };
		Black::JniMemberFunction<void>								remove_all_views		{ class_handle, "removeAllViews" };
	};

	inline void ViewGroup::AddView( View child ) const
	{
		m_handles->add_view_0.Call( *this, child );
	}

	inline void ViewGroup::AddView( View child, int32_t index ) const
	{
		m_handles->add_view_1.Call( *this, child, index );
	}

	inline void ViewGroup::AddView( View child, LayoutParams params ) const
	{
		m_handles->add_view_2.Call( *this, child, params );
	}

	inline void ViewGroup::AddView( View child, int32_t index, LayoutParams params ) const
	{
		m_handles->add_view_3.Call( *this, child, index, params );
	}

	inline void ViewGroup::BringChildToFront( View child ) const
	{
		m_handles->bring_child_to_front.Call( *this, child );
	}

	inline void ViewGroup::RemoveView( View view ) const
	{
		m_handles->remove_view.Call( *this, view );
	}

	inline void ViewGroup::RemoveAllViews() const
	{
		m_handles->remove_all_views.Call( *this );
	}
}
}
}
