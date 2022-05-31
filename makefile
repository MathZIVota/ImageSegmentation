CC=g++

CFLAGS=-c -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings \
 -Wcast-align -Wformat-security -Wmissing-format-attribute  -Wno-long-long \
 -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations  \
 -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
 -Wunused -Wuninitialized -fPIC 

all:a clean 

a: stb_hello.o
		$(CC) stb_hello.o -o a 
stb_hello.o: stb_hello.c
		$(CC) -c stb_hello.c 
clean:
		rm stb_hello.o