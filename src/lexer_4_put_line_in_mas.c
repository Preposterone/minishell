#include "minishell.h"

void	put4(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (term_strlen_mas((*par)->arguments) == 1 || lex->flags_check == 1)
		check_flags(lex);
	if (lex->line != NULL)
	{
		(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments)
				+ 1, (*par)->arguments, lex->line);
	}
}

void	put3(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if ((*par)->output > 0)
		close((*par)->output);
	(*par)->output = open_TRUNC_file_redirect(lex->line);
	if ((*par)->output < 0)
	{
		lex->ex_red = 1;
		free_par_one(lex, par, 0);
		(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments)
				+ 1, (*par)->arguments, NULL);
		lex->line = free_null(lex->line);
	}
	lex->out = 0;
}

void	put1(t_for_in_lexer *lex, t_for_in_parser **par, int i)
{
	char	**ss;

	if (lex->input == 1)
		put8(lex, par);
	else if (lex->out == 1)
		put3(lex, par);
	else if (lex->dollar == 1)
	{
		ss = ft_split(lex->line, ' ');
		while (ss[++i])
		{
			(*par)->arguments
				= strjoin_pr_mas(term_strlen_mas((*par)->arguments)
					+ 1, (*par)->arguments, ss[i]);
			free(ss[i]);
		}
		free((void *)ss);
		lex->dollar = 0;
	}
	else if (lex->outend == 1)
		put5(lex, par);
	else
		put4(lex, par);
}

void	put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->line && lex->line != NULL)
	{
		if (lex->pipe == 1 && lex->ex_red != 1)
		{
			ch_line_par(par, lex, PIPE_M);
			if (lex->exit != 1)
				put2(lex, par);
		}
		if (lex->ex_red == 0)
			put1(lex, par, -1);
		lex->line = free_null(lex->line);
		lex->j++;
	}
	else if (lex->outend == 1 || lex->out == 1
		|| lex->input == 1 || lex->pipe == 1)
	{
		lex->exit = 1;
		ft_puterrln(RED_WHERE);
		free_par_one(lex, par, 0);
		g_all.exit_code = 258;
	}
}
