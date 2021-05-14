#include "minishell.h"

void	lexer(t_for_in_lexer *lex, t_for_in_parser **par,
			t_for_in_terminal *t, t_envp *sh_envp)
{
	lex->if_i = 0;
	while (lex->s[lex->i] != '\0')
	{
		lexer4(lex, par);
		lexer5(lex, par);
		lexer6(lex, par, t, sh_envp);
		if (lex->exit == 1)
			return ;
		if (lex->if_i == 0 && lex->s[lex->i] == ' '
			&& lex->line && lex->line != NULL)
		{
			lex->if_i = 1;
			put_line_in_mas(lex, par);
		}
		if (lex->exit == 1)
			return ;
		lex->i++;
		lex->if_i = 0;
	}
	if (lex->ex_red == 0)
		put_line_in_mas(lex, par);
	(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
	if (lex->exit == 1)
		return ;
}

void	lexer_null(t_for_in_lexer *lex, char *s, t_for_in_terminal *t)
{
	lex->s = s;
	t->i = t->i;
	lex->i = 0;
	lex->j = 0;
	lex->fd = 0;
	lex->len = 0;
	lex->l = 0;
	lex->input = 0;
	lex->out = 0;
	lex->outend = 0;
	lex->pipe = 0;
	lex->ex_red = 0;
	lex->dollar = 0;
	lex->mas_line = NULL;
	lex->line = NULL;
	lex->exit = 0;
	lex->line = (char *)ft_calloc(1, sizeof(char));
}

void	lexer_null2(t_for_in_lexer *lex, t_for_in_parser **par,
			t_for_in_terminal *t, t_envp *sh_envp)
{
	free(lex->flags_arg);
	if (lex->exit == 0)
	{
		del_settings_term(t);
		executor_secretary(par, sh_envp, t);
		do_settings_term(t);
	}
	del_free_par(par);
	free(lex->t_p);
}

void	line_from_terminal_to_lexer(char *s,
		t_for_in_terminal *t, t_envp *sh_envp)
{
	t_for_in_lexer	lex;
	t_for_in_parser	*par;

	lexer_null(&lex, s, t);
	lex.envp = sh_envp->sh_envp;
	par = ft_calloc(1, sizeof(t_for_in_parser));
	par->next = ft_calloc(1, sizeof(t_for_in_parser));
	lex.t_p = par;
	par = par->next;
	par->key = 1;
	par->previous = lex.t_p;
	lex.flags_arg = (int *)ft_calloc(128, sizeof(int));
	if (!lex.flags_arg)
		exit_fatal(MSH_MALLOC_ERR);
	lex.i = 0;
	while (lex.i < 127)
		lex.flags_arg[lex.i++] = 0;
	lex.i = 0;
	lex.flags_check = 0;
	par->arguments = (char **)ft_calloc(1, sizeof(char *));
	par->output = -2;
	par->input = -2;
	lexer(&lex, &par, t, sh_envp);
	lexer_null2(&lex, &par, t, sh_envp);
}
