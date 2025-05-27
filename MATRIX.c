/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : MATRIX.C
*     PROCESSOR : I8086
*     DOT MATRIX test
*****************************************/

#include	"mde8086.h"

void    wait(long del)
{
    while( del-- );
}

void    main(void)
{
    int     dot,i;

    /* 8255 Initialization */
    outportb( PPI2_CR, 0x80 );
    outportb( PPI2_A, 0xff );
    outportb( PPI2_C, 0xff );

    do{
        dot = 0x7f;
        for( i = 0; i != 8; i++ ){
           outportb( PPI2_B, dot );
           dot  >>= 1;
           dot = ( dot | 0x80 );
           wait(30000);
        }
    }while(1);
}

