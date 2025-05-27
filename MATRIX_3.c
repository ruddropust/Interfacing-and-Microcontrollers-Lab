/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : MATRIX_3.C
*     PROCESSOR : I8086
*     DOT MATRIX test
*****************************************/

#include	"mde8086.h"

/* Output Font 'A' */
int     font1[8] = { 0xff, 0xff, 0xff, 0xff,
                     0xff, 0xff, 0xff, 0xff };

int     font2[8] = { 0xc0, 0xff, 0xff, 0xff,
                     0xff, 0xff, 0xff, 0xff };

int     font3[8] = { 0xb7, 0xc0, 0xff, 0xff,
                     0xff, 0xff, 0xff, 0xff };

int     font4[8] = { 0x77, 0xb7, 0xc0, 0xff,
                     0xff, 0xff, 0xff, 0xff };

int     font5[8] = { 0x77, 0x77, 0xb7, 0xc0,
                     0xff, 0xff, 0xff, 0xff };

int     font6[8] = { 0xb7, 0x77, 0x77, 0xb7,
                     0xc0, 0xff, 0xff, 0xff };

int     font7[8] = { 0xc0, 0xb7, 0x77, 0x77,
                     0xb7, 0xc0, 0xff, 0xff };

int     font8[8] = { 0xff, 0xc0, 0xb7, 0x77,
                     0x77, 0xb7, 0xc0, 0xff };

void    wait(long del)
{
    while( del-- );
}

void    display( int *data1 )
{
    int     *data;
    int     common, i, k;
    for( k = 0; k != 20; k++ ){
        common = 0x01;
        data = data1;
        for( i = 0; i != 8; i++ )  {
            
           outportb( PPI2_C, common );
           outportb( PPI2_B, *data );
           wait(120);
           data++;
           common = common << 1;
        }
    }
}

void    main(void)
{

    outportb( PPI2_CR, 0x80 );
    outportb( PPI2_A, 0xff );

    do{
        display(font1);
        display(font2);
        display(font3);
        display(font4);
        display(font5);
        display(font6);
        display(font7);

        display(font8);
        display(font8);
        display(font8);
    } while(1);
}

