/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8251A_1.C             *
*     PROCESSOR : I8086                  *
*     Echo back program (UART Interrupt) *
*****************************************/

#include	"mde8086.h"

#define	INT_V	0x43

unsigned char	rxbuf;
int		rxflag;

void	_8251_int( void )
{
    INTERRUPT_IN;

    if( inportb( UARTC ) & 0x02 )   {		/* Consent Recive */
       rxflag = 1;
       rxbuf = inportb( UARTD );
    }
    else if( inportb( UARTC ) & 0x01 )  {	/* Consent Transmit */
       if( rxflag ) {
           outportb( UARTD, rxbuf );
           rxflag = 0;
       }
    }
    /* EOI Command */
    outportb( INTA, 0X20 );
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

void	main( void )
{
    int	i;
    unsigned char	v;

    unsigned long far *intvect_ptr;

    intvect_ptr = ((unsigned long far *)0);

    asm CLI;
    /* Init 8259 */
    outportb( INTA, 0x1b );      /* ICW1                  */
    outportb( INTA2, 0x40 );     /* ICW2 interrupt Vector */
    outportb( INTA2, 0x01 );     /* ICW4                  */

    outportb( INTA2, 0xf7 );     /* interrupt mask        */

    /* init 8253 */
    outportb( PIT_CR, 0x36 );
    outportb( PIT_CNT0, 16 );
    outportb( PIT_CNT0, 0 );

    /* init 8251 */
    outportb( UARTC, 0x40 );
    for( i = 0;  i < 3;  i++ ) outportb( UARTC, 0 );
    outportb( UARTC, 0x40 );
    outportb( UARTC, 0x4e );	/* 8251 mode */
    outportb( UARTC, 0x27 );	/* 8251 command */
    inportb( UARTD );

    /* init Interrupt vector table */
    *(intvect_ptr+INT_V) = ( unsigned long )_8251_int;
    rxflag = 0;
    asm STI;
    while(1);
}

