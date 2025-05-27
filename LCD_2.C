/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : LCD_2.C
*     PROCESSOR : I8086
*     LCD test
*****************************************/

#define	_LCD			

#include	"mde8086.h"

/*  To the LCD Output String ( Delay One Character ) */
void	string( char *str )
{
    while( *str )  {
        LCD_putch( *str );
        str ++;
        wait( 10000 );
    }
}

void	main( void )
{
    LCD_init;

    LCD_Iout( 0x07 )		/* Entry mode define*/
    do  {
       LCD_Iout( 0x90 )	/* Character Output Position */
       string( "MDA-Win8086 Training Kit" );
    } while(1);

}

