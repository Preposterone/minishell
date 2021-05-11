#include "termcap.h"

int	term_putchar(int c)
{
	return (write(2, &c, 1));
}

void	up_terminal(t_for_in_terminal *t)
{
	if (t->i > 0)
	{
		tputs(restore_cursor, 1, term_putchar);
		tputs(tigetstr("ed"), 1, term_putchar);
		t->del_len = 0;
		if (t->sn)
		{
			if (t->mas_his[t->i])
			{
				free((void *)t->mas_his[t->i]);
				t->mas_his[t->i] = NULL;
			}
			t->mas_his[t->i] = term_strjoin(NULL, t->sn);
		}
		t->i = t->i - 1;
		if (t->sn && t->sn != NULL)
		{
			free((void *)t->sn);
			t->sn = NULL;
		}
		if (t->mas_his[t->i] && t->mas_his[t->i] != NULL)
		{
			write(1, t->mas_his[t->i], term_strlen(t->mas_his[t->i]));
			t->sn = term_strjoin(NULL, t->mas_his[t->i]);
			t->del_len = term_strlen(t->sn);
		}
	}
}

void	down_term_sec(t_for_in_terminal *t)
{
	if (t->mas_his[t->i] && t->mas_his[t->i] != NULL)
	{
		write(1, t->mas_his[t->i], term_strlen(t->mas_his[t->i]));
		t->sn = term_strjoin(NULL, t->mas_his[t->i]);
	}
	else if (t->i == term_strlen_mas(t->mas_his))
	{
		tputs(restore_cursor, 1, term_putchar);
		tputs(tigetstr("ed"), 1, term_putchar);
		write(1, t->s, term_strlen(t->s));
	}
}

void	down_term(t_for_in_terminal *t)
{
	if (t->i < term_strlen_mas(t->mas_his))
	{
		t->del_len = 0;
		tputs(restore_cursor, 1, term_putchar);
		tputs(tigetstr("ed"), 1, term_putchar);
		if (t->sn)
		{
			if (t->mas_his[t->i])
			{
				free((void *)t->mas_his[t->i]);
				t->mas_his[t->i] = NULL;
			}
			t->mas_his[t->i] = term_strjoin(NULL, t->sn);
		}
		t->i = t->i + 1;
		if (t->sn && t->sn != NULL)
		{
			free((void *)t->sn);
			t->sn = NULL;
		}
		down_term_sec(t);
		t->del_len = term_strlen(t->sn);
	}
}
