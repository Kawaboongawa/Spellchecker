#!/bin/bash

UNAME= $(shell uname)

OS=linux64
CC=gcc
ifeq ($(UNAME), Darwin)
OS=osx
CC=gcc-7
endif

CFLAGS= -pedantic -Werror -Wall -Wextra -std=gnu99 -g -O3
DIRSRC= ./src/
TARGET=TextMiningCompiler TextMiningApp
HEADERS=headers

SRC1= $(DIRSRC)main_compiler.c \
$(DIRSRC)trie.c

SRC2= $(DIRSRC)main_app.c \
$(DIRSRC)levenshtein.c \
$(DIRSRC)tools.c \
$(DIRSRC)word_struct.c \
$(DIRSRC)search.c \
$(DIRSRC)trie.c

all: $(TARGET)

TextMiningCompiler : $(SRC1)
	$(CC) -I$(HEADERS) -o $@ $^ $(CFLAGS)

TextMiningApp : $(SRC2)
	$(CC) -I$(HEADERS) -o $@ $^ $(CFLAGS)

test: all
	./ref/$(OS)/TextMiningCompiler misc/words.txt words.bin
	sudo mv words.bin ref/$(OS)/
	./TextMiningCompiler misc/words.txt words.bin
	./TextMiningCompiler --export
	./tests/test.py ./tests/testdir/ $(OS)
	@make clean

doc:
	$(RM) -r doc
	doxygen Doxyfile

clean:
	$(RM) $(DIRSRC)*.o
	$(RM) $(TARGET)
	$(RM) -r doc
	$(RM) -r *.dSYM
	$(RM) -r .DS_STORE
	$(RM) -r misc/.DS_STORE
	$(RM) TextMiningApp
	$(RM) TextMiningCompiler
	$(RM) *~
	$(RM) *#

.PHONY: all clean doc test
