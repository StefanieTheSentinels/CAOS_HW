CC = clang
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L.
DYLIB_FLAGS = -dynamiclib -install_name @rpath/libshared.dylib

STATIC_LIB = libstatic.a
SHARED_LIB = libshared.dylib

PROGRAM_NORMAL = program
PROGRAM_LINK_INTERPOSE = program_link_interpose
LOAD_INTERPOSE_LIB = libload_interpose.dylib

all: $(PROGRAM_NORMAL) $(PROGRAM_LINK_INTERPOSE) $(LOAD_INTERPOSE_LIB)

fred.o: fred.c lib.h
	$(CC) $(CFLAGS) -c fred.c

john.o: john.c lib.h
	$(CC) $(CFLAGS) -c john.c

bill.o: bill.c lib.h
	$(CC) $(CFLAGS) -fPIC -c bill.c

sam.o: sam.c lib.h
	$(CC) $(CFLAGS) -fPIC -c sam.c

program.o: program.c lib.h
	$(CC) $(CFLAGS) -c program.c

link_interpose.o: link_interpose.c
	$(CC) $(CFLAGS) -c link_interpose.c

$(STATIC_LIB): fred.o john.o
	ar rcs $(STATIC_LIB) fred.o john.o

$(SHARED_LIB): bill.o sam.o
	$(CC) $(DYLIB_FLAGS) -o $(SHARED_LIB) bill.o sam.o -lm

$(PROGRAM_NORMAL): program.o $(STATIC_LIB) $(SHARED_LIB)
	$(CC) $(CFLAGS) -o $(PROGRAM_NORMAL) program.o $(LDFLAGS) -lstatic -lshared -lm -Wl,-rpath,.

$(PROGRAM_LINK_INTERPOSE): program.o link_interpose.o $(STATIC_LIB) $(SHARED_LIB)
	$(CC) $(CFLAGS) -o $(PROGRAM_LINK_INTERPOSE) program.o link_interpose.o $(LDFLAGS) -lstatic -lshared -lm -Wl,-rpath,.

$(LOAD_INTERPOSE_LIB): load_interpose.c lib.h $(SHARED_LIB)
	$(CC) $(CFLAGS) -dynamiclib -o $(LOAD_INTERPOSE_LIB) load_interpose.c $(LDFLAGS) -lshared -Wl,-rpath,.

run: $(PROGRAM_NORMAL)
	./$(PROGRAM_NORMAL)

run-link: $(PROGRAM_LINK_INTERPOSE)
	./$(PROGRAM_LINK_INTERPOSE)

run-load: $(PROGRAM_NORMAL) $(LOAD_INTERPOSE_LIB)
	DYLD_INSERT_LIBRARIES=./$(LOAD_INTERPOSE_LIB) ./$(PROGRAM_NORMAL)

libs: $(PROGRAM_NORMAL)
	otool -L ./$(PROGRAM_NORMAL)

clean:
	rm -f *.o *.a *.dylib $(PROGRAM_NORMAL) $(PROGRAM_LINK_INTERPOSE)