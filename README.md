## Example Usage
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
Of course there are more events than just the ones listed above.
You can also subscribe multiple functions to the same action if you increase the amount to allocate in enable functions.





