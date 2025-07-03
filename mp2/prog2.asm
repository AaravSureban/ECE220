;aryana9, sureban2, sanjayb3
; This code acts as a calculator for single-digit postfix expressions. It can perform addition, subtraction, multiplication, division, and exponents. Our program starts by checking whether an input is an operand or an operator. If it is an operator, we check to see what sign it is and jump to that respective function in our code. Once the program figures out what sign was inputted, it checks to see whether there are two numbers in our stack on which to perform the operation, returning an invalid message if it is not valid. The program then performs the operation and pushes the result back into the stack. If an operand is seen, it is printed out on the LC-3 console using the previous code implemented in Lab 1 and pushed into the stack. If an equals sign is seen, it checks if there is only one operand left in the stack, which gets outputted.


; Register Table:
; R0: Used to store user input
; R1: used as digit counter (NEXTCHAR), decrementer (EXP)
; R2: Used to check if the result of multiplication is pos or neg
; R3: Operand #1
; R4: Operand #2
; R5: Used to check popped character
; R6: Storage
; R7: JSR, RET


.ORIG x3000
    AND R0, R0, #0
    AND R1, R1, #0
    AND R2, R2, #0
    AND R3, R3, #0
    AND R4, R4, #0
    AND R5, R5, #0
    AND R6, R6, #0
; NEXTCHAR checks whether our input is an operand or operator, and if an operator, which one.
NEXTCHAR
    GETC                        ; R0 <--- input char
    OUT
    LD R4, NEGATIVE_EQUAL       ; R4 <-- R0 - '='
    ADD R4, R0, R4
    BRz EQUAL_SEEN              ; if char is '=', pop


    LD R4, NEGATIVE_SPACE       ; R4 <-- R0 - '"space"'
    ADD R4, R0, R4
    BRz NEXTCHAR                ; if char is '"space"', get next character


    LD R4, NEGATIVE_PLUS        
    ADD R4, R0, R4
    BRz PLUS_SEEN               ; if char is '+', then go to P


    LD R4, NEGATIVE_MINUS
    ADD R4, R0, R4
    BRz MINUS_SEEN              ; if char is '-', then go to MIN_SEEN


    LD R4, NEGATIVE_MULT	
    ADD R4, R0, R4
    BRz MULT_SEEN		; if char is '*', then go to MULT_SEEN


    LD R4, NEGATIVE_DIV
    ADD R4, R0, R4
    BRz DIV_SEEN		; if char is '/', then go to DIV_SEEN


    LD R4, NEGATIVE_POW
    ADD R4, R0, R4
    BRz EXP_SEEN		; if char is '^', then go to EXP_SEEN
       
    LD R4, NEGATIVE_ZERO        ; check if char is a single digit number
    ADD R4, R0, R4
    BRn INVALID_MESSAGE
    LD R4, NEGATIVE_NINE
    ADD R4, R0, R4
    BRp INVALID_MESSAGE
    BRnzp OPERAND_SEEN
EQUAL_SEEN                      ; equal sign has been seen
    JSR POP
    ADD R5, R5, #0              ; R5 stores 0 if success
    BRp INVALID_MESSAGE
    ADD R6, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRz INVALID_MESSAGE
    ADD R3, R6, #0
    AND R1, R1, #0              ; initializing digit counter
NEXTDIGIT  
    ADD R4, R1, #-4             ; check if greater than 4
    BRzp FINISH
    AND R2, R2, #0              ; initializing digit and bit counter
    AND R5, R5, #0
CHECKBITS  
    ADD R4, R5, #-4             ; check if more than 4 bits from R3
    BRzp MORETHANFOUR
    ADD R2, R2, R2              ; shifting digit
    ADD R3, R3, #0
    BRzp ADDNONE                ; check if R3 is positive or negative
    ADD R2, R2, #1              ; add one if negative
ADDNONE
    ADD R3, R3, R3              ; left shift R3
    ADD R5, R5, #1              ; increment bit counter
    BRnzp CHECKBITS
