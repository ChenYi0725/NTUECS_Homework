;CF-> CY, AF-> AC, ZF->ZR, SF->PL, OF->OV
INCLUDE Irvine32.inc
;作者:111016011 陳奕
; 程式操作說明: 此程式會對48及35做加減法，會先顯示加法(DAA)的結果，再顯示減法(DAS)
; 自評分數:100分	(包含所有功能且有附上註解)
.data
.code
main PROC		;主程式
	mov al, 35h
	add al, 48h
	call newDAA
	call DumpRegs	;顯示目前情況

	mov al, 48h
	sub al, 35h
	call newDAS
	call DumpRegs
	INVOKE ExitProcess, 0
main ENDP

;==========新函式

newDAA PROC		;仿DAA，能把加法最後以Packed BCD表示，並改動CF、AF旗標
	mov bl, al
	lahf				;把 EFlag 低8bits 送進 AH
	mov cl, ah
	and bl, 00001111b	;只保留後四位
	and cl, 00010000b	;只保留carry
	shr cl,4			;把carry 推到第一位


	.IF bl > 9 || cl == 1	;if(al(lo)>0 or Carry == 1)
		add al, 6
		pushf
		or ah,00010000b		;Carry = 1
		popf
		sahf				;把AH的8bit送到Eflag
	.ELSE
		pushf
		or ah,00000000b		;Carry = 0
		popf
		sahf				;把AH的8bit送到Eflag
	.ENDIF

	lahf					
	mov cl, ah
	and cl, 00000001b

	mov bl, al
	and bl, 11110000b 
	shr bl,4			;把前 4bits移到後 4bits



	.IF bl > 9 || cl == 1 ;if(al > 0 or Carry == 1)
		add al, 60h
		pushf
		or ah, 00000001b	;Carry = 1
		popf
		sahf				;把AH的8bit送到Eflag
	.ELSE
		pushf
		or ah, 00000000b	;Carry = 0
		popf
		sahf				;把AH的8bit送到Eflag
	.ENDIF

ret
newDAA ENDP

;=================DAS

newDAS PROC		;仿DAS，能把減法最後以Packed BCD表示，並改動CF、AF旗標
	mov bl, al
	lahf				;把 EFlag 低8bits 送進 AH
	mov cl, ah
	and bl, 00001111b	;只保留後四位
	and cl, 00010000b	;只保留carry
	shr cl,4			;把carry 推到第一位

	.IF bl > 9 || cl == 1	;if(al(lo)>0 or Carry == 1)
		sub al, 6
		pushf
		or ah,00010000b		;Carry = 1
		popf
		sahf				;把 AH 的 8 bit 送到Eflag
	.ELSE
		pushf
		or ah,00000000b		;Carry = 0
		popf
		sahf				;把 AH 的 8 bits 送到 Eflag
	.ENDIF


	lahf					
	mov cl, ah
	and cl, 00000001b



	.IF al > 9Fh || cl == 1 ;if(al > 0 or Carry == 1)
		sub al, 60h
		pushf
		or ah, 00000001b	;Carry = 1
		popf
		sahf				;把AH 的 8bits 送到 Eflag
	.ELSE
		pushf
		or ah, 00000000b	;Carry = 0
		popf
		sahf				;把AH 的 8bits 送到 Eflag
	.ENDIF

ret
newDAS ENDP


END main