# lwt

`lwt` is a lightweight terminal emulator based on the [VTE] and [GTK] libraries.

[VTE]: https://developer.gnome.org/vte/
[GTK]: http://www.gtk.org/

## Key bindings

The default key bindings of VTE are extended with the following:

- `[ctrl] + [shift] + 'c'`
	- Copy selection
- `[ctrl] + [shift] + 'v'`
	- Paste
- `[ctrl] + [shift] + 'l'`
	- Reset scrollback
- `[ctrl] + '+'`
    - Increase font size
- `[ctrl] + '-'`
    - Decrease font size

## Configuration

Store a modified copy of the example configuration file [lwt.conf](lwt.conf) in `~/.config/lwt/lwt.conf`.

Example config:
```
[lwt]
font = "Fixed 11"
shell = "/usr/bin/fish"
```

## Packages

Arch Linux users can install `lwt` using the following [AUR package](https://aur.archlinux.org/packages/lwt-git/).

## Public domain

The source code and any original content of this repository is hereby released into the [public domain].

[public domain]: https://creativecommons.org/publicdomain/zero/1.0/
