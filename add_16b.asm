ASSUME CS:CODE, DS:DATA

DATA SEGMENT
MSG1 DB 0AH,'ENTER NUM1 : $'
MSG2 DB 0AH,'ENTER NUM2 : $'
MSG3 DB 0AH,'SUM IS : $'
DATA ENDS

CODE SEGMENT
START:
MOV AX,DATA
MOV DS,AX

;;	for 1st num	
MOV DX,OFFSET MSG1
MOV AH,09H	;display msg1
INT 21H

MOV AH,01H	;read 1st digit
INT 21H
SUB AL,30H	;convert from ascii to hex
MOV BH,0AH	;MOV 10
MUL BH		;multiply by 10
MOV BH,AL

MOV AH,01H	;read 2nd digit
INT 21H
SUB AL,30H
ADD BH,AL

MOV AH,01H	;read 3rd digit
INT 21H
SUB AL,30H	;convert from ascii to hex
MOV CH,0AH	;MOV 10
MUL CH		;multiply by 10
MOV CH,AL

MOV AH,01H	;read 4th digit
INT 21H
SUB AL,30H
ADD CH,AL

;;	for 2ND num	
MOV DX,OFFSET MSG2
MOV AH,09H	;display msg1
INT 21H

MOV AH,01H	;read 1st digit
INT 21H
SUB AL,30H	;convert from ascii to hex
MOV BL,0AH	;MOV 10
MUL BL		;multiply by 10
MOV BL,AL

MOV AH,01H	;read 2nd digit
INT 21H
SUB AL,30H
ADD BL,AL

MOV AH,01H	;read 3rd digit
INT 21H
SUB AL,30H	;convert from ascii to hex
MOV DH,0AH	;MOV 10
MUL DH		;multiply by 10
MOV DH,AL

MOV AH,01H	;read 4th digit
INT 21H
SUB AL,30H
ADD DH,AL

;;	add the numbers
ADD BH,BL
ADD CH,DH

;to display
MOV DX,OFFSET MSG3
MOV AH,09H
INT 21H

;display 1st byte
MOV CL,0AH	;CL <- 10
MOV AL,BH
MOV AH,00H
DIV CL		;divide by 10

ADD AL,30H	;convert from hex to ascii
MOV BL,AH
MOV DL,AL
MOV AH,02H	;display 1st digit
INT 21H

ADD BL,30H
MOV DL,BL
MOV AH,02H	;display 2nd digit
INT 21H

;display 2nd byte
MOV CL,0AH	;CL <- 10
MOV AL,CH
MOV AH,00H
DIV CL		;divide by 10

ADD AL,30H	;convert from hex to ascii
MOV BL,AH
MOV DL,AL
MOV AH,02H	;display 3rd digit
INT 21H

ADD BL,30H
MOV DL,BL
MOV AH,02H	;display 4th digit
INT 21H
	
MOV AH,4CH
INT 21H

CODE ENDS
END START
