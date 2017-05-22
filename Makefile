SRCDIR := src
BUILDDIR := build
BUILDDIRGCW := build-gcw
BINDIR := bin

PROG   := rrpg
TARGET := $(PROG)
TARGETDIST := $(PROG).opk
CC     := $(CROSS_COMPILE)g++ -std=c++11
INCL   :=
CFLAGS := -g -O2 -Wall -Wmissing-declarations -Weffc++ \
		-pedantic -pedantic-errors -Wextra -Wcast-align \
		-Wcast-qual -Wconversion -Wsign-conversion \
		-Wdisabled-optimization \
		-Werror -Wfloat-equal -Wformat=2 \
		-Wformat-nonliteral -Wformat-security \
		-Wformat-y2k \
		-Wimport -Winit-self -Winline \
		-Winvalid-pch \
		-Wlong-long \
		-Wmissing-field-initializers -Wmissing-format-attribute \
		-Wmissing-include-dirs -Wmissing-noreturn \
		-Wpacked -Wpointer-arith \
		-Wredundant-decls \
		-Wshadow -Wstack-protector \
		-Wstrict-aliasing=2 -Wswitch-default \
		-Wswitch-enum \
		-Wunreachable-code -Wunused \
		-Wunused-parameter \
		-Wvariadic-macros \
		-Wwrite-strings
LDFLAGS:=-Isrc/rRpg -Isrc/common
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -lSDL2 -lSDL2_image

SRC := $(shell find $(SRCDIR)/rRpg/ $(SRCDIR)/common/ -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
OBJGCW := $(patsubst %.cpp,$(BUILDDIRGCW)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: game

full: tools game
	./bin/tools/data-compiler tiles resources/src/floor-tiles.dat resources/floor-tiles.dat
	./bin/tools/data-compiler tilesets resources/src/tilesets.dat resources/tilesets.dat

game: $(PROG)

-include $(DEP)

%.deps: %.cpp
	$(CC) -MM $< >$@

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CCDYNAMICFLAGS) -c -MMD $(patsubst $(BUILDDIR)/%.o,%.cpp,$@) -o $@

$(BUILDDIRGCW)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CCDYNAMICFLAGS) -DGCW -c -MMD $(patsubst $(BUILDDIRGCW)/%.o,%.cpp,$@) -o $@

clean:
	rm -rf $(BUILDDIR) $(LIBDIR)

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) $(CCDYNAMICFLAGS) -o $(BINDIR)/$@ $^

gcw: $(OBJGCW)
	mkdir -p $(BINDIR)
	$(CC) $(CCDYNAMICFLAGS) -o $(BINDIR)/$(PROG) $^

opk:
	mkdir -p dist/bin dist/resources/DawnLike/Objects/ dist/resources/DawnLike/Characters/
	cp -r configs dist/
	cp resources/tilesets.dat resources/floor-tiles.dat resources/taxonomy.dat dist/resources/
	cp resources/DawnLike/Characters/Demon1.png resources/DawnLike/Characters/Player1.png resources/DawnLike/Characters/Demon0.png resources/DawnLike/Characters/Player0.png resources/DawnLike/Characters/Rodent1.png resources/DawnLike/Characters/Rodent0.png dist/resources/DawnLike/Characters/
	cp resources/DawnLike/Objects/Floor.png dist/resources/DawnLike/Objects/
	mkdir -p dist/bin
	cp $(BINDIR)/$(PROG) dist/bin/
	mksquashfs dist $(TARGETDIST) -all-root -noappend -no-exports -no-xattrs

tools:
	@mkdir -p $(BINDIR)/tools
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find src/tools/dataCompiler/ $(SRCDIR)/common/ -name "*.cpp") \
		-o $(BINDIR)/tools/data-compiler
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find src/tools/dataDecompiler/ $(SRCDIR)/common/ -name "*.cpp") \
		-o $(BINDIR)/tools/data-decompiler
