/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : STEPMO_1.C
*     PROCESSOR : I8086
*	  Stepping Motor Control             *
*
*     -- Function --
*     Keypad 0 : LEFT 45
*     Keypad 1 : RIGHT 45
*     Keypad 2 : LEFT 90
*     Keypad 3 : RIGHT 90
*     Keypad 4 : LEFT 180
*     Keypad 5 : RIGHT 180
*     Keypad 6 : LEFT
*     Keypad 7 : RIGHT
*****************************************/

#define		_LCD
#include	"mde8086.h"

#define         INT_V       0x40	/* interrupt vector */

unsigned char	step_tbl[4] = {
		   0xc0, 0x90, 0x30, 0x60
                };

/* Global a Variable */
int	step;
unsigned int	p_cnt;
int	rl_flag;
unsigned int  spd_buf;

/* Process 8253 Interrupt Routine */
void    int_ser(void)
{
    INTERRUPT_IN;

    if( !p_cnt ) goto exit_svr;

    if( p_cnt != 0xffff ) p_cnt --;
    if( rl_flag == 'L' )  {
       step++;
       if( step >= 4 ) step = 0;
    }
    else {
       step--;
       if( step < 0 ) step = 3;
    }

    outportb( PPI1_B, step_tbl[step] );

exit_svr:;
    outportb( PIT_CNT1, spd_buf*0xff );		/* Repeat Initial 8253 Time Constant */
    outportb( PIT_CNT1, (spd_buf>>8)&0xff );

    outportb( INTA, 0x20 );

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

/*  Key Scan */
unsigned char key_scan( void )
{
    unsigned char key;

    while( (inportb(KEY) & 0x80 ) );

    key = inportb( KEY ) & 0x1f;
    outportb( KEY );

    return key;
}


void	l_45( void )
{
    p_cnt = 25;
    rl_flag = 'L';
    LCD_LN21;
    LCD_puts( "Left 45 defree! " );
}

void	r_45( void )
{
    p_cnt = 25;
    rl_flag = 'R';
    LCD_LN21;
    LCD_puts( "Right 45 defree!" );
}

void	l_90( void )
{
    p_cnt = 50;
    rl_flag = 'L';
    LCD_LN21;
    LCD_puts( "Left 90 defree! " );
}

void	r_90( void )
{
    p_cnt = 50;
    rl_flag = 'R';
    LCD_LN21;
    LCD_puts( "Right 90 defree!" );
}

void	l_180( void )
{
    p_cnt = 100;
    rl_flag = 'L';
    LCD_LN21;
    LCD_puts( "Left 180 defree " );
}

void	r_180( void )
{
    p_cnt = 100;
    rl_flag = 'R';
    LCD_LN21;
    LCD_puts( "Right 180 defree" );
}

void	l_rev( void )
{
    p_cnt = 0xffff;
    rl_flag = 'L';
    LCD_LN21;
    LCD_puts( "Left Revolution " );
}

void	r_rev( void )
{
    p_cnt = 0xffff;
    rl_flag = 'R';
    LCD_LN21;
    LCD_puts( "Right Revolution" );
}



void    main(void)
{
    unsigned long far *intvect_ptr;

    intvect_ptr = ((unsigned long far *)0);

    LCD_init;

    /* Init 8259 */
    outportb( INTA,  0x13 );      /* ICW1 */
    outportb( INTA2, 0x40 );     /* ICW2 interrupt Vector */
    outportb( INTA2, 0x01 );     /* ICW4 */
    outportb( INTA2, 0xfe );     /* interrupt mask */

    step = 0;
    p_cnt = 0;
    spd_buf = 30000;

    /* 8253 INIT */
    outportb( PIT_CR, 0x70 );      /* control word */
    outportb( PIT_CNT1, spd_buf & 0xff );      
    outportb( PIT_CNT1, (spd_buf >> 8)&0xff );

    /* Init 8255 port */
    outportb( PPI1_CR, 0x80 );    /* all port is output */
    outportb( PPI1_A, 0xff );
    outportb( PPI1_C, 0x00 );
    outportb( PPI1_B, 0 );

    *(intvect_ptr+INT_V) = ( unsigned long )int_ser;
    asm STI;

    LCD_puts( "Stepping Control" );
    LCD_LN21;
    LCD_puts( "Press 0 - 7 key" );

    outportb( KEY, 0);
    do  {
       switch( key_scan() )  {
          case 0 : l_45();  break;
          case 1 : r_45();  break;
          case 2 : l_90();  break;
          case 3 : r_90();  break;
          case 4 : l_180();  break;
          case 5 : r_180();  break;
          case 6 : l_rev();  break;
          case 7 : r_rev();  break;
       }

    } while( 1 );

}

