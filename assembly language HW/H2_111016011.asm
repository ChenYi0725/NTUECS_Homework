;CF-> CY, AF-> AC, ZF->ZR, SF->PL, OF->OV
INCLUDE Irvine32.inc
;作者:111016011 陳奕
;操作說明:輸入加減乘除及括號的整數運算式, 本程式會列印計算結果
;自評:100(包含所有功能且有附上註解)
.data
stringIn BYTE 100 DUP(0)		;存放輸入
inputNum DWORD 100 DUP(0)		;存放整數
infixArray DWORD 100 DUP(0)		;存放中序式字串
postfixArray DWORD 100 DUP(0)	;存放後序式字串

wordTen WORD 0Ah				;用以x10
stackAmount	DWORD 0				;存放stack中的運算子數量
count DWORD 0					;運算子&運算元數量
temp DWORD 0					;保留數值用
isFirst byte 1					;用以分辨是否為第一個數字
isLastNumber byte 0				;檢查上個是否為數字
inputLength DWORD 0				;輸入長度
parenthesesAmount DWORD 0		;括弧數量，用以平衡inputLength
sum DWORD 0						;答案

outputMsg BYTE "請輸入數字串",0
personalMsg1 Byte "作者:111016011陳奕",0
personalMsg2 Byte "操作說明:輸入加減乘除及括號的整數運算式, 本程式會列印計算結果",0
personalMsg3 Byte "自評:100(包含所有功能且有附上註解)",0

.code
main PROC
	mov edx,OFFSET personalMsg1
	call WriteString
	call Crlf
	mov edx,OFFSET personalMsg2
	call WriteString
	call Crlf
	mov edx,OFFSET personalMsg3
	call WriteString
	call Crlf

	mov edx,OFFSET outputMsg
	call WriteString
	call Crlf

	
	mov edx,OFFSET stringIn			;edx 當輸入的指標
	mov ecx,100
	call ReadString

	mov ebx,OFFSET infixArray		;ebx當infixArray的指針
	mov ecx,eax		;loop 字串長度次	
	mov eax,0



processString:
	inc inputLength				
	movzx edi, byte ptr [edx]	;取得當前字元的ASCII 碼, 並放在edi
	inc edx						;inputString指針往後

	cmp edi,'+'
	jz	isOperator
	cmp edi,'-'
	jz	isOperator
	cmp edi,'*'
	jz	isOperator
	cmp edi,'/'
	jz	isOperator
	cmp edi,'('
	jz	isOperator
	cmp edi,')'
	jz	isOperator
	
	jmp isOperand

isOperator:
	cmp isLastNumber,1
	jz LastIsNumber
	jmp endOfLastIsNumber
	LastIsNumber:
		push edi
		mov edi,' '
		mov [ebx],edi					;存入infixArray
		pop edi
		add ebx,type infixArray		;指針往後
		inc inputLength
	endOfLastIsNumber:
	mov [ebx],edi					;存入infixArray
	add ebx,type infixArray		;指針往後
	mov isLastNumber,0
	jmp endTurnInProcessing
isOperand:
	mov isLastNumber,1
	mov [ebx],edi					;存入infixArray
	add ebx,type infixArray		;指針往後
	jmp endTurnInProcessing

endTurnInProcessing:
	loop processString

	sub ebx,type infixArray
	mov eax,[ebx]

	cmp eax,'+'
	jz	endWithOperator
	cmp eax,'-'
	jz	endWithOperator
	cmp eax,'*'
	jz	endWithOperator
	cmp eax,'/'
	jz	endWithOperator
	cmp eax,'('
	jz	endWithOperator
	cmp eax,')'
	jz	endWithOperator

	add ebx,type infixArray
	mov edi,' '
	mov [ebx],edi
	inc inputLength
endWithOperator:
	
;==============用空格將數字與符號隔開 eg. 21/4 -> 21_/4
;inputLength: 包含空格的長度，infixArray:整理完的陣列的頭

;輸出infixArray
;	mov ebx,OFFSET infixArray	;ebx回到infix的頭
;	mov ecx,inputLength			;遞迴次數
;outputinfix:	
;	mov eax,[ebx]
;	add ebx,4
;	call writeint
;	loop outputinfix
;
;	call crlf
;	call crlf

;忘了pop出來還要比較

