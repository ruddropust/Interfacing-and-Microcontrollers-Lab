/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : MATRIX_2.C
*     PROCESSOR : I8086
*     DOT MATRIX test
*****************************************/
#include	"mde8086.h"

/* Output Font 'A' */
int     font[8] = { 0xff, 0xc0, 0xb7, 0x77,
                    0x77, 0xb7, 0xc0, 0xff };

void    wait(long del)
{
    while( del-- );
}

void    main(void)
{
    int     *data;
    int     common, i;

    outportb( PPI2_CR, 0x80 );
    outportb( PPI2_A, 0xff );

    do{
        data = font;
        common = 0x01;
        for( i = 0; i != 8; i++ ) {
            outportb( PPI2_C, common );
            outportb( PPI2_B, *data );
            wait(120);
            data++;
            common = common << 1;
        }
    }while(1);
}


