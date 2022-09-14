CC = gcc

BUILD_DIR = ../../build
TESTING_DIR = .
LIBK_OBJ_DIR = $(BUILD_DIR)/testing/libk
LIBK_SRC_DIR = ../libk
LIBK_TESTSRC_DIR = libk


# Test of kernel memory operations
KMEM_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/kmem_test.o
kmem_test: $(LIBK_SRC_DIR)/kmem.c | $(LIBK_OBJ_DIR)
	$(CC) -c $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(LIBK_TESTSRC_DIR)/kmem_test.c -o $(LIBK_OBJ_DIR)/kmem_test.o
	$(CC) $(KMEM_TEST_OBJ) -o $(TESTING_DIR)/kmem_test

# VGA video driver test
VGA_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/vga_test.o $(LIBK_OBJ_DIR)/vga.o
vga_test: $(LIBK_SRC_DIR)/kmem.c $(LIBK_SRC_DIR)/vga.c $(LIBK_TESTSRC_DIR)/vga_test.c | $(LIBK_OBJ_DIR)
	$(CC) -c $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(LIBK_SRC_DIR)/vga.c -o $(LIBK_OBJ_DIR)/vga.o
	$(CC) -c $(LIBK_TESTSRC_DIR)/vga_test.c -o $(LIBK_OBJ_DIR)/vga_test.o
	$(CC) $(VGA_TEST_OBJ) -o $(TESTING_DIR)/vga_test

$(LIBK_OBJ_DIR):
	mkdir -p $(LIBK_OBJ_DIR)
