#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "work_with_file.c"
#include "ft_strjoin.c"



#include <stdlib.h>

//gcc -g work_in_line -ltermcap
// ./a.out



int ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int main(int argc, char const *argv[], char const *envp[])
{
    char str[2000];
    int l;
    struct termios term;
	struct winsize win;
	char *term_name = "xterm-256color";
	int n;
	char *s;
	int fd;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ECHO);
    term.c_lflag &= ~(ICANON);
    tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	n = 0;
	write(1, &str, 100);
	while (strcmp(str, "\4"))
	{
		tputs(save_cursor, 1, ft_putchar);
		do
		{
			ioctl(0, FIONREAD, &n);
			l = read(0, str, n);
			str[l] = 0;
			if (!strcmp(str, "\e[A"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "previous", 8);
			}
			else if (!strcmp(str, "\e[B"))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "next", 4);
			}
			else if (strcmp(str, key_backspace) && !strcmp(str, "\177"))
			{
				s = str_delet_last_char(s);
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
			}
			else if (!strcmp(str, "\e[D"))
				write(1, "left", 0);
			else if (!strcmp(str, "\e[C"))
				write(1, "right", 0);
			else
			{
				s = ft_strjoin(s, str);
				write (1, str, l);
			}
		} 
		while (strcmp(str, "\n") && strcmp(str, "\4"));
		{
			if (strcmp(s, "\n"))
				file(s);
			s = NULL;
		}
	}
    write(1, "\n", 1);
    return 0;
}