MORETHANFOUR    
    ADD R4, R2, #-9             ; check if digit less than 9
    BRnz ADDZERO
    ADD R2, R2, #15
    ADD R2, R2, #15
    ADD R2, R2, #15
    ADD R2, R2, #10             ; adding 55
    BRnzp PRINTOUTPUT
ADDZERO
    ADD R2, R2, #15             ; adding 48
    ADD R2, R2, #15
    ADD R2, R2, #15
    ADD R2, R2, #3
PRINTOUTPUT 
    ADD R0, R2, #0  
    OUT     ;OUT TRAP
    ADD R1, R1, #1              ; increment digit counter
    BRnzp NEXTDIGIT             ; return to check if all printed
FINISH      
    ADD R5, R6, #0
    BRnzp FINISHED


PLUS_SEEN 			; a plus sign has been seen
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE	   	;check if you popped a value or not
    ADD R4, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE
    ADD R3, R0, #0
    JSR PLUS ; values will be stored in R3 and R4, call PLUS subroutine
    JSR PUSH 			; push output to stack
    BRnzp NEXTCHAR
   
MINUS_SEEN			; minus sign has been seen
    JSR POP
    ADD R5, R5, #0		; check if you popped a value or not
    BRp INVALID_MESSAGE
    ADD R4, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE
    ADD R3, R0, #0
    JSR MIN			; R3 and R4 contain operands, call MIN subroutine
    JSR PUSH 			; push value to stack
    BRnzp NEXTCHAR


MULT_SEEN
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE		; check if you popped a value or not
    ADD R4, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE
    ADD R3, R0, #0
    JSR MUL
    JSR PUSH			; push value to stack
    BRnzp NEXTCHAR
DIV_SEEN
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE		; check if you popped a value or not
    ADD R4, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE
    ADD R3, R0, #0
    JSR DIV
    JSR PUSH
    BRnzp NEXTCHAR
EXP_SEEN
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE		; check if you popped a value or not
    ADD R4, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRp INVALID_MESSAGE
    ADD R3, R0, #0
    JSR EXP
    JSR PUSH			; push result to stack
    BRnzp NEXTCHAR
OPERAND_SEEN ; if we see a digit 0-9
    LD R4, NEGATIVE_ZERO ; convert it from ASCII to binary
    ADD R0, R4, R0
    JSR PUSH 	; push it to stack
    BRnzp NEXTCHAR
   
INVALID_MESSAGE 		; in the event that we have an INVALID message
    LEA R0, INVALID 		; INVALID label contains the string
    PUTS 			; output the string to console
    BRnzp FINISHED






FINISHED 
HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;R0 <-- R3 + R4
PLUS    
    ADD R0, R3, R4             	;add R3 and R4 and store it in R0
    RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;input r3, r4
;out R0
;R0 <-- R3 - R4
MIN 	; minus subroutine
    NOT R4, R4
    ADD R4, R4, #1 	       ; convert R4 to negative
    ADD R0, R3, R4 	       ; subtract R4 from R3
    RET
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;R0 <-- R3 * R4


MUL 			; multiply R3 and R4
    AND R2, R2, #0 	; R2 tells us if our answer should be pos or neg
    ADD R2, R2, #1 	; if R2 pos, answer pos, else neg
    ADD R3, R3, #0
    BRzp CHECKNEXT	; check sign of R3
    NOT R3, R3
    ADD R3, R3, #1 	; convert to pos if negative
    NOT R2, R2
    ADD R2, R2, #1 	; flip sign of R2
CHECKNEXT
    ADD R4, R4, #0 	; check sign of R4
    BRzp NEXTSTEP
    NOT R4, R4 		; convert R4 to pos if negative
    ADD R4, R4, #1
    NOT R2, R2
    ADD R2, R2, #1 	; flip sign of R2
