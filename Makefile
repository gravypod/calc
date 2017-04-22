MODULES = tokenizer lexer parser

INCDIR  := $(abspath ./includes)
OBJDIR  := $(abspath ./bin/obj)
BINDIR  := $(abspath ./bin)

CC      := gcc
CFLAGS  := -Wall -I$(INCDIR)/ -pedantic-errors -O2
LDFLAGS := -lm

export

all: $(MODULES)

tokenizer:
	$(MAKE) -C  mtokenizer

lexer:
	$(MAKE) -C mlexer

parser:
	$(MAKE) -C mparser
