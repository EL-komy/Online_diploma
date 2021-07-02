.section .vectors
.word 0x20001000
.word Vector_handler
.word Vector_handler
.word Vector_handler
.word Vector_handler
.word Vector_handler
.word Vector_handler

.section .text
_reset:
  bl main	
  bl .
.thumb_func  

Vector_handler:
   b _reset
