/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : SPEAK_1.C
*     PROCESSOR : I8086
*     Sound test
*     Press keypad 0 to F
*****************************************/

#include	"mde8086.h"

unsigned int   FREQ_TBL[] = {
                     0xb2, 0xa8, 0x96, 0x85, 0x7a, 0x70,
                     0x64, 0x59, 0x54, 0x4a, 0x42, 0x3e,
                     0x37, 0x31, 0x2c, 0x29
                };
char	scan( void )
{
	char	ch;

        do  {
           ch = inportb( KEY );
           if( !(ch & 0x80 ) && !(ch & 0x10 ) ) break;
        } while( 1 );

        outportb( KEY, 0 );

        return ch & 0x0f;
}


void    main(void)
{
     unsigned int    	*ptr;
     unsigned char	sp;
     int   	i, k;
     int	ch;
     long	j;

     outportb( KEY, 0 );

     do {
        ch = scan();
        sp = 0xff;
        for( i = 0; i < 30; i ++ ) {
            outportb( SPK, sp );
            for( j = 0;  j <= FREQ_TBL[ch];  j++ );
            sp ^= 0x01;
        }
        outportb( SPK, 0 );
    }while(1);
}


