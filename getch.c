#include <stdio.h>
#include <termios.h>

static struct termios old;
static struct termios new;

void initTermios(int echo)
{
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= echo ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &new);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo)
{
  char ch;

  initTermios(echo);
  ch = getchar();
  resetTermios();
  return (ch);
}

char getch(void)
{
  return (getch_(0));
}
