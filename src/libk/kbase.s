
gdtr:
	.word 0
	.long 0
	
	.type set_gdt, @function

set_gdt:
	cli
	mov %ax, 4(%esp)
	mov [gdtr], %ax
	mov %eax, 8(%esp)
	mov [gdtr + 2], %eax
	lgdt [gdtr]
	sti
	ret
	
