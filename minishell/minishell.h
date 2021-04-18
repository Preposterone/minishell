

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>


# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>


# include <math.h>
# include <unistd.h>




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
	int peri;

}   t_for_in_terminal;


int			get_next_line(int fd, char **line);
int			ft_putchar(int c);
char		*ft_strjoin(char *s1, char *s2);
char		*str_delet_last_char(char *s1);
int			ft_strlen(char *s);
int			ft_strlen_mas(char **s);
char		**strjoin_for_mas(int len, char **s, char *line);
int			file(char *str);

void		terminal(int argc, char const *argv[], char const *envp[]);
void		terminal_do_write(t_for_in_terminal *t);
void		terminal_do_elseif(t_for_in_terminal *t);
void		terminal_do_if(t_for_in_terminal *t);
int			file_mas(char **str, int i);
void		from_file(t_for_in_terminal *t);
int			ft_strcmp(const char *s1, const char *s2);




#endif
