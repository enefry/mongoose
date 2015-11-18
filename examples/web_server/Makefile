PROG = web_server
SOURCES = $(PROG).c DataBuffer.c ../../mongoose.c
CFLAGS = -W -Wall -I../.. $(CFLAGS_EXTRA)
OPENSSL_FLAGS = -DMG_ENABLE_SSL -lssl

# PolarSSL paths and flags
POLARSSL_PATH = /usr/local
POLARSSLCOMPAT_PATH = ./../../../polar
SOURCES_POLAR = $(SOURCES) $(POLARSSLCOMPAT_PATH)/polarssl_compat.c
INCDIR_POLAR = -I$(POLARSSLCOMPAT_PATH) -I$(POLARSSL_PATH)/include
LDFLAGS_POLAR = -L$(POLARSSL_PATH)/lib -lmbedtls
CFLAGS_POLAR = $(CFLAGS) $(INCDIR_POLAR) -DMG_ENABLE_SSL


all: $(PROG)

$(PROG): $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(PROG).exe: $(SOURCES)
	cl $(SOURCES) /I../.. /MD /Fe$@

openssl:
	$(CC) -o $(PROG) $(SOURCES) $(CFLAGS) $(OPENSSL_FLAGS)

polarssl:
	$(CC) -o $(PROG) $(SOURCES_POLAR) $(LDFLAGS_POLAR) $(CFLAGS_POLAR)
	
clean:
	rm -rf *.gc* *.dSYM *.exe *.obj *.o a.out $(PROG)
