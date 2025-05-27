/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : SPEAK.C
*     PROCESSOR : I8086
*     Sound test
*****************************************/

#include	"mde8086.h"

#define     PER         0x0c

unsigned char     FREQ_TAB[24] = { 0x25, 0x27, 0x29, 0x2c, 0x2e, 0x31,
                         0x34, 0x37, 0x3b, 0x3e, 0x42, 0x46,
                         0x4a, 0x4f, 0x54, 0x59, 0x5e, 0x64,
                         0x6a, 0x70, 0x77, 0x7e, 0x85, 0xff};

void    main(void)
{
     unsigned char   *ptr;
     unsigned char   i,j,k;

     do {
        ptr = FREQ_TAB;
        while( *ptr != 0xff )
            {
                j =  PER;
                k = 0xff;                                                                                                  j = PER;
                while(  j != 0x00 )  {
                    outportb( SPK, k );
                    for( i = *ptr; i > 0x00 ; i -- );
                    k = k ^ 0x01;
                    j --;
                }
                ptr++;
            }
    }while(1);
}


