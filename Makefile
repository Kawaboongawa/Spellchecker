#!/bin/bash

CC=gcc
CFLAGS= -pedantic -Werror -Wall -Wextra -std=c99 -g
DIRSRC= ./src/
TARGET=TextMiningCompiler TextMiningApp
HEADERS=
OBJ1= $(DIRSRC)main_app.o
OBJ2= $(DIRSRC)main_compiler.o 

all: $(TARGET)

TextMiningCompiler : $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS)

TextMiningApp : $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS)


##########################################
# Generic rules
##########################################

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(DIRSRC)*.o
	rm -f $(TARGET)
        
        
