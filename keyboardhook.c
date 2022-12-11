#include <windows.h>
#include "keyboardhook.h"

size_t onKeyDown_handlers_amount;
key_event* onKeyDown_handlers;

size_t onKeyUp_handlers_amount;
key_event* onKeyUp_handlers;

HHOOK keyboard_hook;

LRESULT CALLBACK keyboardhook_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
		int key_code = key->vkCode;
		switch (wParam)
		{
			case WM_KEYUP:
				for (size_t i = 0; i < onKeyUp_handlers_amount; i++)
				{
					if (onKeyUp_handlers[i])
					{
						onKeyUp_handlers[i](key_code);
					}
				}
				break;
			case WM_KEYDOWN:
				for (size_t i = 0; i < onKeyDown_handlers_amount; i++)
				{
					if (onKeyDown_handlers[i])
					{
						onKeyDown_handlers[i](key_code);
					}
				}
				break;
		}
		return 0;
	}
	return CallNextHookEx(keyboard_hook, nCode, wParam, lParam);
}

BOOL keyboardhook_enable(size_t max_onKeyDown_handlers, size_t max_onKeyUp_handlers)
{
	onKeyDown_handlers_amount = max_onKeyDown_handlers;
	onKeyUp_handlers_amount = max_onKeyUp_handlers;

	if (onKeyDown_handlers_amount > 0)
	{
		onKeyDown_handlers = (key_event*)malloc(sizeof(key_event) * onKeyDown_handlers_amount);
		if (onKeyDown_handlers == NULL)
		{
			return 1;
		}
		memset(onKeyDown_handlers, 0, sizeof(key_event) * onKeyDown_handlers_amount);
	}

	if (onKeyUp_handlers_amount > 0)
	{
		onKeyUp_handlers = (key_event*)malloc(sizeof(key_event) * onKeyUp_handlers_amount);
		if (onKeyUp_handlers == NULL)
		{
			return 1;
		}
		memset(onKeyUp_handlers, 0, sizeof(key_event) * onKeyUp_handlers_amount);
	}

	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardhook_proc, NULL, 0);

	return 0;
}


void keyboardhook_disable()
{
	UnhookWindowsHookEx(keyboard_hook);
	free(onKeyDown_handlers);
	free(onKeyUp_handlers);
	onKeyDown_handlers_amount = 0;
	onKeyUp_handlers_amount = 0;
}

BOOL keyboardhook_subscribe_onKeyDown(key_event handler)
{
	for (size_t i = 0; i < onKeyDown_handlers_amount; i++)
	{
		if (!onKeyDown_handlers[i])
		{
			onKeyDown_handlers[i] = handler;
			return 0;
		}
	}
	return 1;
}

BOOL keyboardhook_subscribe_onKeyUp(key_event handler)
{
	for (size_t i = 0; i < onKeyUp_handlers_amount; i++)
	{
		if (!onKeyUp_handlers[i])
		{
			onKeyUp_handlers[i] = handler;
			return 0;
		}
	}
	return 1;
}

BOOL keyboardhook_unsubscribe_onKeyDown(key_event handler)
{
	for (size_t i = 0; i < onKeyDown_handlers_amount; i++)
	{
		if (onKeyDown_handlers[i] == handler)
		{
			onKeyDown_handlers[i] = NULL;
			return 0;
		}
	}
	return 1;
}

BOOL keyboardhook_unsubscribe_onKeyUp(key_event handler)
{
	for (size_t i = 0; i < onKeyUp_handlers_amount; i++)
	{
		if (onKeyUp_handlers[i] == handler)
		{
			onKeyUp_handlers[i] = NULL;
			return 0;
		}
	}
	return 1;
}