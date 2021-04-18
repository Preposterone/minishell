

#ifndef MINISHELL_H
# define MINISHELL_H

#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>


typedef struct for_in_terminal
{
    int argc;
    char const **argv;
    char const **envp;
    int l;
    char **mas_his;
    struct termios term;
	struct winsize win;
	char *term_name;
	int n;
	char *s;
	char *sn;
	int j;
	int fd;
    int i;
    char str[2000];

}   t_for_in_terminal;



int ft_putchar(int c);
char				*ft_strjoin(char *s1, char *s2);
char				*str_delet_last_char(char *s1);
int			ft_strlen(char *s);
int			ft_strlen_mas(char **s);
char **strjoin_for_mas(int len, char **s, char *line);
int file(char *str);

void terminal(int argc, char const *argv[], char const *envp[]);
void terminal_do_write(t_for_in_terminal *t);
void terminal_do_elseif(t_for_in_terminal *t);
void terminal_do_if(t_for_in_terminal *t);




#endif
