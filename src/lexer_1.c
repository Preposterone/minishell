#include "minishell.h"

void	del_masiv(char **l)
{
	int	i;

	i = 0;
	if (l != NULL)
	{
		while (l[i] != NULL)
		{
			l[i] = free_null(l[i]);
			i++;
		}
		free(l);
	}
}

void	del_free_par(t_for_in_parser **par)
{
	int	i;
	int	j;

	j = 0;
	while (*par != NULL)
	{
		i = 0;
		while ((*par)->arguments != NULL && (*par)->arguments[i] != NULL)
		{
			free((*par)->arguments[i]);
			(*par)->arguments[i] = NULL;
			i++;
		}
		free((*par)->arguments);
		free((*par)->next);
		*par = (*par)->previous;
		j++;
	}
	free(*par);
}

void	check_flags2(t_for_in_lexer *lex)
{
	if (lex->c_i == -1)
	{
		lex->flags_check = 0;
		free(lex->c_s);
		lex->c_s = NULL;
		return ;
	}
	if (lex->c_s[1] == '\0')
	{
		free(lex->c_s);
		lex->c_s = NULL;
		lex->c_s = (char *)ft_calloc(1, sizeof(char));
	}
	lex->flags_check = 1;
	free(lex->line);
	lex->line = NULL;
	lex->line = lex->c_s;
}

void	check_flags3(t_for_in_lexer *lex)
{
	if (lex->line[lex->c_i] < 127
		&& lex->flags_arg[(int)lex->line[lex->c_i]] == 0)
		lex->c_s = lexer_charjoin(lex->c_s, lex->line[lex->c_i]);
	if ((int)lex->line[lex->c_i] < 127)
		lex->flags_arg[(int)lex->line[lex->c_i]] = 1;
}

void	check_flags(t_for_in_lexer *lex)
{
	if (!lex->line)
		return ;
	lex->c_s = (char *)ft_calloc(1, sizeof(char));
	lex->c_i = -1;
	if (lex->line[0] == '-' && lex->line[1] != '-' && lex->line[1] != '\0')
	{
		lex->c_i++;
		lex->c_s = lexer_charjoin(lex->c_s, lex->line[lex->c_i]);
		while (lex->line[++lex->c_i])
		{
			if ((lex->line[lex->c_i] >= 65 && lex->line[lex->c_i] <= 90)
				|| (lex->line[lex->c_i] >= 97 && lex->line[lex->c_i] <= 122))
				check_flags3(lex);
			else
			{
				lex->c_s = free_null(lex->c_s);
				return ;
			}
		}
	}
	check_flags2(lex);
}
