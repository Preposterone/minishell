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

void	check_flags3(t_for_in_lexer *lex, t_for_in_lex_two *k)
{
	if (lex->line[k->i] < 127
		&& lex->flags_arg[(int)lex->line[k->i]] == 0)
		k->s = lexer_charjoin(k->s, lex->line[k->i]);
	if ((int)lex->line[k->i] < 127)
		lex->flags_arg[(int)lex->line[k->i]] = 1;
	return ;
}

void	check_flags2(t_for_in_lexer *lex, t_for_in_lex_two *k)
{
	if (lex->line[0] == '-' && lex->line[1] != '-' && lex->line[1] != '\0')
	{
		k->i++;
		k->s = lexer_charjoin(k->s, lex->line[k->i]);
		while (lex->line[++k->i])
		{
			if ((lex->line[k->i] >= 65 && lex->line[k->i] <= 90)
				|| (lex->line[k->i] >= 97 && lex->line[k->i] <= 122))
			{
				check_flags3(lex, k);
			}
			else
			{
				k->s = free_null(k->s);
				return ;
			}
		}
	}
	else
	{
		lex->flags_check = 0;
		k->s = free_null(k->s);
		return ;
	}
}

void	check_flags(t_for_in_lexer *lex)
{
	t_for_in_lex_two	k;

	k.i = 0;
	if (!lex->line)
		return ;
	k.s = (char *)ft_calloc(1, sizeof(char));
	k.i = -1;
	check_flags2(lex, &k);
	if (k.s[1] == '\0')
	{
		free(k.s);
		k.s = NULL;
		k.s = (char *)ft_calloc(1, sizeof(char));
	}
	lex->flags_check = 1;
	free(lex->line);
	lex->line = NULL;
	lex->line = k.s;
}
