CC=gcc
CFLAGS=
GERANUM_OBJ=geranum.o  
CRIPTO_OBJ=cripto.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: geranum cripto

geranum: $(GERANUM_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cripto: $(CRIPTO_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o geranum cripto

.PHONY: geranum cripto clean