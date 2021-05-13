#include "minishell.h"

void	put4(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (term_strlen_mas((*par)->arguments) == 1 || lex->flags_check == 1)
		check_flags(lex);
	if (lex->line != NULL && lex->line[0] != '\0')
		(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments)
				+ 1, (*par)->arguments, lex->line);
}

void	put3(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if ((*par)->output > 0)
		close((*par)->output);
	(*par)->output = open_TRUNC_file_redirect(lex->line);
	if ((*par)->output < 0)
	{
		lex->exit = 1;
		lex->line = free_null(lex->line);
		return ;
	}
	lex->out = 0;
}

void	put2(t_for_in_lexer *lex, t_for_in_parser **par)
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

void	put1(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->input == 1)
		put2(lex, par);
	else if (lex->out == 1)
		put3(lex, par);
	else if (lex->dollar == 1)
	{
		(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments)
				+ 1, (*par)->arguments, lex->line);
		lex->dollar = 0;
	}
	else if (lex->outend == 1)
		put5(lex, par);
	else
		put4(lex, par);
}

void	put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par)
{
	t_for_in_parser	*t_p;

	if (lex->line && lex->line != NULL)
	{
		if (lex->pipe == 1)
		{
			ch_line_par(par, lex, PIPE_M);
			if (lex->exit != 1)
			{
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
		}
		put1(lex, par);
		lex->line = free_null(lex->line);
		lex->j++;
	}
	else if (lex->outend == 1 || lex->out == 1 || lex->input == 1 || lex->pipe == 1)
	{
		lex->exit = 1;
		ft_puterrln(RED_WHERE);
	}
}
