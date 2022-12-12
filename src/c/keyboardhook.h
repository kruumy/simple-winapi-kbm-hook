#pragma once

typedef void (*key_event)(int);

BOOL keyboardhook_enable(size_t max_onKeyDown_handlers, size_t _onKeyUp_handlers_amount);

void keyboardhook_disable();

BOOL keyboardhook_subscribe_onKeyDown(key_event handler);

BOOL keyboardhook_subscribe_onKeyUp(key_event handler);

BOOL keyboardhook_unsubscribe_onKeyDown(key_event handler);

BOOL keyboardhook_unsubscribe_onKeyUp(key_event handler);
