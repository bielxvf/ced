#if !defined(TOOEE_H)
#define TOOEE_H

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

void tooee_init();
void tooee_deinit();

void tooee_screen_clear();

void tooee_cursor_move_up();
void tooee_cursor_move_down();
void tooee_cursor_move_right();
void tooee_cursor_move_left();
void tooee_cursor_move(uint32 x, uint32 y);

void tooee_write(const char *string);
void tooee_write_at(const char* string, uint32 x, uint32 y);

#endif /* TOOEE_H */

#if defined(TOOEE_IMPLEMENTATION)

struct termios _tooee_termios_original;
struct termios _tooee_termios_actual;

void tooee_init()
{
  tcgetattr(STDIN_FILENO, &_tooee_termios_original);

  _tooee_termios_actual = _tooee_termios_original;
  _tooee_termios_actual.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  _tooee_termios_actual.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  _tooee_termios_actual.c_oflag &= ~(OPOST);
  _tooee_termios_actual.c_cflag |= (CS8);

  _tooee_termios_actual.c_cc[VMIN] = 1;
  _tooee_termios_actual.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_tooee_termios_actual);
}

void tooee_deinit()
{
  tooee_screen_clear();
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_tooee_termios_original);
}

inline void tooee_screen_clear()
{
  write(STDOUT_FILENO, "\033[2J\033[H", 7);
}

inline void tooee_cursor_move_up()
{
  write(STDOUT_FILENO, "\033[A", 3);
}

inline void tooee_cursor_move_down()
{
  write(STDOUT_FILENO, "\033[B", 3);
}

inline void tooee_cursor_move_right()
{
  write(STDOUT_FILENO, "\033[C", 3);
}

inline void tooee_cursor_move_left()
{
  write(STDOUT_FILENO, "\033[D", 3);
}

void tooee_cursor_move(uint32 x, uint32 y)
{
}

#endif /* TOOEE_IMPLEMENTATION */
