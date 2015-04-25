#ifndef __LWT_H__
#define __LWT_H__

#define LWT_FONT "Fixed 12"
#define LWT_LINES 65535
#define LWT_SHELL "/bin/bash"

gboolean on_win_key_press(GtkWidget *win, GdkEventKey *event, VteTerminal *vte);

#endif /* #ifndef __LWT_H__ */
