#include <Windows.h>
#include "mousehook.h"

size_t onMouseWheel_handlers_amount;
mousewheel_event* onMouseWheel_handlers;

size_t onMouseMove_handlers_amount;
mousemove_event* onMouseMove_handlers;

size_t onMouseButtonDown_handlers_amount;
mousebutton_event* onMouseButtonDown_handlers;

size_t onMouseButtonUp_handlers_amount;
mousebutton_event* onMouseButtonUp_handlers;

HHOOK mouse_hook;
LRESULT CALLBACK mousehook_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

            switch (wParam)
            {
                case WM_MOUSEWHEEL:
                    if (HIWORD(pMouseStruct->mouseData) == 120)
                    {
                        for (size_t i = 0; i < onMouseWheel_handlers_amount; i++)
                        {
                            if (onMouseWheel_handlers[i])
                            {
                                onMouseWheel_handlers[i](1);
                            }
                        }
                    }
                    else
                    {
                        for (size_t i = 0; i < onMouseWheel_handlers_amount; i++)
                        {
                            if (onMouseWheel_handlers[i])
                            {
                                onMouseWheel_handlers[i](-1);
                            }
                        }
                    }
                    break;
                case WM_MOUSEMOVE:
                    if (pMouseStruct != NULL)
                    {
                        for (size_t i = 0; i < onMouseMove_handlers_amount; i++)
                        {
                            if (onMouseMove_handlers[i])
                            {
                                onMouseMove_handlers[i](pMouseStruct->pt.x, pMouseStruct->pt.y);
                            }
                        }
                    }
                    break;
                case WM_LBUTTONDOWN:
                    for (size_t i = 0; i < onMouseButtonDown_handlers_amount; i++)
                    {
                        if (onMouseButtonDown_handlers[i])
                        {
                            onMouseButtonDown_handlers[i](0);
                        }
                    }
                    break;
                case WM_RBUTTONDOWN:
                    for (size_t i = 0; i < onMouseButtonDown_handlers_amount; i++)
                    {
                        if (onMouseButtonDown_handlers[i])
                        {
                            onMouseButtonDown_handlers[i](1);
                        }
                    }
                    break;
                case WM_LBUTTONUP:
                    for (size_t i = 0; i < onMouseButtonUp_handlers_amount; i++)
                    {
                        if (onMouseButtonUp_handlers[i])
                        {
                            onMouseButtonUp_handlers[i](0);
                        }
                    }
                    break;
                case WM_RBUTTONUP:
                    for (size_t i = 0; i < onMouseButtonUp_handlers_amount; i++)
                    {
                        if (onMouseButtonUp_handlers[i])
                        {
                            onMouseButtonUp_handlers[i](1);
                        }
                    }
                    break;
            }
    }
    return CallNextHookEx(mouse_hook, nCode, wParam, lParam);
}

BOOL mousehook_enable(size_t max_onMouseWheel_handlers, size_t max_onMouseMove_handlers, size_t max_onMouseButtonDown_handlers, size_t max_onMouseButtonUp_handlers)
{
    onMouseWheel_handlers_amount = max_onMouseWheel_handlers;
    onMouseMove_handlers_amount = max_onMouseMove_handlers;
    onMouseButtonDown_handlers_amount = max_onMouseButtonDown_handlers;
    onMouseButtonUp_handlers_amount = max_onMouseButtonUp_handlers;

    if (onMouseWheel_handlers_amount > 0)
    {
        onMouseWheel_handlers = (mousewheel_event*)calloc(onMouseWheel_handlers_amount, sizeof(mousewheel_event));
        if (onMouseWheel_handlers == NULL)
        {
            return 1;
        }
    }
    if (onMouseMove_handlers_amount > 0)
    {
        onMouseMove_handlers = (mousemove_event*)calloc(onMouseMove_handlers_amount, sizeof(mousemove_event));
        if (onMouseMove_handlers == NULL)
        {
            return 1;
        }
    }
    if (onMouseButtonDown_handlers_amount > 0)
    {
        onMouseButtonDown_handlers = (mousebutton_event*)calloc(onMouseButtonDown_handlers_amount, sizeof(mousebutton_event));
        if (onMouseButtonDown_handlers == NULL)
        {
            return 1;
        }
    }
    if (onMouseButtonUp_handlers_amount > 0)
    {
        onMouseButtonUp_handlers = (mousebutton_event*)calloc(onMouseButtonUp_handlers_amount, sizeof(mousebutton_event));
        if (onMouseButtonUp_handlers == NULL)
        {
            return 1;
        }
    }

    mouse_hook = SetWindowsHookExA(WH_MOUSE_LL, mousehook_proc, NULL, 0);

    return 0;
}


void mousehook_disable()
{
    UnhookWindowsHookEx(mouse_hook);
    free(onMouseWheel_handlers);
    free(onMouseMove_handlers);
    free(onMouseButtonDown_handlers);
    free(onMouseButtonUp_handlers);
    onMouseWheel_handlers_amount = 0;
    onMouseMove_handlers_amount = 0;
    onMouseButtonDown_handlers_amount = 0;
    onMouseButtonUp_handlers_amount = 0;
}

BOOL mousehook_subscribe_onMouseWheel(mousewheel_event handler)
{
    for (size_t i = 0; i < onMouseWheel_handlers_amount; i++)
    {
        if (!onMouseWheel_handlers[i])
        {
            onMouseWheel_handlers[i] = handler;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_unsubscribe_onMouseWheel(mousewheel_event handler)
{
    for (size_t i = 0; i < onMouseWheel_handlers_amount; i++)
    {
        if (onMouseWheel_handlers[i] == handler)
        {
            onMouseWheel_handlers[i] = NULL;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_subscribe_onMouseMove(mousemove_event handler)
{
    for (size_t i = 0; i < onMouseMove_handlers_amount; i++)
    {
        if (!onMouseMove_handlers[i])
        {
            onMouseMove_handlers[i] = handler;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_unsubscribe_onMouseMove(mousemove_event handler)
{
    for (size_t i = 0; i < onMouseMove_handlers_amount; i++)
    {
        if (onMouseMove_handlers[i] == handler)
        {
            onMouseMove_handlers[i] = NULL;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_subscribe_onMouseButtonDown(mousebutton_event handler)
{
    for (size_t i = 0; i < onMouseButtonDown_handlers_amount; i++)
    {
        if (!onMouseButtonDown_handlers[i])
        {
            onMouseButtonDown_handlers[i] = handler;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_unsubscribe_onMouseButtonDown(mousebutton_event handler)
{
    for (size_t i = 0; i < onMouseButtonDown_handlers_amount; i++)
    {
        if (onMouseButtonDown_handlers[i] == handler)
        {
            onMouseButtonDown_handlers[i] = NULL;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_subscribe_onMouseButtonUp(mousebutton_event handler)
{
    for (size_t i = 0; i < onMouseButtonUp_handlers_amount; i++)
    {
        if (!onMouseButtonUp_handlers[i])
        {
            onMouseButtonUp_handlers[i] = handler;
            return 0;
        }
    }
    return 1;
}

BOOL mousehook_unsubscribe_onMouseButtonUp(mousebutton_event handler)
{
    for (size_t i = 0; i < onMouseButtonUp_handlers_amount; i++)
    {
        if (onMouseButtonUp_handlers[i] == handler)
        {
            onMouseButtonUp_handlers[i] = NULL;
            return 0;
        }
    }
    return 1;
}