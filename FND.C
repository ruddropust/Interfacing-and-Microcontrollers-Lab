/*****************************************
*     MDE-Win8086 EXPERIMENT PROGRAM     *
*     FILENAME  : FND.C
*     PROCESSOR : I8086
*     8255 TEST
*****************************************/
#include	"mde8086.h"

int     data[11] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92,
                 0x82, 0xf8, 0x80, 0x90, 0x00 };

void    wait(long del)
{
        while( del-- );
}

void    main(void)
{
    int     *data1;

    outportb( PPI1_CR, 0x80 );
    outportb( PPI1_B, 0xf0 );
    outportb( PPI1_C, 0x00 );

    do {
        data1 = data;

        while( *data1 != 0x00 ){
                outportb( PPI1_A, *data1 );
                wait(30000);
                data1++;
        }
    }while(1);
}

