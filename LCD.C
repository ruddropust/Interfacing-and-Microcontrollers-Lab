/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : LCD.C
*     PROCESSOR : I8086
*     LCD test
*****************************************/

#define _LCD            /*  You must define it,
                            because using LCD Function in the HeaderFile. */
#include	"mde8086.h"

/*  To the LCD Output String( Delay One character) */
void    string( char *str )                   
{
    while( *str )  {
        LCD_putch( *str );
        str ++;
        wait( 10000 );
    }
}

void	main( void )
{
    LCD_init;				/* LCD Initial */

    string( "Serial monitor !" );
    LCD_LN21;
    string( "MDA-Win8086 Kit!" );

    do  {
       LCD_DISPOFF;
       wait( 20000 );
       LCD_DISPON;
       wait( 20000 );
    } while(1);

}


