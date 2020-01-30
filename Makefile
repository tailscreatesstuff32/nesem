IDIR=../include
CC=cc
CFLAGS=-I$(IDIR) -O3 -fomit-frame-pointer

ODIR=obj

_DEPS=emulator.h
DEPS=$(pathsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=emulator.o
OBJ=$(pathsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

emulator: $(OBJ)
	$(CC) -c -o $@ $^ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *- core $(INCDIR)/*-
