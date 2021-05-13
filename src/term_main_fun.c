#include "minishell.h"

void	terminal_while2(t_for_in_terminal *t)
{
	if (g_all.key_signal == 1)
	{
		if (t->del_len == 0)
		{
			t->s = (char *)ft_calloc(1, sizeof(char));
			g_all.key_signal = 0;
			t->key_main = 0;
		}
		if (t->del_len > 0 && t->s)
		{
			t->s = free_null(t->s);
			t->s = term_strjoin(NULL, "\0");
		}
		else if (t->del_len > 0 && t->sn)
		{
			t->sn = free_null(t->sn);
			t->sn = term_strjoin(NULL, "\0");
		}
		g_all.key_signal = 0;
		t->key_main = 0;
	}
	else
		do_term(t);
}

void	terminal_while3(t_for_in_terminal *t, t_envp *sh_envp)
{
	g_all.key_ctr = 0;
	t->key_main = 1;
	while_enter_term(t, sh_envp);
	write(1, TERMINALNAME, ft_strlen(TERMINALNAME));
	if (t->s)
	{
		free((void *)t->s);
		t->s = NULL;
	}
	if (t->sn)
	{
		free((void *)t->sn);
		t->sn = NULL;
	}
	t->i = t->j;
	g_all.key_signal = 0;
}

void	terminal(int argc, char *argv[], t_envp *sh_envp)
{
	t_for_in_terminal	t;
	int					i;

	ft_bzero(&t, sizeof(t_for_in_terminal));
	t.argc = argc;
	g_all.exit_code = 0;
	t.argv = argv;
	t.envp = sh_envp->sh_envp;
	tcgetattr(0, &t.term);
	from_file(&t);
	t.i = term_strlen_mas(t.mas_his);
	do_settings_term(&t);
	t.term_name = sh_envp->sh_term;
	tgetent(0, t.term_name);
	t.n = 0;
	t.del_len = 0;
	t.j = t.i;
	t.peri = t.i;
	i = 2;
	if (argc > 1)
	{
		if (!term_strcmp(argv[1], "-c"))
		{
			while (argv[i] != NULL)
			{
				//printf("\n1 =%s\n", argv[2]);
				t.s = term_strjoin(NULL, argv[i]);
				line_from_terminal_to_lexer(t.s, &t, sh_envp);
				free(t.s);
				t.s = NULL;
				i++;
			}
			return ;
		}
	}
	if (argc > 1)
		exit_minishell(MANY_ARGS, -1, &t);
	write(1, TERMINALNAME, term_strlen(TERMINALNAME));
	while (term_strcmp(t.str, "\4"))
		terminal_while(&t, sh_envp);
	return ;
}
