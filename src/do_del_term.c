#include "minishell.h"

void	del_term2(t_for_in_terminal *t)
{
	if (t->s[0] != 0 && t->s[0] != 10)
	{
		tputs(cursor_left, 1, term_putchar);
		tputs(tgetstr("dc", 0), 1, term_putchar);
	}
	t->s = str_delet_last_char(t->s);
	if (t->del_len == 1)
	{
		free(t->s);
		t->s = (char *)ft_calloc(1, sizeof(char));
	}
}

void	del_term(t_for_in_terminal *t)
{
	if (t->del_len > 0 && t->i == term_strlen_mas(t->mas_his) && t->s)
		del_term2(t);
	else if (t->del_len > 0 && t->sn)
	{
		if (t->sn[0] != 0)
		{
			tputs(cursor_left, 1, term_putchar);
			tputs(tgetstr("dc", 0), 1, term_putchar);
		}
		t->sn = str_delet_last_char(t->sn);
		if (t->del_len == 1)
		{
			free(t->sn);
			t->sn = (char *)ft_calloc(1, sizeof(char));
		}
	}
	if (t->del_len > 0)
		t->del_len--;
}

void	do_term2(t_for_in_terminal *t)
{
	if (t->str[0] == 0)
		t->i = t->i;
	else if (t->i == term_strlen_mas(t->mas_his))
	{
		t->del_len++;
		t->s = term_strjoin(t->s, t->str);
	}
	else if (t->mas_his[t->i])
	{
		t->del_len++;
		t->sn = term_strjoin(t->sn, t->str);
	}
	if (t->str[0] != '\n')
		write (1, t->str, t->l);
}

void	do_term(t_for_in_terminal *t)
{
	ioctl(0, FIONREAD, &t->n);
	t->l = read(0, t->str, t->n);
	t->str[t->l] = 0;
	if (t->str[0] == 0)
		return ;
	if (!term_strcmp(t->str, "\e[A"))
		up_terminal(t);
	else if (!term_strcmp(t->str, "\4") && t->del_len == 0)
		ft_do_exit((char *[]){0, NULL}, t, 1);
	else if (!term_strcmp(t->str, "\4"))
		t->i = t->i;
	else if (!term_strcmp(t->str, "\e[B"))
		down_term(t);
	else if (term_strcmp(t->str, key_backspace) && !term_strcmp(t->str, "\177"))
		del_term(t);
	else if (!term_strcmp(t->str, "\e[D") || !term_strcmp(t->str, "\e[C"))
		t->i = t->i;
	else if (t->str[0] < 31 && t->str[0] != 10)
		t->str[0] = '\0';
	else
		do_term2(t);
}
