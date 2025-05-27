/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : LCD_3.C
*     PROCESSOR : I8086
*     LCD test
*****************************************/

#define	_LCD			 /*  You must define it,
                                     because using LCD Function in the HeadterFile. */

#include	"mde8086.h"


/*  Input KeyCode.  */
unsigned char key_scan( void )
{
    unsigned char key;

    while( (inportb(KEY) & 0x80 ) );
    key = inportb( KEY ) & 0x1f;
    outportb( KEY, 0 );
    return key;
}

/*
       Integer as Long Output to the LCD.
	    	v     : Output DATA
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

    LCD_puts( temp1 );			

}

void	main( void )
{
    unsigned char  keycode;

    LCD_init;

    LCD_puts( "   Key Code" );
    do  {
       LCD_Iout( 0xc0 + 7 );
       keycode = key_scan();
       LCD_Lintput( keycode, 2, 16 );
    } while(1);

}
