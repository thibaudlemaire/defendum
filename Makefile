CC=gcc

# Directories
SRCDIR=src
HEADDIR=include
LIBDIR=obj
BINDIR=bin


# Compiler options
CFLAGS= -I$(HEADDIR) -Wall -lev3dev-c -pthread

# Exec name
BIN=main

# Sources search
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(LIBDIR)/%.o)

# Rules :
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

$(OBJ): $(LIBDIR)/%.o: $(SRCDIR)/%.c $(HEADDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(LIBDIR)/*.o

Clean: clean
	rm $(BINDIR)/*
