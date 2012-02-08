#ifndef __LWT_H__
#define __LWT_H__

#define LWT_FONT  "Fixed 9"
#define LWT_LINES 65535
#define LWT_SHELL "/bin/bash"

void lwt_spawn(void);
gboolean on_win_key_press(GtkWidget *win, GdkEventKey *event, VteTerminal *vte);
void lwt_set_geometry_hints(GtkWindow *win, VteTerminal *vte);

#endif /* #ifndef __LWT_H__ */