;==============以下為轉後序	
	mov eax,0
	mov ebx,OFFSET infixArray	;ebx回到infix的頭
	mov edx,OFFSET postfixArray	;edx到postfix的頭
	mov ecx,0			;遞迴次數			
turnPostfix:	
	mov edi,[ebx]
	add ebx,type infixArray

secondCompare:
	cmp edi,'+'				;if(edi == operator)else直接輸出
	jz	postFixAddAndMinus
	cmp edi,'-'
	jz	postFixAddAndMinus
	cmp edi,'*'
	jz	postFixMulAndDiv
	cmp edi,'/'
	jz	postFixMulAndDiv
	cmp edi,'('
	jz	postFixLP
	cmp edi,')'
	jz	postFixRP				

	jmp postFixNumber		

postFixAddAndMinus:
	mov eax,[esp]		;抓出stack最上面，如果非+-*/則 push進

	cmp eax,'+'
	jz popOperator
	cmp eax,'-'
	jz popOperator
	cmp eax,'*'
	jz popOperator
	cmp eax,'/'
	jz popOperator

	push edi
	inc stackAmount
	
	jmp postfixEndTurn
postFixMulAndDiv:
	mov eax,[esp]		;抓出stack最上面，如果非*/則 push進
	cmp eax,'*'
	jz popOperator
	cmp eax,'/'
	jz popOperator

	push edi
	inc stackAmount

	jmp postfixEndTurn

postFixLP:
	push edi
	inc stackAmount
	add parenthesesAmount,2
	jmp postfixEndTurn

postFixRP:
	mov eax,[esp]		;抓出stack最上面
	
	cmp eax,'('
	jz meetLP
	pop eax			
	dec stackAmount
	mov [edx],eax
	add edx,type postfixArray
	jmp postFixRP
	meetLP:

	jmp postfixEndTurn

postFixNumber:		;直接放入postfix

	mov [edx],edi
	add edx,type postfixArray

	jmp postfixEndTurn
popOperator:
	pop eax			;把stack的top取出，再把手上的放進去
	dec stackAmount
	mov [edx],eax
	add edx,type postfixArray
	jmp secondCompare


	jmp postfixEndTurn
postfixEndTurn:
	inc ecx
	cmp ecx,inputLength
	jnz turnPostfix

	mov ecx,parenthesesAmount 
	;sub stackAmount,ecx
;把剩餘的pop 出來
	mov ecx,stackAmount
popTheRest:
	pop edi
	cmp edi,'('
	jz popLR
	mov [edx],edi
	add edx,type postfixArray
	popLR:
	loop popTheRest
	
	mov ecx,parenthesesAmount	;校正字串長度
	sub inputLength,ecx			

;====================
;確認postfix的內容
;mov edx,offset postfixArray
;mov ecx,inputLength
;opn:
;	mov eax,[edx]
;	call writeint
;	add edx,type postfixArray
;	loop opn
;
;call crlf


;==================計算結果
mov eax,0
mov ebx,0
mov edi,offset postfixArray
mov ecx,inputLength

calculate:
	mov ebx,[edi]
	add edi,type postfixArray	

	cmp ebx,'+'
	jz cAdd
	cmp ebx,'-'
	jz cMinus
	cmp ebx,'*'
	jz cMul
	cmp ebx,'/'
	jz cDiv
	cmp ebx,' '
	jz cSpace
	jmp cNumber
cAdd:
	pop edx
	pop eax
	add eax,edx
	push eax

	mov eax,0
	mov edx,0
	jmp endCalculateTurn
cMinus:
	pop edx
	pop eax
	sub eax,edx
	push eax
	mov eax,0
	mov edx,0
	jmp endCalculateTurn
cMul:
	pop temp
	pop eax
	mul temp
	push eax
	mov eax,0
	mov temp,0
	jmp endCalculateTurn
cDiv:
	pop temp
	pop eax
	div temp
	push eax
	mov eax,0
	mov temp,0
	jmp endCalculateTurn
cSpace:
	push eax
	mov eax,0
	jmp endCalculateTurn
cNumber:
	mul wordTen
	sub ebx,'0'
	add eax,ebx
	jmp endCalculateTurn
endCalculateTurn:
	cmp ecx,0
	dec ecx
	jnz calculate

pop eax
call writeint


Exit
main ENDP
END main