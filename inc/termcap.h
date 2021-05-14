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
# define TOCHKA_M "syntax error near unexpected token `;'"
# define PIPE_M "syntax error near unexpected token `|'"
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
void	check_flags(t_for_in_lexer *lex);
char	*free_null(char *l);
void	del_mas(t_for_in_lexer *lex);
void	del_free_par(t_for_in_parser **par);
void	del_masiv(char **l);
void	put5(t_for_in_lexer *lex, t_for_in_parser **par);
char	*find_in_envp(t_for_in_lexer *lex, char *s);
void	put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par);
void	dollar(t_for_in_lexer *lex, t_for_in_parser **par);
void	lexer6(t_for_in_lexer *lex,
			t_for_in_parser **par, t_for_in_terminal *t, t_envp *sh_envp);
void	lexer5(t_for_in_lexer *lex, t_for_in_parser **par);
void	lexer4(t_for_in_lexer *lex, t_for_in_parser **par);
void	lexer22(t_for_in_lexer *lex);
void	while_enter_term(t_for_in_terminal *t, t_envp *sh_envp);
void	while_enter_term2(t_for_in_terminal *t, t_envp *sh_envp);
void	del_term(t_for_in_terminal *t);
void	do_term(t_for_in_terminal *t);
int		en(char *s);
void	ch_line_par(t_for_in_parser **par, t_for_in_lexer *lex, char *s);
void	put2(t_for_in_lexer *lex, t_for_in_parser **par);
void	lexer7(t_for_in_lexer *lex, t_for_in_parser **par);
void	terminal_while3(t_for_in_terminal *t, t_envp *sh_envp);
void	terminal_while(t_for_in_terminal *t, t_envp *sh_envp);
void	terminal_while2(t_for_in_terminal *t);
void	put8(t_for_in_lexer *lex, t_for_in_parser **par);
void	free_par_one(t_for_in_lexer *lex, t_for_in_parser **par, int i);

#endif
