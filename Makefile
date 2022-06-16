CC = gcc
CFLAGS = -g -Wall $(shell curl-config --cflags) $(shell curl-config --libs)
source = src/udl.c src/lib.h src/config.h
BIN = "dist/udl"
defualt: build

build: ${source}
	mkdir -p dist
	${CC} -o ${BIN} src/udl.c ${CFLAGS}

clean:
	$(RM) -rf $(BIN)