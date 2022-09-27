	// Constants for the GNU Multiboot Specification
	// See https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
	.set ALIGN_ON_PAGE_BOUNDARIES, 	1<<0
	.set INCLUDE_MEMORY_INFO, 	1<<1
	.set ENABLE_GRAPHICS,		1<<2

	.set MAGIC, 0x1badb002
	.set FLAGS, ALIGN_ON_PAGE_BOUNDARIES | INCLUDE_MEMORY_INFO | ENABLE_GRAPHICS
	.set CHECKSUM, -(MAGIC + FLAGS)

	.set MODE_TYPE, 1    // 0 = Linear graphics mode, 1 = EGA text mode
	.set WIDTH,     80
	.set HEIGHT,    25
	.set DEPTH,     0


	// Multiboot header
	.section .multiboot
	.align 4

	.long MAGIC
	.long FLAGS
	.long CHECKSUM

	.skip 20

	.long MODE_TYPE
	.long WIDTH
	.long HEIGHT
	.long DEPTH

	// Leave space for the returned header
	.space 4 * 13


	.section .bss
	.align 16

stack_bottom:
	.skip 16384
stack_top:

	push %ebx

	.section .text

	.global _start
	.type _start, @function

_start:
	mov $stack_top, %esp

	call kearly
	call kmain

	cli
halt:	hlt
	jmp halt

	.size _start, . - _start
