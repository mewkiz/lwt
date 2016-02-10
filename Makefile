DESTDIR=/usr

CFLAGS=-Wall `pkg-config --cflags gtk+-3.0 vte-2.91` -I./src
LIBS=`pkg-config --libs gtk+-3.0 vte-2.91` -liniparser

all: lwt

lwt: src/lwt.c
	${CC} ${CFLAGS} -o $@ $< ${LIBS}
	@gzip -c data/lwt.1 > lwt.1.gz

.PHONY: install uninstall clean

install: lwt
	@mkdir -p "${DESTDIR}/bin"
	install -m755 lwt "${DESTDIR}/bin"
	@mkdir -p "${DESTDIR}/share/applications"
	install -m644 data/lwt.desktop "${DESTDIR}/share/applications"
	@mkdir -p "${DESTDIR}/share/man/man1"
	install -m644 lwt.1.gz "${DESTDIR}/share/man/man1"

uninstall:
	rm -f "${DESTDIR}/bin/lwt"
	rm -f "${DESTDIR}/share/applications/lwt.desktop"
	rm -f "${DESTDIR}/share/man/man1/lwt.1.gz"

clean:
	rm -f lwt
	rm -f lwt.1.gz
