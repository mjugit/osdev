	// Constants used for the Multiboot header
	// See https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
	.set ALIGN_ON_PAGE_BOUNDARIES, 	1<<0
	.set INCLUDE_MEMORY_INFO, 	1<<1
	
	.set MULTIBOOT_FLAGS, 		ALIGN_ON_PAGE_BOUNDARIES | INCLUDE_MEMORY_INFO
	.set MULTIBOOT_MAGIC, 		0x1BADB002
	.set MULTIBOOT_CHECKSUM, 	-(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

	// Multiboot header
	.section .multiboot
	.align 4
	.long MULTIBOOT_MAGIC
	.long MULTIBOOT_FLAGS
	.long MULTIBOOT_CHECKSUM


	.section .bss
	.align 16
stack_bottom:
	.skip 16384
stack_top:


	.section .text
	.global _start
	.type _start, @function
_start:
	mov $stack_top, %esp
	call kernel_main

	cli
halt:	hlt
	jmp halt

	.size _start, . - _start
