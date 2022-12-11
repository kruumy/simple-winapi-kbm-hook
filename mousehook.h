#pragma once

typedef void (*mousebutton_event)(int);
typedef void (*mousewheel_event)(int);
typedef void (*mousemove_event)(int, int);

BOOL mousehook_enable(size_t max_onMouseWheel_handlers, size_t max_onMouseMove_handlers, size_t max_onMouseButtonDown_handlers, size_t max_onMouseButtonUp_handlers);

void mousehook_disable();

BOOL mousehook_subscribe_onMouseWheel(mousewheel_event handler);

BOOL mousehook_unsubscribe_onMouseWheel(mousewheel_event handler);

BOOL mousehook_subscribe_onMouseMove(mousemove_event handler);

BOOL mousehook_unsubscribe_onMouseMove(mousemove_event handler);

BOOL mousehook_subscribe_onMouseButtonDown(mousebutton_event handler);

BOOL mousehook_unsubscribe_onMouseButtonDown(mousebutton_event handler);

BOOL mousehook_subscribe_onMouseButtonUp(mousebutton_event handler);

BOOL mousehook_unsubscribe_onMouseButtonUp(mousebutton_event handler);
