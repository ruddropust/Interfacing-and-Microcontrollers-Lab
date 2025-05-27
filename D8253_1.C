/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8253_1.C
*     PROCESSOR : I8086
*     8253 Test
*****************************************/
#include    "mde8086.h"

#define	INT_V	0x41		/* Interrupt vector */

unsigned char	led;

/* Process Interrupt Function  */
void	_8253_int( void )
{
    INTERRUPT_IN;

    outportb( PPI1_B, led );
    led = (led << 1);
    if( led & 0x10 )  led = 0xf1;

    outportb( PIT_CNT2, 10 );
    outportb( PIT_CNT2, 0 );

    /* EOI Command */
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



void    main( void )
{
    unsigned long far *intvect_ptr = ((unsigned long far *)0 );

    /* 8255 INIT */
    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_B, 0xf0 );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_C, 0x20 );

    /* Init 8259 */
    outportb( INTA, 0x13 );      /* ICW1                  */
    outportb( INTA2, 0x40 );     /* ICW2 interrupt Vector */
    outportb( INTA2, 0x01 );     /* ICW4                  */
    outportb( INTA2, 0xfd );     /* interrupt mask        */


    /* Init 8253 */
    outportb( PIT_CR, 0x76 );    /* Counter 1 mode 3 */
    outportb( PIT_CR, 0xb0 );    /* Counter 2 mode 0 */

    outportb( PIT_CNT2, 10 );    /* Counter 2 Time Constant */
    outportb( PIT_CNT2, 0 );
    outportb( PIT_CNT1, 0x00 );  /* Counter 1 Time Constant */
    outportb( PIT_CNT1, 0x80 );

    /* init Interrupt vector table */
    *(intvect_ptr + INT_V ) = (unsigned long )_8253_int;

    asm STI;

    led = 0xf1;
    while(1);
}
