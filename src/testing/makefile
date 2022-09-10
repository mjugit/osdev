CC = gcc

BUILD_DIR = ../../build
LIBK_OBJ_DIR = $(BUILD_DIR)/testing/libk
LIBK_SRC_DIR = ../libk
LIBK_TESTSRC_DIR = libk


KMEM_TEST_OBJ = $(LIBK_OBJ_DIR)/kmem.o $(LIBK_OBJ_DIR)/kmem_test.o
.PHONY: kmem_test
kmem_test: $(LIBK_SRC_DIR)/kmem.c | $(LIBK_OBJ_DIR)
	$(CC) -c $(LIBK_SRC_DIR)/kmem.c -o $(LIBK_OBJ_DIR)/kmem.o
	$(CC) -c $(LIBK_TESTSRC_DIR)/kmem_test.c -o $(LIBK_OBJ_DIR)/kmem_test.o
	$(CC) $(KMEM_TEST_OBJ) -o $(LIBK_OBJ_DIR)/kmem_test

$(LIBK_OBJ_DIR):
	mkdir -p $(LIBK_OBJ_DIR)
