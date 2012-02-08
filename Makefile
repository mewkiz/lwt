BIN_NAME=lwt
DESTDIR=/usr

CC=clang
CFLAGS=-Wall `pkg-config --cflags gtk+-2.0 vte` -I./src
LIBS=-lgtk-x11-2.0 -lgobject-2.0 -lvte

all: $(BIN_NAME)

$(BIN_NAME):
	$(CC) $(CFLAGS) -o $@ src/*.c $(LIBS)
	@gzip -c data/lwt.1 > lwt.1.gz

install:
	@mkdir -p "$(DESTDIR)/bin/"
	install -m755 $(BIN_NAME) "$(DESTDIR)/bin/"
	@mkdir -p "$(DESTDIR)/share/applications/"
	install -m644 data/$(BIN_NAME).desktop "$(DESTDIR)/share/applications/"
	@mkdir -p "$(DESTDIR)/share/man/man1/"
	install -m644 $(BIN_NAME).1.gz "$(DESTDIR)/share/man/man1/"

uninstall:
	rm -f "$(DESTDIR)/bin/$(BIN_NAME)"
	rm -f "$(DESTDIR)/share/applications/$(BIN_NAME).desktop"
	rm -f "$(DESTDIR)/share/man/man1/$(BIN_NAME).1.gz"

clean:
	rm -f $(BIN_NAME)
	rm -f $(BIN_NAME).1.gz
