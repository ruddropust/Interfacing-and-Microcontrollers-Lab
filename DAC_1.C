/*
;*****************************************
;*     MDE-8086 EXPERIMENT PROGRAM       *
;*     Chapter 11-4 (Example 2)          *
;*	DA and AD Test   		 *
;*		DA => AD( Output Valt)   *
;*     PROGRAM BY MiDAS ENGINEERING      *
;*****************************************
	;
        ;	FILENAME  : DAC_1.C
        ;	PROCESSOR : I8086
        ;	VER.      : V1.1
        ;
*/
#define	_LCD
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


/*
       Integer as Long Output LCD.
	    	v     : Output Data
		max   : Output Location
		radix : Radix
*/
void	LCD_Lintput( long v, int max, int radix )
{
    char  temp[20], *ptr;
    char  temp1[20];
    int	  len, i;

    ltoa( v, temp, radix );
    memset( temp1, '0', max );	
    temp1[max] = 0;

    len = strlen( temp );		
    memmove( temp1+(max-len), temp, len );

    for( ptr = temp1; *ptr;  ptr++ ) 
       *ptr = toupper( *ptr );

    LCD_puts( temp1 );			/* Output LCD */

}


void    main( void )
{
    long	v;
    unsigned char	da;

    /* 8255 init */
    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_A, 0xff );
    outportb( PPI1_B, 0xf0 );

    da = 0;
    LCD_init;

    LCD_puts( "   DA     AD" );

    do  {
        outportb( PPI1_C, da );
        LCD_Iout( 0xc0+3 );
        LCD_Lintput( da, 3, 10 );

        /* start adc */
	outportb( ADC, 0);
	wait( 8000 );
	v = inportb(ADC)*(500000l/256);
        v /= 100;
        LCD_Iout( 0xc0 + 8 );
        LCD_putf( v, 4, 3 );
        LCD_puts( " V" );
        da ++;
    } while( 1);

}


