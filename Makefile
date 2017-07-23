#!/bin/bash

CC=gcc
CFLAGS= -pedantic -Werror -Wall -Wextra -std=c99 -g
DIRSRC= ./src/
TARGET=TextMiningCompiler TextMiningApp
HEADERS=
SRC1= $(DIRSRC)main_compiler.c
SRC2= $(DIRSRC)main_app.c $(DIRSRC)levenshtein.c

all: $(TARGET)

TextMiningCompiler : $(SRC1)
	$(CC) -o $@ $^ $(CFLAGS)

TextMiningApp : $(SRC2)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(DIRSRC)*.o
	rm -f $(TARGET)
        
        
