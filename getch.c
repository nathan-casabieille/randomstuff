#include <stdio.h>
#include <termios.h>

void initTermios(struct termios *term)
{
    struct termios new_term;

    tcgetattr(0, term);
    new_term = *term;
    new_term.c_lflag &= ~ICANON;
    new_term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_term);
}

void resetTermios(struct termios *term)
{
    tcsetattr(0, TCSANOW, term);
}

char getch(void)
{
    char ch;
    struct termios term;

    initTermios(&term);
    ch = getchar();
    resetTermios(&term);
    return (ch);
}
