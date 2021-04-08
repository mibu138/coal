CC = gcc

CFLAGS = -Wall -Wno-missing-braces -Wno-attributes -fPIC
LIBS = -lm 
ifeq ($(OS), WIN)
	OS_HEADERS = $(WIN_HEADERS)
	LIBEXT = dll
	HOMEDIR =  "$(HOMEDRIVE)/$(HOMEPATH)"
else
	OS_HEADERS = $(UNIX_HEADERS)
	LIBEXT = so
	HOMEDIR =  $(HOME)
LIBDIR  = $(HOMEDIR)/lib
LIBNAME = coal
LIBPATH = $(LIBDIR)/lib$(LIBNAME).$(LIBEXT)

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

release: CFLAGS += -DNDEBUG -O3
release: all

all: lib 

clean: 
	rm -f $(O)/* $(LIBPATH)

tags:
	ctags -R .

lib: $(OBJS) $(DEPS) 
	$(CC) -shared -o $(LIBPATH) $(OBJS)

$(O)/%.o:  %.c $(DEPS)
	$(CC) $(CFLAGS) $(INFLAGS) -c $< -o $@
