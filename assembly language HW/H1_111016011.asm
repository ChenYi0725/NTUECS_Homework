;CF-> CY, AF-> AC, ZF->ZR, SF->PL, OF->OV
INCLUDE Irvine32.inc
;作者:111016011陳奕
;操作說明:輸入一串數值,中間用空白隔開，可以將輸入的數字按照數值,由大到小排序
;自評:100(包含所有功能且有附上註解)
.data
stringIn BYTE 100 DUP(0)		;存放輸入
inputNum DWORD 100 DUP(0)		;存放整數
count DWORD 0					;整數數量
wordTen WORD 0Ah				;用以x10
isFirst byte 1					;用以分辨是否為第一個數字
temp DWORD 0					;交換用
outputMsg BYTE "請輸入數字串",0
personalMsg1 Byte "作者:111016011陳奕",0
personalMsg2 Byte "操作說明:輸入一串數值,中間用空白隔開，可以將輸入的數字按照數值,由大到小排序",0
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


	mov ebx,OFFSET inputNum
	mov edx,OFFSET outputMsg
	call WriteString
	call Crlf

	mov edx,OFFSET stringIn			;edx存字串
	mov ecx,100
	call ReadString


	mov ecx,eax		;loop 字串長度次	
	mov eax,0
	push edx

processString:	
	mov edi,0
	movzx edi, byte ptr [edx]	;取得當前字元的ASCII碼
	add edx,1
									
	cmp edi,' ' 				
	jnz notSpace
	cmp edi,0					
	jz isSpace
								;如果不是空格，eax持續往下紀錄，直到遇到空格
	inc count
	mov [ebx],eax
	add ebx,type inputNum		;存到陣列中

	mov isFirst,1
	mov eax,0
	jmp isSpace				;遇到空白跳過
notSpace: 
	push edx
	sub edi ,'0'			;把ASCII改回數字
		
	cmp isFirst,1
	jz First
	mul wordTen				;如果不是第一次則*10加新數字
First: 
	add eax,edi
	mov isFirst,0
	pop edx
	
		
isSpace:
 	loop processString

	inc count
	mov [ebx],eax
	add ebx,type inputNum		;存到陣列中
	pop edx

	;排序
	mov ecx,count
	dec ecx
sortLoop2:				;外迴圈

;內迴圈
	push ecx
	mov ecx,count
	dec ecx
sortLoop1:
	;if(not (A[i]>A[i+1]))->dont swap
	push eax
	mov eax,[inputNum+ecx*4]
	cmp eax,[inputNum+ecx*4+4]
	pop eax
	jge notSwap	
	;交換
	push eax
	push ebx
	mov eax,[inputNum+ecx*4]	
	mov ebx,[inputNum+ecx*4+4]
	mov [inputNum+ecx*4+4],eax
	mov [inputNum+ecx*4],ebx
	pop ebx
	pop eax
notSwap:
	sub ecx,1
	cmp ecx,0
	jge sortLoop1

	pop ecx
;外迴圈判定
	sub ecx,1
	cmp ecx,0
	jge sortLoop2			;回到外迴圈最上面

	;輸出陣列
	mov ebx,0			;for(ebx=n;ebx>0;ebx--)
outputArray:
	mov eax,[inputNum+ebx*4]		
	call writeint
	mov al,' '
	call writechar
	inc ebx
	cmp ebx,count
	jnz outputArray

Exit
main ENDP
END main