#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <vte/vte.h>

#include "lwt.h"

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	// Create window with a terminal emulator.
	GtkWindow *win = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	VteTerminal *vte = VTE_TERMINAL(vte_terminal_new());
	gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(vte));
	vte_terminal_set_font(vte, pango_font_description_from_string(LWT_FONT));
	vte_terminal_set_scrollback_lines(vte, LWT_LINES);

	// Connect signals.
	g_signal_connect(win, "delete_event", gtk_main_quit, NULL);
	g_signal_connect(win, "key-press-event", G_CALLBACK(on_win_key_press), vte);
	g_signal_connect(vte, "child-exited", gtk_main_quit, NULL);

	// Fork shell process.
	char *shell_argv[2] = {LWT_SHELL, NULL};
	vte_terminal_spawn_sync(vte, 0, NULL, shell_argv, NULL, 0, NULL, NULL, NULL, NULL, NULL);

	gtk_widget_show_all(GTK_WIDGET(win));
	gtk_main();

	return 0;
}

gboolean on_win_key_press(GtkWidget *win, GdkEventKey *event, VteTerminal *vte) {
	int mod = event->state & gtk_accelerator_get_default_mod_mask();
	VtePty *pty;

	// [ctrl] + [shift]
	if (mod == (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) {
		switch (event->keyval) {
		// [ctrl] + [shift] + [c]
		case GDK_KEY_C:
		case GDK_KEY_c:
			vte_terminal_copy_clipboard(vte);
			return TRUE;

		// [ctrl] + [shift] + [v]
		case GDK_KEY_V:
		case GDK_KEY_v:
			vte_terminal_paste_clipboard(vte);
			return TRUE;

		// [ctrl] + [shift] + [l]
		case GDK_KEY_L:
		case GDK_KEY_l:
			vte_terminal_reset(vte, TRUE, TRUE);
			pty = vte_terminal_get_pty(vte);
			write(vte_pty_get_fd(pty), "\x0C", 1);
			return TRUE;
		}
	}

	return FALSE;
}
