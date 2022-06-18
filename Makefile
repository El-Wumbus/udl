CC = gcc
CFLAGS = -g -Wall $(shell curl-config --cflags) $(shell curl-config --libs)
source = src/udl.c src/lib.h src/config.h
BIN = "dist/udl"
defualt: build

build: ${source}
	bash -c "mkdir -p dist"
	${CC} -o ${BIN} src/udl.c ${CFLAGS}

install:
	mkdir -p "${PREFIX}${DESTDIR}/usr/bin"
	mkdir -p "${DESTDIR}${PREFIX}/usr/share/doc"
	install -Dm755 dist/udl "${PREFIX}${DESTDIR}/usr/bin/udl"
	install -Dm644 README.rst "${DESTDIR}${PREFIX}/usr/share/doc/udl"

clean:
	$(RM) -rf $(BIN)