
ifeq ($(OS), Windows_NT)
	OS = WIN
else 
	OS = UNIX
endif

CC = gcc

CFLAGS = -Wall -Wno-missing-braces -Wno-attributes -fPIC
LIBS = -lm 
ifeq ($(OS), WIN)
	OS_HEADERS = $(WIN_HEADERS)
	LIBEXT = dll
	HOMEDIR =  C:
	XEXT = .exe
else
	OS_HEADERS = $(UNIX_HEADERS)
	LIBEXT = so
	HOMEDIR =  $(HOME)
endif
LIBDIR  = $(HOMEDIR)/lib
NAME    = coal
LIBNAME = lib$(NAME).$(LIBEXT)
LIBPATH = $(LIBDIR)/$(LIBNAME)
TESTNAME = $(NAME)test$(XEXT)

O = build

NAME = coal

DEPS =  \
		m_math.h \
		m.h \
		util.h

OBJS =  \
		$(O)/m_math.o \
		$(O)/m.o \
		$(O)/util.o

debug: CFLAGS += -g -DVERBOSE=1
debug: all

win: OS = WIN
win: all

release: CFLAGS += -DNDEBUG -O3
release: all

all: lib test

clean: 
	rm -f $(O)/* $(LIBPATH) $(TESTNAME) $(TESTNAME).exe

tags:
	ctags -R .

lib: $(OBJS) $(DEPS) 
	$(CC) -shared -o $(LIBPATH) $(OBJS) $(LIBS)

test: $(OBJS) $(DEPS)
	$(CC) -L$(LIBDIR) coaltest.c -o $(TESTNAME) -l$(NAME)

$(O)/%.o:  %.c $(DEPS)
	$(CC) $(CFLAGS) $(INFLAGS) -c $< -o $@
