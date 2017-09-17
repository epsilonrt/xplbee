.section .bootvect,"ax",@progbits
.global __vector_default
__vector_default:
    rjmp  __vector_default
