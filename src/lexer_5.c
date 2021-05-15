#include "minishell.h"

void	lexer2(t_for_in_lexer *lex, t_for_in_parser **par)
{
	while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != '"')
	{
		if (lex->s[lex->i] == '$')
			dollar(lex, par);
		else if (lex->s[lex->i] == 92)
		{
			if (lex->s[lex->i + 1] != '\0')
				lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
			else
			{
				lex->exit = 1;
				lex->line = free_null(lex->line);
				ft_puterrln(ERROR_E);
				g_all.exit_code = 258;
				return ;
			}
		}
		else
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
	}
	lex22(lex);
}

void	lexer3(t_for_in_lexer *lex)
{
	while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != 39)
		lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
	if (lex->s[lex->i - 1] == 39 && lex->s[lex->i] == 39
		&& lex->line == NULL)
	{
		lex->line = lexer_charjoin(lex->line, '1');
		lex->line[0] = '\0';
	}
	if (lex->s[lex->i] == '\0')
	{
		lex->exit = 1;
		lex->if_i = 1;
		lex->line = free_null(lex->line);
		ft_puterrln(M_QUOTES);
		g_all.exit_code = 258;
		return ;
	}
	lex->if_i = 1;
}

void	lexer4(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->if_i == 0 && lex->s[lex->i] == '"')
		lexer2(lex, par);
	if (lex->if_i == 0 && lex->s[lex->i] == 39)
		lexer3(lex);
	if (lex->if_i == 0 && lex->s[lex->i] == '$')
		dollar(lex, par);
	if (lex->if_i == 0 && lex->s[lex->i] == '|')
	{
		if (lex->ex_red == 0)
			put_line_in_mas(lex, par);
		lex->pipe = 1;
		lex->if_i = 1;
		lex->ex_red = 0;
	}
	lexer42(lex, par);
}

void	lexer5(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->if_i == 0 && lex->s[lex->i] == '<')
	{
		put_line_in_mas(lex, par);
		lex->input = 1;
		lex->if_i = 1;
	}
	if (lex->if_i == 0 && lex->s[lex->i] == 92)
	{
		if (lex->s[lex->i + 1] != '\0')
			lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
		else
		{
			lex->exit = 1;
			lex->line = free_null(lex->line);
			ft_puterrln(ERROR_E);
			g_all.exit_code = 258;
			return ;
		}
		lex->if_i = 1;
	}
}

void	lexer6(t_for_in_lexer *lex, t_for_in_parser **par,
			t_for_in_terminal *t, t_envp *sh_envp)
{
	int	i;

	if (lex->if_i == 0 && lex->s[lex->i] == ';')
	{
		ch_line_par(par, lex, TOCHKA_M);
		if (lex->ex_red == 1)
			free_par_one(lex, par, 0);
		i = lexer62(lex);
		if (i == 1)
			return ;
		put_line_in_mas(lex, par);
		del_settings_term(t);
		executor_secretary(par, sh_envp, t);
		del_free_par(par);
		do_settings_term(t);
		free(lex->t_p);
		lexer7(lex, par);
		lex->ex_red = 0;
	}
	if (lex->if_i == 0 && lex->s[lex->i] != ' ' && lex->s[lex->i] != 10)
	{
		lex->if_i = 1;
		lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
	}
}
