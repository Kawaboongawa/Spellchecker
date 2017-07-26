#!/bin/bash

CC=gcc
CFLAGS= -pedantic -Werror -Wall -Wextra -std=gnu99 -g
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

clean:
	$(RM) $(DIRSRC)*.o
	$(RM) $(TARGET)
	$(RM) -r *.dSYM
	$(RM) -r .DS_STORE
	$(RM) -r misc/.DS_STORE

.PHONY: all clean
