; Partners: sanjayb3, aryana9, sureban2
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
	
;; We were given the code to populate the histogram with the right values.
;; This means all we need to do is loop through each loop of the histogram.
;; We can set a loop counter and loop through the histogram 27 times, starting with the first line.
;; We use the loop counter to also calculate the ASCII of the current character.
;; For each row, we load the bits in that row of the histogram into R3.
;; In Lab 1, we wrote a script to output the value stored in R3 as a hex number.
;; We run that same Lab 1 code for each row, printing the hex value of the bits stored at each row of the histogram.
;; When loop counter reaches 27, we break out of the loop.
;; R0 is used to print out characters
;; R1 is used as the digit counter
;; R2 is used as the bit counter
;; R3 holds the character needed to print
;; R4 is used as a temp register to check conditions for branches
;; R5 is used to store digit
;; R6 is used as the final loop counter for the histogram

	AND R0, R0, #0		; Reset print reg
	AND R6, R6, #0		; Initialize loop counter
PRINT	ADD R0, R6, #15		; Store value to be printed in R0
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #4
	OUT
	AND R0, R0, #0		; Reset print reg and print space
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #2
	OUT
	LD R3, HIST_ADDR	; Load memory address of the character we want to print in R3
	ADD R3, R3, R6
	LDR R3, R3, #0

	AND R1, R1, #0 		; Lab 1 code
	ADD R1, R1, #4 		; init digit counter

LOOP	ADD R1, R1, #0
	BRz BLINE
	AND R2, R2, #0		; init bit counter
	AND R5, R5, #0 		; init digit
CHECK	AND R4, R4, #0		; Check if R3 has less than 4 bits
	ADD R4, R2, #-4
	
 	BRn LESS		; Branch if R3 has less than 4 bits
	ADD R4, R5, #-9		; Check if digit is less than 9
	BRnz NINE		; Branch if digit is less than 9
	ADD R5, R5, #15		; Add 'A' - 10
	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #10
	AND R0, R0, #0
	ADD R0, R0, R5
	OUT
	ADD R1, R1, #-1		; Decrement digit counter
	BRnzp LOOP

NINE	ADD R5, R5, #15		; Add '0'
	ADD R5, R5, #15
	ADD R5, R5, #15
	ADD R5, R5, #3
	AND R0, R0, #0
	ADD R0, R0, R5
	OUT
	ADD R1, R1, #-1		; Decerement digit counter
	BRnzp LOOP


LESS	ADD R5, R5, R5		; Shift digit left by one bit
	ADD R3, R3, #0
	BRn SHIFT		; Check if R3 is negative
	ADD R5, R5, #0		; Add 0 to digit
	ADD R3, R3, R3		; Shift R3 left by one bit
	ADD R2, R2, #1		; Increment bit counter
	BRnzp CHECK

SHIFT	ADD R5, R5, #1		; Add 1 to digit
	ADD R3, R3, R3		; Shift R3 left by one bit
	ADD R2, R2, #1		; Increment bit counter
	BRnzp CHECK

BLINE	AND R0, R0, #0		; Print blankline
	ADD R0, R0, #10
	OUT
	ADD R6, R6, #1		; Check if counter < 27
	ADD R5, R6, #-16
	ADD R5, R5, #-11
	BRn PRINT		; If true, loop back and repeat
	

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
	
; for testing, you can use the lines below to include the string in this
; program...   ; STR_START	.FILL STRING	; string starting address ;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
