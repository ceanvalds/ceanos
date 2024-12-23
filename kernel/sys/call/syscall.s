global isr128

extern sys_write

;---------------------------------; 
extern invalid_syscall
;---------------------------------;

isr128:
        pusha

        cmp eax, 0
        je sys_write_asm

        jmp invalid_syscall_asm
        
sys_write_asm:
        mov ebx, [esp + 4]     
        call sys_write         
        jmp syscall_end           

invalid_syscall_asm:
        call invalid_syscall
        jmp syscall_end
syscall_end:
        popa
        iret
