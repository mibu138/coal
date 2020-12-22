CC = gcc

CFLAGS = -Wall -Wno-missing-braces -Wno-attributes -fPIC
LDFLAGS = -L/opt/hfs18.0/dsolib -L$(HOME)/lib
INFLAGS = -I$(HOME)/dev
LIBS = -lm 
LIB = $(HOME)/lib
LIBNAME = coal

O = build

NAME = coal

DEPS =  \
		m_math.h \

OBJS =  \
		$(O)/m_math.o \

debug: CFLAGS += -g -DVERBOSE=1
debug: all

release: CFLAGS += -DNDEBUG -O3
release: all

all: lib tags 

clean: 
	rm -f $(O)/* $(LIB)/$(LIBNAME) 

tags:
	ctags -R .

lib: $(OBJS) $(DEPS) 
	$(CC) -shared -o $(LIB)/lib$(LIBNAME).so $(OBJS)

staticlib: $(OBJS) $(DEPS) shaders
	ar rcs $(LIB)/lib$(NAME).a $(OBJS)

$(O)/%.o:  %.c $(DEPS)
	$(CC) $(CFLAGS) $(INFLAGS) -c $< -o $@

