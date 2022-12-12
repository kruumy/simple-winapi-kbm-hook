#include "mouse.hpp"
#include <map>
#include <Windows.h>

static std::map<const void*, iohook::mouse::events> mouse_handlers{};

static HHOOK mouse_hook;

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
                for (const auto& h : mouse_handlers)
                    if (h.second == iohook::mouse::OnMouseScroll)
                    {
                        reinterpret_cast<iohook::mouse::OnEvent>(h.first)(1);
                    }
            }
            else
            {
                for (const auto& h : mouse_handlers)
                    if (h.second == iohook::mouse::OnMouseScroll)
                    {
                        reinterpret_cast<iohook::mouse::OnEvent>(h.first)(0);
                    }
            }
            break;
        case WM_MOUSEMOVE:
            if (pMouseStruct != NULL)
            {
                for (const auto& h : mouse_handlers)
                    if (h.second == iohook::mouse::OnMouseMove)
                    {
                        reinterpret_cast<iohook::mouse::OnMoveEvent>(h.first)(pMouseStruct->pt.x, pMouseStruct->pt.y);
                    }
            }
            break;
        case WM_LBUTTONDOWN:
            for (const auto& h : mouse_handlers)
                if (h.second == iohook::mouse::OnMouseButtonDown)
                {
                    reinterpret_cast<iohook::mouse::OnEvent>(h.first)(0);
                }
            break;
        case WM_RBUTTONDOWN:
            for (const auto& h : mouse_handlers)
                if (h.second == iohook::mouse::OnMouseButtonDown)
                {
                    reinterpret_cast<iohook::mouse::OnEvent>(h.first)(1);
                }
            break;
        case WM_LBUTTONUP:
            for (const auto& h : mouse_handlers)
                if (h.second == iohook::mouse::OnMouseButtonUp)
                {
                    reinterpret_cast<iohook::mouse::OnEvent>(h.first)(0);
                }
            break;
        case WM_RBUTTONUP:
            for (const auto& h : mouse_handlers)
                if (h.second == iohook::mouse::OnMouseButtonUp)
                {
                    reinterpret_cast<iohook::mouse::OnEvent>(h.first)(1);
                }
            break;
        }
        return 0;
    }
    return CallNextHookEx(mouse_hook, nCode, wParam, lParam);
}

void iohook::mouse::enable()
{
    mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, mousehook_proc, NULL, 0);
}

void iohook::mouse::disable()
{
	UnhookWindowsHookEx(mouse_hook);
    mouse_handlers.clear();
}

void iohook::mouse::subscribe(iohook::mouse::events event, const OnEvent& func)
{
    mouse_handlers[func] = event;
}

void iohook::mouse::subscribe(iohook::mouse::events event, const OnMoveEvent& func)
{
    mouse_handlers[func] = event;
}

void iohook::mouse::unsubscribe(const OnEvent& func)
{
    mouse_handlers.erase(func);
}

void iohook::mouse::unsubscribe(const OnMoveEvent& func)
{
    mouse_handlers.erase(func);
}
