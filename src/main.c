#include <conio.h>
#include <graph.h>

#include "vga.h"

int main() 
{
    VGA_SetVideoMode_320x240();

    getch();
    _setvideomode(_DEFAULTMODE);

    return 0;
}
