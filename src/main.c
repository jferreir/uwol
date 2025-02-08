#include <stdio.h>
#include <conio.h>
#include <graph.h>

int main() 
{
    int color;
    char buf[512];
    long size;

    _setvideomode(_MRES256COLOR);

    for (color = 0; color < 256; color++)
    {
        _setcolor(color);
        _setpixel(color, 0);
    }

    for (color = 0; color < 512; color++)
    {
        buf[color] = 0;
    }

    _getimage( 0, 0, 255, 0, buf );
    size =  _imagesize( 0, 0, 255, 0 );

    getch();
    _setvideomode(_DEFAULTMODE);
    printf ("Image size %ld\n", size);
    for (color = 0; color < size; color+=8)
    {
        printf("%02x %02x %02x %02x %02x %02x %02x %02x ", buf[color], buf[color+1], buf[color+2], buf[color+3],
                                                                    buf[color+4], buf[color+5], buf[color+6], buf[color+7]);
        color +=8;
        printf("%02x %02x %02x %02x %02x %02x %02x %02x\n", buf[color], buf[color+1], buf[color+2], buf[color+3],
                                                                    buf[color+4], buf[color+5], buf[color+6], buf[color+7]);
    }

    return 0;
}

// Mode 0x12, 4 bitplanes, 16 colors
// 0000 0000 1111 1111
// 0000 1111 0000 1111
// 0011 0011 0011 0011
// 0101 0101 0101 0101
// 0123 4567 89AB CDEF


// Mode 0x13, 1 bitplane, 256 color, 8bits/pixel
// size 256+6
// 01 00
// 00 01
// 00 08
// 00 01 02 03 04 05 06 07
// 08 09 0A 0B 0C 0D 0E 0F