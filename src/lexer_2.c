#include "minishell.h"

char	*free_null(char *l)
{
	if (l)
		free(l);
	return (NULL);
}

void	del_mas(t_for_in_lexer *lex)
{
	int	i;

	i = 0;
	while (lex->mas_line[i])
	{
		free((void *)lex->mas_line[i]);
		lex->mas_line[i] = NULL;
		i++;
	}
	free((void **)lex->mas_line);
	lex->mas_line = NULL;
}

void	put5(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if ((*par)->output > 0)
		close((*par)->output);
	(*par)->output = open_APPEND_file_redirect(lex->line);
	if ((*par)->output < 0)
	{
		lex->ex_red = 1;
		lex->line = free_null(lex->line);
		return ;
	}
	lex->outend = 0;
}

void 	lexer22(t_for_in_lexer *lex)
{
	if (lex->s[lex->i] == '\0')
	{
		lex->exit = 1;
		lex->line = free_null(lex->line);
		ft_puterrln(M_QUOTES);
		g_all.exit_code = 258;
		return ;
	}
	lex->if_i = 1;
}

void	ch_line_par(t_for_in_parser **par, t_for_in_lexer *lex, char *s)
{
	if ((*par)->arguments[0] == NULL
		&& (*par)->input == -2 && (*par)->output == -2)
	{
		lex->exit = 1;
		ft_puterrln(s);
		g_all.exit_code = 258;
	}
}
