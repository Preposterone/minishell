#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <term.h>
# include <sys/ioctl.h>

# ifndef MAX_FD
#  define MAX_FD 100
# endif

typedef struct s_envp
{
	char		**sh_envp;
	char		*sh_path;
	char		*sh_term;
	char		*sh_name;
	char		*sh_lvl;
	int			truefd0;
	int			truefd1;
	int			ispipe;
	int			isb_in;
}				t_envp;

typedef struct s_pipe_data
{
	int			pipe_fd[MAX_FD][2];
	pid_t		ch_id[MAX_FD];
	int			ch_index;
	int			ch_total;
}				t_pipe_data;

typedef struct s_for_in_terminal
{
	int				argc;
	char			**argv;
	char			**envp;
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
	int				del_len;
	int				key_main;
}					t_for_in_terminal;

typedef struct s_for_in_parser
{
	char					**arguments;
	int						input;
	int						output;
	int						j;
	struct s_for_in_parser	*next;
	struct s_for_in_parser	*previous;
	int						key;
}					t_for_in_parser;

typedef struct s_for_in_lexer
{
	int				argc;
	char const		**argv;
	char			**envp;
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
	int				pipe_ch;
	int				dollar;
	int				l;
	int				*flags_arg;
	int				flags_check;
	int				exit;
	int				c_i;
	char			*c_s;
	char			*k_s;
	int				k_i;
	int				nr;
	char			*nr_str;
	int				nr_i;
	int				nr_j;
	char			*dol_str;
	int				if_i;
	int				ex_red;
	t_for_in_parser	*t_p;
}					t_for_in_lexer;

#endif
