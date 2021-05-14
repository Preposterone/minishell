#include "minishell.h"

int	en(char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL || !s[i] || s[i] == '\0')
		return (0);
	while (s && s[i] && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	put2(t_for_in_lexer *lex, t_for_in_parser **par)
{
	t_for_in_parser	*t_p;

	t_p = *par;
	(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
	(*par)->next->key = (*par)->key + 1;
	*par = (*par)->next;
	(*par)->previous = t_p;
	(*par)->arguments = (char **)ft_calloc(1, sizeof(char *));
	(*par)->output = -2;
	(*par)->input = -2;
	lex->pipe = 0;
}

void	lexer7(t_for_in_lexer *lex, t_for_in_parser **par)
{
	(*par) = ft_calloc(1, sizeof(t_for_in_parser));
	(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
	lex->t_p = *par;
	(*par) = (*par)->next;
	(*par)->key = 1;
	(*par)->previous = lex->t_p;
	(*par)->arguments = (char **)ft_calloc(1, sizeof(char *));
	(*par)->output = -2;
	(*par)->input = -2;
	lex->if_i = 1;
}

void	put8(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if ((*par)->input > 0)
		close((*par)->input);
	(*par)->input = open_RDONLY_file_redirect(lex->line);
	if ((*par)->input < 0)
	{
		lex->exit = 1;
		lex->line = free_null(lex->line);
		return ;
	}
	lex->input = 0;
}
