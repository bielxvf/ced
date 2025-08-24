#include "types.h"

#define TUI_IMPLEMENTATION
#include "tui.h"

boolean string_equal(const char *sl, const char *sr)
{
  while (*sl != '\0' && *sr != '\0') {
    if (*sl++ != *sr++) {
      return FALSE;
    }
  }

  return *sl == *sr;
}

#include <stdio.h>

#define UNREACHABLE \
  do {                                              \
    fprintf(                                        \
      stderr,                                       \
      "Error: Reached unreachable code at %s:%d\n", \
      __FILE__,                                     \
      __LINE__                                      \
    );                                              \
    abort();                                        \
  } while (FALSE)

int main(int argc, char **argv)
{
  tui_init();
  atexit(tui_deinit);

  char c;
  while (read(STDIN_FILENO, &c, 1)) {
    switch (c) { /* normal mode */
    case ':': {
      tui_cursor_move(10, -10);
      write(STDOUT_FILENO, "\033[2K", 4);
      write(STDOUT_FILENO, ":", 1);
      char cmd[1024];
      char l;
      int i = 0;
      while (read(STDIN_FILENO, &l, 1)) {
        if (l == '\r') {
          cmd[i] = '\0';
          break;
        } else {
          write(STDOUT_FILENO, &l, 1);
          cmd[i++] = l;
        }
      }

      if (string_equal("q", cmd) || string_equal("quit", cmd)) {
        return 0;
      }
    }
    case 'h': {
      tui_cursor_move_left();
    } break;
    case 'j': {
      tui_cursor_move_down();
    } break;
    case 'k': {
      tui_cursor_move_up();
    } break;
    case 'l': {
      tui_cursor_move_right();
    } break;
    case 'i': { /* insert mode */
      char l;
      while (read(STDIN_FILENO, &l, 1)) {
        switch (l) {
        case '\033': { /* TODO: add ^C */
          goto endwhile;
        } break;
        case 127:
        case '\b': {
          write(STDOUT_FILENO, "\b \b", 3);
        } break;
        case '\r': {
          write(STDOUT_FILENO, "\n" , 1);
          write(STDOUT_FILENO, "\033[1G", 4);
        } break;
        default: {
          write(STDOUT_FILENO, &l, 1);
        } break;
        }
      }
      endwhile:
    } break;
    }
  }

  return 0;
}
