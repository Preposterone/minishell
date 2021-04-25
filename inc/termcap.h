#ifndef TERMCAP_H
# define TERMCAP_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define FILE_HISTORY ".minishell_history"
# define TERMINALNAME "minishell$ "
# include <term.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct s_for_in_terminal
{
	int				argc;
	char const		**argv;
	char const		**envp;
	int				l;
	char			**mas_his;
	char			**mas_line;
	struct termios	term;
	struct winsize	win;
	char			*term_name;
	int				n;
	char			*s;
	char			*sn;
	int				j;
	int				fd;
	int				i;
	char			str[2000];
	int				peri;
	int				len;
}					t_for_in_terminal;

typedef struct s_for_in_lexer
{
	int				argc;
	char const		**argv;
	char const		**envp;
	char			**mas_his;
	char			**mas_line;
	char			*line;
	char			*s;
	int				j;
	int				fd;
	int				i;
	int				len;
	char			*use;

	int				input;
	int				out;
	int				outend;
	int				pipe;
	int				l;
}					t_for_in_lexer;

typedef struct s_for_in_parser
{
	char			**arguments;
	char			**input;
	char			**out;
	char			**outend;
	int				j;
	struct s_for_in_parser		*next;
	struct s_for_in_parser		*previous;
	int key;
}					t_for_in_parser;


int		term_get_next_line(int fd, char **line, int reader);
int		term_putchar(int c);
char	*term_strjoin(char *s1, char *s2);
char	*str_delet_last_char(char *s1);
int		term_strlen(char *s);
int		term_strlen_mas(char **s);
char	**strjoin_for_mas(int len, t_for_in_terminal *t, char *line);
int		file(char *str);
void	terminal(int argc, char const *argv[], char const *envp[]);
int		file_mas(char **str, int i);
void	from_file(t_for_in_terminal *t);
void	*my_memmove(void *dst, const void *src, size_t len);
size_t	my_strlen(const char *s);
char	*term_strjoin_str(char *s1, char *s2);
int		term_strcmp(const char *s1, const char *s2);
void	up_terminal(t_for_in_terminal *t);
void	down_term(t_for_in_terminal *t);
char	*get_h_const(char *h_const);
int		gnl_second(int reader, char **buff);
void	line_from_terminal_to_lexer(char *s, t_for_in_terminal *t);
char	*lexer_charjoin(char *s1, char c);
char	**strjoin_lex_mas(int len, t_for_in_lexer *t);
void	del_mas(t_for_in_lexer *lex);
char	**strjoin_pr_mas(int len, char **s, char *line);

#endif
