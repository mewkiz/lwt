#ifndef __LWT_H__
#define __LWT_H__

#define FONT  "Fixed 9"
#define LINES 65535
#define SHELL "/bin/bash"

gboolean on_win_key_press(GtkWidget *win, GdkEventKey *event, VteTerminal *vte);

#endif /* #ifndef __LWT_H__ */
