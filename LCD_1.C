/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : LCD_1.C
*     PROCESSOR : I8086
*     LCD test
*****************************************/

#define _LCD            /*  You must define it,
                            because using LCD Function in the HeadterFile. */
#include	"mde8086.h"

void	main( void )
{
    int	i;

    LCD_init;

    do  {
       LCD_ALLCLR;
       LCD_puts( "Serial monitor !" );
       LCD_LN21;
       LCD_puts( "MDA-Win8086 Kit!" );

       for( i = 0;  i < 16;  i ++ )  {
           wait( 15000 );
           LCD_RShift;              /* Right shift */
       }
    } while(1);
}

