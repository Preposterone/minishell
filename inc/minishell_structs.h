#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H
# include "minishell.h"

typedef struct	s_envp
{
	char	**sh_envp;	//malloc, for set / unset
	char	*sh_path;	//malloc, for executor logic
	char	*sh_term;	//malloc, for termcap logic
}				t_envp;

#endif
