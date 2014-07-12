NAME=lwt
DESTDIR=/usr

CFLAGS=-Wall `pkg-config --cflags gtk+-3.0 vte-2.90` -I./src
LIBS=`pkg-config --libs gtk+-3.0 vte-2.90`

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $@ src/*.c $(LIBS)
	@gzip -c data/lwt.1 > lwt.1.gz

install: $(NAME)
	@mkdir -p "$(DESTDIR)/bin"
	install -m755 $(NAME) "$(DESTDIR)/bin"
	@mkdir -p "$(DESTDIR)/share/applications"
	install -m644 data/$(NAME).desktop "$(DESTDIR)/share/applications"
	@mkdir -p "$(DESTDIR)/share/man/man1"
	install -m644 $(NAME).1.gz "$(DESTDIR)/share/man/man1"

uninstall:
	rm -f "$(DESTDIR)/bin/$(NAME)"
	rm -f "$(DESTDIR)/share/applications/$(NAME).desktop"
	rm -f "$(DESTDIR)/share/man/man1/$(NAME).1.gz"

clean:
	rm -f $(NAME)
	rm -f $(NAME).1.gz
