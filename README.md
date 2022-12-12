## Example C Usage
```
#include "keyboardhook.h"
#include "mousehook.h"

void onMouseMove(int x, int y)
{
    // something
}

void onMouseButtonDown(int btn)
{
   if(btn == 0)
   {
      // left mouse btn
   }
   else if(btn == 1)
   {
      // right mouse btn
   }
}

void onKeyDown(int vkCode)
{
    // something
}

int main()
{
    mousehook_enable(0,1,1,0);
    mousehook_subscribe_onMouseMove(onMouseMove); 
    mousehook_subscribe_onMouseButtonDown(onMouseButtonDown); 
    
    keyboardhook_enable(1,0);
    keyboardhook_subscribe_onKeyDown(onKeyDown);
    
    mousehook_disable();
    keyboardhook_disable();
}

```
## Example C++ Usage 
Note: More overhead because of use of std::map so you do not need to manually allocate.
```
#include "iohook/keyboard.hpp"
#include "iohook/mouse.hpp"

void OnMouseScroll(int dir)
{
   if(dir == 0)
   {
      // scroll down
   }
   else if(btn == 1)
   {
      // scroll up
   }
}

void OnKeyUp(int vkCode)
{
    // something
}

int main()
{
    iohook::mouse::enable();
    iohook::mouse::subscribe(iohook::mouse::OnMouseScroll, OnMouseScroll); 
    
    iohook::keyboard::subscribe(iohook::keyboard::OnKeyUp, OnKeyUp);
    
    iohook::mouse::disable();
    iohook::keyboard::disable();
}

```






