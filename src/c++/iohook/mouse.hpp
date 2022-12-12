#pragma once

namespace iohook
{
	namespace mouse
	{
		typedef void (*OnEvent)(int);
		typedef void (*OnMoveEvent)(int,int);

		enum events
		{
			OnMouseScroll,
			OnMouseMove,
			OnMouseButtonDown,
			OnMouseButtonUp
		};

		void enable();
		void disable();

		void subscribe(events event,const OnEvent& func);
		void subscribe(events event,const OnMoveEvent& func);

		void unsubscribe(const OnEvent& func);
		void unsubscribe(const OnMoveEvent& func);
	}
}
