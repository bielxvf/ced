#include "types.h"

#define STRING_IMPLEMENTATION
#include "string.h"

#define TOOEE_IMPLEMENTATION
#include "tooee.h"

#include <stdio.h>

#define UNREACHABLE \
  do {                                              \
    fprintf(                                        \
      stderr,                                       \
      "Error: Reached unreachable code at %s:%d\n", \
      __FILE__,                                     \
      __LINE__                                      \
    );                                              \
  } while (FALSE)

int main(int argc, char **argv)
{
  tooee_init();
  atexit(tooee_deinit);

  char c;
  while (read(STDIN_FILENO, &c, 1)) {
    switch (c) {
    case ':': {
      char cmd;
      read(STDIN_FILENO, &cmd, 1);
      switch (cmd) {
      case 'q': {
        return 0;
      } break;
      default: {
        UNREACHABLE;
      } break;
      }
    }
    case 'h': {
      tooee_cursor_move_left();
    } break;
    case 'j': {
      write(STDOUT_FILENO, "\033[B", 3);
    } break;
    case 'k': {
      write(STDOUT_FILENO, "\033[A", 3);
    } break;
    case 'l': {
      write(STDOUT_FILENO, "\033[C", 3);
    } break;
    case 'i': {
      char l;
      while (read(STDIN_FILENO, &l, 1)) {
        if (l == '\033') { /* TODO: add ^C */
          break;
        }

        if (l == '\r') {
          write(STDOUT_FILENO, "\n" , 1);
          write(STDOUT_FILENO, "\033[1G", 4);
        } else {
          write(STDOUT_FILENO, &l, 1);
        }
      }
    } break;
    }
  }

  return 0;
}
