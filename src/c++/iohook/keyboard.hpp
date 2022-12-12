#pragma once

namespace iohook
{
	namespace keyboard
	{
		typedef void (*OnEvent)(int);

		enum events
		{
			OnKeyDown,
			OnKeyUp
		};

		void enable();
		void disable();

		void subscribe(events event,const OnEvent& func);

		void unsubscribe(const OnEvent& func);
	}
}
