#include "termcap.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	terminal_do_write(t_for_in_terminal *t)
{
	if (t->str[0] == 0)
		t->i = t->i;
	else if (t->i == ft_strlen_mas(t->mas_his))
	{
		t->s = ft_strjoin_str(t->s, t->str);
	}
	else if (t->mas_his[t->i])
	{
		t->sn = ft_strjoin_str(t->sn, t->str);
	}
	write (1, t->str, t->l);
}

void	terminal_do_elseif(t_for_in_terminal *t)
{
	if (t->i < ft_strlen_mas(t->mas_his))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (t->sn)
		{
			t->mas_his[t->i] = ft_strjoin(NULL, t->sn);
			if (t->sn)
				free((void *)t->sn);
			//t->sn = NULL;
		}
		t->i = t->i + 1;
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

void	terminal_do_if(t_for_in_terminal *t)
{
	if (t->i > 0)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (t->sn)
		{
			t->mas_his[t->i] = ft_strjoin(NULL, t->sn);
			//if (t->sn)
				//free((void *)t->sn);
			//t->sn = NULL;
		}
		t->i = t->i - 1;
		if (t->mas_his[t->i] && t->mas_his[t->i] != NULL)
		{
			write(1, t->mas_his[t->i], ft_strlen(t->mas_his[t->i]));
			t->sn = ft_strjoin(NULL, t->mas_his[t->i]);
		}
	}
}

void	terminal_while_sec(t_for_in_terminal *t)
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
			terminal_while_sec_t(t);
		}
	}
	if (t->s)
	{
		t->s = NULL;
		free((void *)t->s);
	}
	write(1, TERMINALNAME, 11);
	t->s = NULL;
	t->i = t->j;
}
