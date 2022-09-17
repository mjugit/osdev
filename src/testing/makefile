CC = gcc
CFLAGS = -g -Wextra

BUILD_DIR = ../../build
TESTING_DIR = .
LIBK_OBJ_DIR = $(BUILD_DIR)/testing/libk
LIBK_SRC_DIR = ../libk
LIBK_TESTSRC_DIR = libk

.PHONY: all
all: kmem_test vga_test kstd_test

# Test of kernel memory operations
KMEM_TEST_FILE = $(LIBK_TESTSRC_DIR)/kmem_test.c
KMEM_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/kmem_test.o
kmem_test: $(LIBK_SRC_DIR)/kmem.c $(KMEM_TEST_FILE)| $(LIBK_OBJ_DIR)
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(CFLAGS) $(KMEM_TEST_FILE) -o $(LIBK_OBJ_DIR)/kmem_test.o
	$(CC) $(KMEM_TEST_OBJ) -o $(TESTING_DIR)/kmem_test

# VGA video driver test
VGA_TEST_FILE = $(LIBK_TESTSRC_DIR)/vga_test.c
VGA_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/vga_test.o $(LIBK_OBJ_DIR)/vga.o
vga_test: $(LIBK_SRC_DIR)/kmem.c $(LIBK_SRC_DIR)/vga.c $(VGA_TEST_FILE) | $(LIBK_OBJ_DIR)
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/vga.c -o $(LIBK_OBJ_DIR)/vga.o
	$(CC) -c $(CFLAGS) $(VGA_TEST_FILE) -o $(LIBK_OBJ_DIR)/vga_test.o
	$(CC) $(VGA_TEST_OBJ) -o $(TESTING_DIR)/vga_test

# Kernel standard library test
KSTD_TEST_FILE = $(LIBK_TESTSRC_DIR)/kstd_test.c
KSTD_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/kstd_test.o $(LIBK_OBJ_DIR)/vga.o $(LIBK_OBJ_DIR)/kstd.o
kstd_test: $(LIBK_SRC_DIR)/kmem.c $(LIBK_SRC_DIR)/vga.c $(LIBK_SRC_DIR)/kstd.c $(KSTD_TEST_FILE) | $(LIBK_OBJ_DIR)
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/vga.c -o $(LIBK_OBJ_DIR)/vga.o
	$(CC) -c $(CFLAGS) $(LIBK_SRC_DIR)/kstd.c -o $(LIBK_OBJ_DIR)/kstd.o
	$(CC) -c $(CFLAGS) $(KSTD_TEST_FILE) -o $(LIBK_OBJ_DIR)/kstd_test.o
	$(CC) $(KSTD_TEST_OBJ) -o $(TESTING_DIR)/kstd_test

$(LIBK_OBJ_DIR):
	mkdir -p $(LIBK_OBJ_DIR)

.PHONY: clean
clean:
	rm vga_test
	rm kmem_test
	rm kstd_test
