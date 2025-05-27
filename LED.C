/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : LED.C
*     PROCESSOR : I8086
*	  8255 test
*****************************************/
#include	"mde8086.h"

void    wait( long del )
{
    while( del-- );
}

void    main( void )
{
    unsigned char led;

    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_B, 0xff );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_C, 0X20 );

    led = 0xf1;
    do  {
       outportb( PPI1_B, led );
       led = led << 1;
       if( led & 0x10 )  led = 0xf1;
       wait( 10000 );
    } while( 1);
}
