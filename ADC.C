/****************************************
*     MDE-8086 EXPERIMENT PROGRAM       *
*	  FILENAME  : ADC.C                 *
*     PROCESSOR : I8086                 *
*	  Volt Meter		                *
*****************************************/

#define		_LCD
#include    "mde8086.h"

/* Output Fixed Point
	v     : Output Data
	max   : Output Location( Integer Inclusion )
	point : Point Location
*/

void	LCD_putf( long v, int max, int point )
{
    char  temp[20];
    char  temp1[20];
    int	  len, i;

    ltoa( v, temp, 10 );		
    memset( temp1, '0', max );	
    temp1[max] = 0;

    len = strlen( temp );		
    memmove( temp1+(max-len), temp, len );

    /* Output Integer */
    for( i = 0;  i < max-point; i ++ )  LCD_putch( temp1[i] );

    LCD_putch( '.' );	
    LCD_puts( temp1+i );	

}

void    main( void )
{
    long	v;
    char	buf[20], temp[10];
	int		i;

    LCD_init;

    LCD_puts( "   Volt Meter" );

    do  {
       outportb( ADC, 0xff);
       wait( 20000 );

       v = inportb(ADC)*(500000l/256);

       v /= 100;
       LCD_Iout( 0xc5 );	

       LCD_putf( v, 4, 3 );
       LCD_puts( " V" );

    } while( 1);

}



