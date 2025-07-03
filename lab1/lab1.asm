.ORIG x3000
	AND R1, R1, #0
	ADD R1, R1, #4 		;init digit counter

LOOP	ADD R1, R1, #0
	BRz DONE
	AND R2, R2, #0		;init bit counter
	AND R5, R5, #0 		;init digit
CHECK	AND R4, R4, #0
	ADD R4, R2, #-4
	
 	BRn LESS
	ADD R4, R5, #-9
	BRnz NINE
	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #10
	AND R0, R0, #0
	ADD R0, R0, R5
	OUT
	ADD R1, R1, #-1
	BRnzp LOOP

NINE	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #3
	AND R0, R0, #0
	ADD R0, R0, R5
	OUT
	ADD R1, R1, #-1
	BRnzp LOOP


LESS	ADD R5, R5, R5
	ADD R3, R3, #0
	BRn SHIFT
	ADD R5, R5, #0
	ADD R3, R3, R3
	ADD R2, R2, #1
	BRnzp CHECK

SHIFT	ADD R5, R5, #1
	ADD R3, R3, R3
	ADD R2, R2, #1
	BRnzp CHECK
	
DONE	HALT

	.END
	
	
	
