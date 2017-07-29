#!/bin/bash

UNAME= $(shell uname)
CC=gcc
ifeq ($(UNAME), Darwin)
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
	./tests/test.py ./tests/testdir/
	@make clean

clean:
	$(RM) $(DIRSRC)*.o
	$(RM) $(TARGET)
	$(RM) -r *.dSYM
	$(RM) -r .DS_STORE
	$(RM) -r misc/.DS_STORE
	$(RM) TextMiningApp
	$(RM) TextMiningCompiler
        
.PHONY: all clean
