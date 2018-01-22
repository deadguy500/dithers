SHELL = /bin/sh

CXX = g++
 
FFLAGS = -g -Wno-deprecated-declarations -Wno-write-strings
 
TARGET = dithers
OBJDIR = obj
SRCDIR = src
BINDIR = bin
VPATH = $(SRCDIR):$(OBJDIR)
FULLTARGET = $(BINDIR)/$(TARGET)

OBJFILES = main.o dither_rnd.o common.o

INCLUDES = -I/Library/Frameworks/SDL2.framework/Headers/
INCLUDES += -I/Library/Frameworks/SDL2_image.framework/Headers/

LINCLUDES = -framework SDL2 -framework Cocoa -framework SDL2_image
 
.SUFFIXES: .m .o
.m.o: ; @mkdir -p $(BINDIR) $(OBJDIR) 
	$(CXX) -c $(FFLAGS) -o $(OBJDIR)/$@ $< $(INCLUDES)

.SUFFIXES: .cpp .o
.cpp.o: ; @mkdir -p $(BINDIR) $(OBJDIR)
	$(CXX) -c $(FFLAGS) -o $(OBJDIR)/$@ $< $(INCLUDES)
 
$(FULLTARGET): $(OBJFILES)
	$(CXX) $(FFLAGS) -o $@ $(addprefix $(OBJDIR)/, $(OBJFILES)) $(LINCLUDES)

.PHONEY: clean
clean:
	@rm -rf *~ $(BINDIR) $(OBJDIR)  $(SRCDIR)/*~ *.out

%.o:

