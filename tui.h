#if !defined(TUI_H)
#define TUI_H

#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

void tui_init();
void tui_deinit();

void tui_screen_clear();

void tui_cursor_move_up();
void tui_cursor_move_down();
void tui_cursor_move_right();
void tui_cursor_move_left();
void tui_cursor_move(int32 ncols, int32 nlines);

void tui_write(const char *string);
void tui_write_at(const char* string, uint32 x, uint32 y);

#endif /* TUI_H */

#if defined(TUI_IMPLEMENTATION)

struct termios _tui_termios_original;
struct termios _tui_termios_actual;

void tui_init()
{
  tcgetattr(STDIN_FILENO, &_tui_termios_original);

  _tui_termios_actual = _tui_termios_original;
  _tui_termios_actual.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  _tui_termios_actual.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  _tui_termios_actual.c_oflag &= ~(OPOST);
  _tui_termios_actual.c_cflag |= (CS8);

  _tui_termios_actual.c_cc[VMIN] = 1;
  _tui_termios_actual.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_tui_termios_actual);

  tui_screen_clear();
}

void tui_deinit()
{
  tui_screen_clear();
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_tui_termios_original);
}

inline void tui_screen_clear()
{
  write(STDOUT_FILENO, "\033[2J\033[H", 7);
}

inline void tui_cursor_move_up()
{
  write(STDOUT_FILENO, "\033[A", 3);
}

inline void tui_cursor_move_down()
{
  write(STDOUT_FILENO, "\033[B", 3);
}

inline void tui_cursor_move_right()
{
  write(STDOUT_FILENO, "\033[C", 3);
}

inline void tui_cursor_move_left()
{
  write(STDOUT_FILENO, "\033[D", 3);
}

void tui_cursor_move(int32 ncols, int32 nlines)
{
  write(STDOUT_FILENO, "\033[6n", 4);
  char buf[32];
  uint i;
  for (i = 0; i < 32; i++) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) {
      break;
    }

    if (buf[i] == 'R') {
      break;
    }
  }
  buf[i] = '\0';

  if (buf[0] != '\033' || buf[1] != '[') {
    return;
  }

  uint32 line, col;
  sscanf(&buf[2], "%d;%d", &line, &col);

  printf("\033[%d;%dH", line + nlines, col + ncols);
  fflush(stdout);
}

#endif /* TUI_IMPLEMENTATION */
