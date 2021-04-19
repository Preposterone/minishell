#include "termcap.h"

void dellet(char *s)
{
	if (s != NULL)
	{
		free((void *)s);
		s = NULL;
	}
}

void	terminal_while(t_for_in_terminal *t)
{
	int f;
	f = 0;
	tputs(save_cursor, 1, ft_putchar);
	do
	{
		ioctl(0, FIONREAD, &t->n);
		t->l = read(0, t->str, t->n);
		t->str[t->l] = 0;
		if (!ft_strcmp(t->str, "\e[A"))
		{
			if (t->i > 0)
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				if (t->sn)
				{
					t->mas_his[t->i] = ft_strjoin(NULL, t->sn);
				}
				t->i = t->i - 1;
				if (t->sn && t->sn != NULL)
				{
					free((void *)t->sn);
					t->sn = NULL;
				}
				if (t->mas_his[t->i] && t->mas_his[t->i] != NULL)
				{
					write(1, t->mas_his[t->i], ft_strlen(t->mas_his[t->i]));
					t->sn = ft_strjoin(NULL, t->mas_his[t->i]);
				}
			}
		}
		else if (!ft_strcmp(t->str, "\e[B"))
		{
			if (t->i < ft_strlen_mas(t->mas_his))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				if (t->sn)
				{
					t->mas_his[t->i] = ft_strjoin(NULL, t->sn);
				}
				t->i = t->i + 1;
				if (t->sn && t->sn != NULL)
				{
					free((void *)t->sn);
					t->sn = NULL;
				}
				if (t->mas_his[t->i] && t->mas_his[t->i] != NULL)
				{
					write(1, t->mas_his[t->i], ft_strlen(t->mas_his[t->i]));
					t->sn = ft_strjoin(NULL, t->mas_his[t->i]);
				}
				else if (t->i == ft_strlen_mas(t->mas_his))
				{
					tputs(restore_cursor, 1, ft_putchar);
					tputs(tigetstr("ed"), 1, ft_putchar);
					write(1, t->s, ft_strlen(t->s));
				}
			}
			
		}
		else if (ft_strcmp(t->str, key_backspace) && !ft_strcmp(t->str, "\177"))
		{
			if (t->i == ft_strlen_mas(t->mas_his) && t->s)
			{
				if (t->s[0] != 0 && t->s[0] != 10)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(tgetstr("dc", 0), 1, ft_putchar);
				}
				t->s = str_delet_last_char(t->s);
			}
			else if (t->sn)
			{
				if (t->sn[0] != 0)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(tgetstr("dc", 0), 1, ft_putchar);
				}
				t->sn = str_delet_last_char(t->sn);
			}
		}
		else if (!ft_strcmp(t->str, "\e[D"))
			write(1, "left", 0);
		else if (!ft_strcmp(t->str, "\e[C"))
			write(1, "right", 0);
		else
		{
			if (t->str[0] == 0)
				t->i = t->i;
			else if (t->i == ft_strlen_mas(t->mas_his))
			{
				t->s = ft_strjoin(t->s, t->str);
			}
			else if (t->mas_his[t->i])
			{
				t->sn = ft_strjoin(t->sn, t->str);
			}
			write (1, t->str, t->l);
		}
	}














	while (ft_strcmp(t->str, "\n") && ft_strcmp(t->str, "\4"));
	{
		if (ft_strcmp(t->s, "\n"))
		{
			if (t->i == ft_strlen_mas(t->mas_his)
				&& t->s[0] != 0 && t->s[0] != 4 && t->s[0] != 10)
			{
				t->mas_his = strjoin_for_mas(ft_strlen_mas(t->mas_his)
						+ 1, t->mas_his, t->s);
				t->j = t->j + 1;
				t->i = t->j;
			}
			else if (t->i == 0 && ft_strlen_mas(t->mas_his) == 0)
			{
				t->i = t->i;
			}
			else if (t->mas_his[t->i])
			{
				if (t->sn != NULL && t->sn[0] != 0
					&& t->sn[0] != 4 && t->sn[0] != 10)
				{
					t->mas_his = strjoin_for_mas(ft_strlen_mas(t->mas_his)
							+ 1, t->mas_his, t->sn);
					t->j = t->j + 1;
					t->i = t->j;
				}
			}
		}
		if (t->s)
		{
			free(t->s);
			t->s = NULL;
		}
		if (t->sn)
		{
			free(t->sn);
			t->sn = NULL;
		}
		f = 1;
		write(1, TERMINALNAME, 11);
		t->i = t->j;
	}
}

void	terminal(int argc, char const *argv[], char const *envp[])
{
	t_for_in_terminal	t;

	t.argc = argc;
	t.argv = argv;
	t.envp = envp;
	/*t.str = (char *)(malloc(sizeof(char) * (2000)));
	if (!t.str)
		return ;
	int jj = 0;
	while (jj < 2000)
	{
		t.str[jj] = 45;
		jj++;
	}*/
	tcgetattr(0, &t.term);
	//from_file(&t);
	t.i = ft_strlen_mas(t.mas_his);
	t.term.c_lflag &= ~(ECHO);
	t.term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &t.term);
	tgetent(0, t.term_name);
	t.term_name = "xterm-256color";
	t.n = 0;
	t.j = t.i;
	t.peri = t.i;
	write(1, &t.str, 100);
	write(1, TERMINALNAME, 11);
	while (ft_strcmp(t.str, "\4"))
		terminal_while(&t);
	write(1, "\n", 1);
	file_mas(t.mas_his, t.peri);
	return ;
}
