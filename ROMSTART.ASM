		NAME    STARTUP
		PAGE    60,132
;/*------------------------------------------------------------*/
;/*                                                            */
;/*            STARTUP.ASM -- Start up code (SMALL)            */
;/*           = = = = = = = = = = = = = = = = = = =            */
;/*                                                            */
;/*               Borland C Run time library                   */
;/*                                                            */
;/*                     by Midas Eng. Co., Ltd.                */
;/*                                                            */
;/*------------------------------------------------------------*/

RAM_SEG         EQU     0040H           ; RAM Segment
PRG_OFFSET      EQU     0000H           ; PROGRAM offset
STACK_SIZE	EQU	2048		; Stack size

; Define segment

_TEXT   SEGMENT BYTE PUBLIC 'CODE'
_TEXT   ENDS

_DATA   SEGMENT WORD PUBLIC 'DATA'
_DATA   ENDS

_BSS    SEGMENT WORD PUBLIC 'BSS'
_BSS    ENDS

_BSSEND SEGMENT BYTE PUBLIC 'STACK'
_BSSEND ENDS

DGROUP  GROUP   _DATA, _BSS, _BSSEND


        ASSUME  CS:_TEXT, DS:DGROUP, ES:DGROUP, SS:DGROUP


_TEXT   SEGMENT

STARTX  PROC    NEAR
        ORG     PRG_OFFSET
RST_START:
	;  세스면트 레지스터값 설정
        mov     ax,RAM_SEG           ;
        mov     es,ax                       ; set to ram area
	mov	ss,ax
        lea	bx,DGROUP:edata@
        add	bx,STACK_SIZE
        mov     sp,bx	; SET STACK POINTER

	mov	dx,DGROUP	; DX := GROUP Segment address

; 프로그램 영역(ROM)에 있는 초기화된 변수를 RAM영역으로 복사
;
	mov	ds,dx
	mov	si,offset DGROUP:adata@
	mov	di,si
	mov	cx,offset DGROUP:bdata@
	sub	cx,si
	cld			; auto incremant
	rep	movsb

        mov     ds,ax           ; DS to ram area.

; Reset uninitialized data area
        xor     ax,ax
        mov     di,offset DGROUP:bdata@
        mov     cx,offset DGROUP:edata@
        sub     cx,di
        jz      STARTX1
        rep     stosb
STARTX1:
        extrn   _main:near
        call     _main
        cli
        jmp     $

STARTX  ENDP

_TEXT   	ENDS

		SUBTTL  Start up data area
		PAGE

_DATA   	SEGMENT
adata@          label   byte
_DATA   	ENDS

_BSS    	SEGMENT
bdata@          label   byte
_BSS    	ENDS

_BSSEND 	SEGMENT
edata@          label   byte
_BSSEND 	ENDS

        END
