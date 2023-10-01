IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=../src
BUILDDIR=build

_DEPS = params.h gen_file.h gen_md.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.c gen_file.c gen_md.c params.c
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

boiler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~





