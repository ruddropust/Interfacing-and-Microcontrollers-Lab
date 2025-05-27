/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8259.C
*     PROCESSOR : I8086
*     8259 TEST
*     Description : Press IR2 button
*****************************************/
#include	"mde8086.h"

void    wait( long del )
{
    while( del-- );
}

void    init8259(void)
{
    outportb( INTA, 0x13 );
    outportb( INTA2, 0x40 );
    outportb( INTA2, 0x01 );
    outportb( INTA2, 0xfb );
}

void    main(void)
{
    int     led = 0xf1;

    init8259();
    /* INIT 8255 */
    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_C, 0x00 );
    outportb( PPI1_B, led );
    do{
        outportb( INTA, 0x0c );
        while( !(inportb(INTA) & 0x80) )
        {
            outportb( INTA, 0x0c );
        }
        wait(10000);
        led = led << 1;
        if( led & 0x10 ) led = 0xf1;
        else {
            led = led | 0xf0;
        }
        outportb( PPI1_B, led );
        outportb( INTA, 0x20 );
    }while(1);
}


