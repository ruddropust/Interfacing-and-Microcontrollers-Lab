/* ==========================================================

	C Include file for MDE-8086

        		by Midas Eng. Co., Ltd.

*/

/*  IO 
*/
#define     PPI1_CR     0x1f	/* 8255 1 ( FND, LED, DA )*/
#define     PPI1_A      0x19
#define     PPI1_B      0x1B
#define     PPI1_C      0x1D

#define     PPI2_CR     0x1e       /* 8255 2 ( DOT )*/
#define     PPI2_C      0x1c
#define     PPI2_B      0x1a
#define     PPI2_A      0x18

#define     UARTD	   0x08		  /* 8251  */
#define     UARTC	   0x0a

#define     PIT_CNT0	   0x09	  /* 8253 */
#define     PIT_CNT1       0x0b
#define     PIT_CNT2	   0x0d
#define     PIT_CR	   0x0f

#define     INTA      0x10	         /* 8259 */
#define     INTA2     0x12

#define     SPK	0x17	   /* Speaker */

#define     ADC	0x18	   /* ADC */

#define     KEY	0x01      /* key board address */


/* Interrupt Service Vector */
#define	    INTERRUPT_IN	\
           asm  push ax;     \
           asm  push bx;     \
           asm  push cx;     \
           asm  push dx;     \
           asm  push es;     \
           asm  push ds


/* --------------------------
	 LCD Control Function and Macro
*/

#ifdef	_LCD

#define	    LCDC	0x00		/* LCD Control Address */
#define	    LCDC_S	0x02
#define	    LCDD	0x04

/* Char. Oup */
#define	    LCD_putch( ch )	{	\
	 while( inportb(LCDC_S) & 0x80 );	\
		outportb( LCDD, ch ); }

/* LCD Command */
#define	    LCD_Iout( cmd )	{	\
	 while( inportb(LCDC_S) & 0x80 );	\
		outportb( LCDC, cmd ); }

/* Busy flag */
#define	    LCD_wait_BF    while( inportb( LCDC_S ) & 0x80 )

/* LCD initialization */
#define	    LCD_init			\
	outportb( LCDC, 0x30 );         \
        wait( 100 );                    \
	outportb( LCDC, 0x30 );         \
        wait( 10 );                     \
	outportb( LCDC, 0x30 );         \
        wait( 5 );                      \
        LCD_wait_BF;                    \
	outportb( LCDC, 0x3c );         \
        LCD_wait_BF;                    \
	outportb( LCDC, 0x06 );         \
        LCD_wait_BF;                    \
	outportb( LCDC, 0x01 );         \
        LCD_wait_BF;                    \
	outportb( LCDC, 0x0c )

/* LCD Control Command */
#define LCD_LN11	LCD_Iout( 0x02 );
#define LCD_LN21	LCD_Iout( 0xc0 )
#define LCD_DISPOFF	LCD_Iout( 0x08 );
#define LCD_DISPON	LCD_Iout( 0x0f );
#define LCD_ALLCLR	LCD_Iout( 0x01 );
#define	LCD_RShift	LCD_Iout( 0x1c );

/* LCD Out */
void	LCD_puts( char *ptr )
{
    while( *ptr )  {
       LCD_putch( *ptr );
       ptr ++;
    }
}

/* 시간 지연 함수 */
void    wait( long del )
{
    while( del-- );
}

#endif

