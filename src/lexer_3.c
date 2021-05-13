#include "minishell.h"

int find_in_envp2(t_for_in_lexer *lex, char **s)
{
	while (lex->envp[lex->nr_j] != NULL)
	{
		lex->nr_i = 0;
		while (lex->envp[lex->nr_j][lex->nr_i] && lex->envp[lex->nr_j][lex->nr_i] != '=')
			lex->nr_str = lexer_charjoin(lex->nr_str, lex->envp[lex->nr_j][lex->nr_i++]);
		if (!term_strcmp(lex->nr_str, *s))
		{
			free(*s);
			free(lex->nr_str);
			lex->nr_str = NULL;
			while (lex->envp[lex->nr_j][++lex->nr_i])
				lex->nr_str = lexer_charjoin(lex->nr_str, lex->envp[lex->nr_j][lex->nr_i]);
			return (1);
		}
		free(lex->nr_str);
		lex->nr_str = (char *)ft_calloc(1, sizeof(char));
		lex->nr_j++;
	}
	return (0);
}

char *find_in_envp(t_for_in_lexer *lex, char *s)
{
	lex->nr_j = 0;
	lex->nr_str = (char *)ft_calloc(1, sizeof(char));
	if (s == NULL || lex->envp == NULL)
	{
		if (s != NULL)
			free(s);
		return (NULL);
	}
	lex->nr = find_in_envp2(lex, &s);
	if (lex->nr == 1)
		return (lex->nr_str);
	free(lex->nr_str);
	free(s);
	return (NULL);
}