NEXTSTEP    		; repeatedly add R3 R4 amount of times
    AND R0, R0, #0
    ADD R4, R4, #0
    BRz MULDONE
MULREPEAT  
    ADD R0, R0, R3
    ADD R4, R4, #-1
    BRp MULREPEAT
MULDONE 		
    ADD R2, R2, #0
    BRp MULFIN 		; if R2 is positive, all done, otherwise make answer neg
    NOT R0, R0
    ADD R0, R0, #1
MULFIN  
    RET
   
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV 		       ; division subroutine
    AND R0, R0, #0
    ADD R3, R3, #0
    NOT R4, R4
    ADD R4, R4, #1     ; make R4 negative
DIVREPEAT  
    ADD R3, R3, R4     ; subtract R4 from R3 until our answer < 0
    BRn DIVDONE
    ADD R0, R0, #1
    BRnzp DIVREPEAT
DIVDONE
    RET
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;R0 <-- R3 ^ R4


EXP
;your code goes here
    ADD R1, R4, #0 	; R1 contains R4
    ADD R5, R7, #0 	; save R7 when we call Multiply subroutine
    AND R4, R4, #0
    ADD R4, R4, #1 	; R4 contains starting value
    ADD R1, R1, #0
    BRz EXPDONE
EXPREPEAT   
    JSR MUL 		; repeatedly multiply R4 and R3 
    ADD R4, R0, #0
    ADD R1, R1, #-1
    BRp EXPREPEAT
    ADD R7, R5, #0
EXPDONE
RET


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH    
    ST R3, PUSH_SaveR3          ;save R3
    ST R4, PUSH_SaveR4          ;save R4
    AND R5, R5, #0              ;
    LD R3, STACK_END            ;
    LD R4, STACk_TOP            ;
    ADD R3, R3, #-1             ;
    NOT R3, R3                  ;
    ADD R3, R3, #1              ;
    ADD R3, R3, R4              ;
    BRz OVERFLOW                ;stack is full
    STR R0, R4, #0              ;no overflow, store value in the stack
    ADD R4, R4, #-1             ;move top of the stack
    ST R4, STACK_TOP            ;store top of stack pointer
    BRnzp DONE_PUSH             ;
OVERFLOW
    ADD R5, R5, #1              ;
DONE_PUSH
    LD R3, PUSH_SaveR3          ;
    LD R4, PUSH_SaveR4          ;
    RET




PUSH_SaveR3 .BLKW #1            ;
PUSH_SaveR4 .BLKW #1            ;




;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
    ST R3, POP_SaveR3           ;save R3
    ST R4, POP_SaveR4           ;save R3
    AND R5, R5, #0              ;clear R5
    LD R3, STACK_START      
    LD R4, STACK_TOP    
    NOT R3, R3          
    ADD R3, R3, #1      
    ADD R3, R3, R4      
    BRz UNDERFLOW      
    ADD R4, R4, #1      
    LDR R0, R4, #0      
    ST R4, STACK_TOP    
    BRnzp DONE_POP      
UNDERFLOW
    ADD R5, R5, #1      
DONE_POP
    LD R3, POP_SaveR3  
    LD R4, POP_SaveR4  
    RET




POP_SaveR3  .BLKW #1    
POP_SaveR4  .BLKW #1    


STACK_END   .FILL x3FF0
STACK_START .FILL x4000
STACK_TOP   .FILL x4000
NEGATIVE_EQUAL  .FILL xFFC3
NEGATIVE_SPACE  .FILL xFFE0
NEGATIVE_ZERO   .FILL xFFD0
NEGATIVE_NINE   .FILL xFFC7
NEGATIVE_PLUS   .FILL xFFD5
NEGATIVE_MINUS  .FILL xFFD3
NEGATIVE_MULT   .FILL xFFD6
NEGATIVE_DIV        .FILL xFFD1
NEGATIVE_POW        .FILL xFFA2
INVALID .STRINGZ    "Invalid Message"  
.END
