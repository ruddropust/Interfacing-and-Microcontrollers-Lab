/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : MATRIX_1.C
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

    /* 8255 Initial */
    outportb( PPI2_CR, 0x80 );
    outportb( PPI2_A, 0x00 );
    outportb( PPI2_B, 0x00 );

    do{
        dot = 0x01;
        for( i = 0; i != 8; i++ ){
           outportb( PPI2_C, dot );
           dot  <<= 1;
           wait(30000);
        }
    }while(1);
}

