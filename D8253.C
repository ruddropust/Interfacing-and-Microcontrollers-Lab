/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8253.C
*     PROCESSOR : I8086
*     8253 Test
*****************************************/

#include        "mde8086.h"

#define         INT_V       0x40	/* interrupt vector */

unsigned char   led;

/* Process Interrupt Function */
void    int_ser(void)
{
    INTERRUPT_IN;

    led = led << 1;
    if( led == 0x10 ) led = 0x01;

    outportb( PPI1_B, led );
    outportb( PIT_CNT1, 0xff );
    outportb( PIT_CNT1, 0xff );

    outportb( INTA, 0x20 );		/* eoi Command */

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
    unsigned long far *intvect_ptr = ( (unsigned long far *)0 );
    /* Init 8259 */
    outportb( INTA, 0x13 );      /* ICW1                  */
    outportb( INTA2, 0x40 );     /* ICW2 interrupt Vector */
    outportb( INTA2, 0x01 );     /* ICW4                  */
    outportb( INTA2, 0xfe );     /* interrupt mask        */

    led = 0x01;                  

    /* 8253 INIT */
    outportb( PIT_CR, 0x70 );      /* control word */
    outportb( PIT_CNT1, 0xff );    /* Time Constant */
    outportb( PIT_CNT1, 0xff );

    /* Init 8255 port */
    outportb( PPI1_CR, 0x80 );    /* all port is output */
    outportb( PPI1_A, 0xff );     /* Init A port        */
    outportb( PPI1_C, 0x00 );     /* Init B port        */
    outportb( PPI1_B, led );      

    /* init Interrupt vector table */
    *(intvect_ptr + INT_V ) = (unsigned long)int_ser;
    asm STI;
    while(1);
}

