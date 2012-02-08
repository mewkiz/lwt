#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <vte/vte.h>

#include "lwt.h"

int main(int argc, char **argv)
{
   gtk_init(&argc, &argv);
   lwt_spawn();
   gtk_main();
   return 0;
}

void lwt_spawn(void)
{
   GtkWindow *win;
   VteTerminal *vte;
   char *argv[2] = {LWT_SHELL, NULL};

   win = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
   vte = VTE_TERMINAL(vte_terminal_new());
   gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(vte));
   g_object_connect
   (
      win,
      "signal::delete_event", gtk_main_quit, NULL,
      "signal::key-press-event", on_win_key_press, vte,
      NULL
   );
   g_signal_connect(vte, "child-exited", gtk_main_quit, NULL);
   vte_terminal_set_audible_bell(vte, FALSE);
   vte_terminal_set_font_from_string(vte, LWT_FONT);
   vte_terminal_set_scrollback_lines(vte, LWT_LINES);
   lwt_set_geometry_hints(win, vte);
   vte_terminal_fork_command_full
   (
      vte,  // terminal
      0,    // pty_flags
      NULL, // working_directory
      argv, // argv
      NULL, // envv
      0,    // spawn_flags
      NULL, // child_setup
      NULL, // child_setup_data
      NULL, // child_pid
      NULL  // error
   );
   gtk_widget_show_all(GTK_WIDGET(win));
}

gboolean on_win_key_press(GtkWidget *win, GdkEventKey *event, VteTerminal *vte)
{
   int mod = event->state & gtk_accelerator_get_default_mod_mask();

   // [ctrl] + [shift]
   if(mod == (GDK_CONTROL_MASK | GDK_SHIFT_MASK))
   {
      switch(event->keyval)
      {
      // [ctrl] + [shift] + [c]
      case GDK_C:
      case GDK_c:
         vte_terminal_copy_clipboard(vte);
         return TRUE;

      // [ctrl] + [shift] + [v]
      case GDK_V:
      case GDK_v:
         vte_terminal_paste_clipboard(vte);
         return TRUE;

      // [ctrl] + [shift] + [l]
      case GDK_L:
      case GDK_l:
         vte_terminal_reset(vte, TRUE, TRUE);
         write(vte_terminal_get_pty(vte), "\x0C", 1);
         return TRUE;
      }
   }
   return FALSE;
}

void lwt_set_geometry_hints(GtkWindow *win, VteTerminal *vte)
{
   GdkGeometry hints;
   GtkBorder *border;
   gint char_width, char_height;

   gtk_widget_style_get(GTK_WIDGET(vte), "inner-border", &border, NULL);
   char_width = vte_terminal_get_char_width(vte);
   char_height = vte_terminal_get_char_height(vte);
   hints.base_width = border->left + border->right;
   hints.base_height = border->top + border->bottom;
   hints.min_width = char_width + border->left + border->right;
   hints.min_height = char_height + border->top + border->bottom;
   hints.width_inc = char_width;
   hints.height_inc = char_height;
   gtk_window_set_geometry_hints
   (
      win,
      GTK_WIDGET(vte),
      &hints,
      GDK_HINT_MIN_SIZE | GDK_HINT_RESIZE_INC
   );
}
