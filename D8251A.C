/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : D8251A.C
*     PROCESSOR : I8086
*     Echo back program (Polling)
*****************************************/
#include	"mde8086.h"

/*  Recive One Character */
unsigned char	read_8251( void )
{
	while( !(inportb( UARTC ) & 0x02) );	/* rxd Test */
    return inportb( UARTD );
}

/* Transmit One Character */
void	write_8251( unsigned char v )
{
	while( !(inportb( UARTC ) & 0x01) );	/* txd Test */
    outportb( UARTD, v );
}
void	main( void )
{
     int	i;
     unsigned char	v;

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

     do {
           v = read_8251();
           write_8251( v );
     } while(1);
}
