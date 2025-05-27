/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : DAC.C                  *
*     PROCESSOR : I8086                  *
*     DAC test program - level meter     *
*****************************************/
#include	"mde8086.h"

void	wait( int del )
{
    while( del -- );
}

void	main( void )
{
    unsigned char  da;
    /* 8255 init */
    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_B, 0xf0 );
    da = 0;
    do {
    	outportb( PPI1_C, da );		/* Output DA  */
        wait( 10000 );
        da++;
        if( da >= 0x64 ) da = 0;
    } while(1);
}
