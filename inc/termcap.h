#ifndef TERMCAP_H
# define TERMCAP_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define FILE_HISTORY ".minishell_history"
# define TERMINALNAME "minishell$ "
# define ERROR_LEXER "minishell: error\n"
# define MANY_ARGS "minishell: too many arguments\n"
# define EXIT "minishell: "
# define NO_FILE_PUT "minishell: syntax error near unexpected token `newline'\n"
# include "minishell.h"

int		term_get_next_line(int fd, char **line, int reader);
int		term_putchar(int c);
char	*term_strjoin(char *s1, char *s2);
char	*str_delet_last_char(char *s1);
int		term_strlen(char *s);
int		term_strlen_mas(char **s);
char	**strjoin_for_mas(int len, t_for_in_terminal *t, char *line);
int		file(char *str);
void	terminal(int argc, char *argv[], t_envp *sh_envp);
int		file_mas(char **str, int i, t_for_in_terminal *t);
void	from_file(t_for_in_terminal *t);
void	*my_memmove(void *dst, const void *src, size_t len);
size_t	my_strlen(const char *s);
char	*term_strjoin_str(char *s1, char *s2);
int		term_strcmp(const char *s1, const char *s2);
void	up_terminal(t_for_in_terminal *t);
void	down_term(t_for_in_terminal *t);
char	*get_h_const(char *h_const);
int		gnl_second(int reader, char **buff);
void	line_from_terminal_to_lexer(char *s, t_for_in_terminal *t,
			t_envp *sh_envp);
char	*lexer_charjoin(char *s1, char c);
char	**strjoin_lex_mas(int len, t_for_in_lexer *t);
void	del_mas(t_for_in_lexer *lex);
char	**strjoin_pr_mas(int len, char **s, char *line);
int		open_APPEND_file_redirect(char *s);
int		open_TRUNC_file_redirect(char *s);
int		open_RDONLY_file_redirect(char *s);
void	del_settings_term(t_for_in_terminal *t);
void	do_settings_term(t_for_in_terminal *t);
void	exit_minishell(char *str, int reason, t_for_in_terminal *t);

#endif
