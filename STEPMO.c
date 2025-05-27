/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : STEPMO.C
*     PROCESSOR : I8086
;*	  Stepping Motor Test 1		 *
;*		-- 1 Phase Magnetization *
*****************************************/

#include	"mde8086.h"

void    wait( long del )
{

    while( del-- );
}

/* Output Pulse Table to the Motor. */
unsigned char	step_tbl[4] = {
		   0xe0, 0xd0, 0xb0, 0x70
                };

void    main( void )
{
    unsigned char step;

    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_B, 0xff );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_C, 0X20 );

    step = 0;
    do  {
       outportb( PPI1_B, step_tbl[step++] );
       if( step >= 4 )  step = 0;
       wait( 100 );
    } while( 1);
}
