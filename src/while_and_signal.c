#include "minishell.h"

void	ft_signal_slesh(int sig);

void	ft_signal_c(int sig);

void	while_enter_term2(t_for_in_terminal *t, t_envp *sh_envp)
{
	t->mas_his = strjoin_for_mas(term_strlen_mas(t->mas_his) + 1, t, t->sn);
	t->j = t->j + 1;
	t->i = t->j;
	line_from_terminal_to_lexer(t->sn, t, sh_envp);
}

void	while_enter_term(t_for_in_terminal *t, t_envp *sh_envp)
{
	t->del_len = 0;
	if (term_strcmp(t->s, "\n"))
	{
		if (t->i == term_strlen_mas(t->mas_his)
			&& t->s[0] != 0 && t->s[0] != 4 && t->s[0] != 10)
		{
			t->mas_his = strjoin_for_mas(term_strlen_mas(t->mas_his)
					+ 1, t, t->s);
			t->j = t->j + 1;
			t->i = t->j;
			line_from_terminal_to_lexer(t->s, t, sh_envp);
		}
		else if (t->i == 0 && term_strlen_mas(t->mas_his) == 0)
			t->i = t->i;
		else if (t->mas_his[t->i])
		{
			if (t->sn != NULL && t->sn[0] != 0
				&& t->sn[0] != 4 && t->sn[0] != 10)
			{
				while_enter_term2(t, sh_envp);
			}
		}
	}
}

void	terminal_while(t_for_in_terminal *t, t_envp *sh_envp)
{
	tputs(save_cursor, 1, term_putchar);
	g_all.key_ctr = 0;
	t->key_main = 1;
	while (t->key_main == 1)
	{
		g_all.key_ctr = 1;
		signal(SIGQUIT, ft_signal_slesh);
		signal(SIGINT, ft_signal_c);
		terminal_while2(t);
		if (!term_strcmp(t->str, "\n\0"))
		{
			write(1, "\n", 1);
			t->key_main = 0;
		}
	}
	terminal_while3(t, sh_envp);
}

void	ft_signal_slesh(int sig)
{
	if (g_all.key_ctr == 0)
		write(1, "Quit: 3\n", ft_strlen("Quit: 3\n"));
	g_all.key_signal = 2;
	sig = 1;
}

void	ft_signal_c(int sig)
{
	write(1, "\n", 1);
	g_all.key_signal = 1;
	sig = 1;
	g_all.exit_code = 1;
}
