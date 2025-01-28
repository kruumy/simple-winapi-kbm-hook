#include "keyboard.hpp"
#include <map>
#include <Windows.h>

static std::map<iohook::keyboard::OnEvent, iohook::keyboard::events> keyboard_handlers{};

static HHOOK keyboard_hook;

LRESULT CALLBACK keyboardhook_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
		int key_code = key->vkCode;
		switch (wParam)
		{
		case WM_KEYDOWN:
			for (const auto& h : keyboard_handlers)
				if (h.second == iohook::keyboard::OnKeyDown)
				{
					h.first(key_code);
				}
			break;
		case WM_KEYUP:
			for (const auto& h : keyboard_handlers)
				if (h.second == iohook::keyboard::OnKeyUp)
				{
					h.first(key_code);
				}
			break;
		}
	}
	return CallNextHookEx(keyboard_hook, nCode, wParam, lParam);
}

void iohook::keyboard::enable()
{
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardhook_proc, NULL, 0);
}

void iohook::keyboard::disable()
{
	UnhookWindowsHookEx(keyboard_hook);
	keyboard_handlers.clear();
}

void iohook::keyboard::subscribe(iohook::keyboard::events event, const iohook::keyboard::OnEvent& func)
{
	keyboard_handlers[func] = event;
}

void iohook::keyboard::unsubscribe(const iohook::keyboard::OnEvent& func)
{
	keyboard_handlers.erase(func);
}
