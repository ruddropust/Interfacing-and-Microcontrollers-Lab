/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8259.C
*     PROCESSOR : I8086
*     8259 TEST
*     Description : Press IR2 button
*****************************************/
#include        "mde8086.h"

#define         INT_V	0x42

int     data[11] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92,
                     0x82, 0xf8, 0x80, 0x90, 0x00 };
int     index = 0;

void    wait(long del)
{
    while( del-- );
}
/* Process Interrupt Routine */
void    int_ser(void)
{
    INTERRUPT_IN;
    index ++;
    if( index >= 10 )  index = 0;
    outportb( PPI1_A, data[index] );

	/* eoi command */
    outportb( INTA, 0x20 );

    asm  pop  ds;
    asm  pop  es;
    asm  pop  dx;
    asm  pop  cx;
    asm  pop  bx;
    asm  pop  ax;
    asm  pop  di;
    asm  pop  si;
    asm  iret;

}

void    main(void)
{
    unsigned long far *intvect_ptr;

    intvect_ptr = ((unsigned long far *)0);
    /* Init 8259 */
    asm CLI;
    outportb( INTA, 0x13 );      /* ICW1                  */
    outportb( INTA2, 0x40 );     /* ICW2 interrupt Vector */
    outportb( INTA2, 0x01 );     /* ICW4                  */
    outportb( INTA2, 0xfb );     /* interrupt mask        */

	/* 8255 Initial */
    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_B, 0xf0 );
    outportb( PPI1_C, 0x00 );
    outportb( PPI1_A, 0xc0 );

	/* Define Interrupt Vector Table */
    *(intvect_ptr+INT_V) = ( unsigned long )int_ser;
    asm     STI;
    while(1);
}
