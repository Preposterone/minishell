#include "termcap.h"

void	del_term(t_for_in_terminal *t)
{
	if (t->i == term_strlen_mas(t->mas_his) && t->s)
	{
		if (t->s[0] != 0 && t->s[0] != 10)
		{
			tputs(cursor_left, 1, term_putchar);
			tputs(tgetstr("dc", 0), 1, term_putchar);
		}
		t->s = str_delet_last_char(t->s);
	}
	else if (t->sn)
	{
		if (t->sn[0] != 0)
		{
			tputs(cursor_left, 1, term_putchar);
			tputs(tgetstr("dc", 0), 1, term_putchar);
		}
		t->sn = str_delet_last_char(t->sn);
	}
}

void	do_term(t_for_in_terminal *t)
{
	ioctl(0, FIONREAD, &t->n);
	t->l = read(0, t->str, t->n);
	t->str[t->l] = 0;
	if (!term_strcmp(t->str, "\e[A"))
		up_terminal(t);
	else if (!term_strcmp(t->str, "\e[B"))
		down_term(t);
	else if (term_strcmp(t->str, key_backspace) && !term_strcmp(t->str, "\177"))
		del_term(t);
	else if (!term_strcmp(t->str, "\e[D"))
		write(1, "left", 0);
	else if (!term_strcmp(t->str, "\e[C"))
		write(1, "right", 0);
	else
	{
		if (t->str[0] == 0)
			t->i = t->i;
		else if (t->i == term_strlen_mas(t->mas_his))
			t->s = term_strjoin(t->s, t->str);
		else if (t->mas_his[t->i])
			t->sn = term_strjoin(t->sn, t->str);
		write (1, t->str, t->l);
	}
}

void	while_enter_term(t_for_in_terminal *t)
{
	if (term_strcmp(t->s, "\n"))
	{
		if (t->i == term_strlen_mas(t->mas_his)
			&& t->s[0] != 0 && t->s[0] != 4 && t->s[0] != 10)
		{
			t->mas_his = strjoin_for_mas(term_strlen_mas(t->mas_his)
					+ 1, t, t->s);
			t->j = t->j + 1;
			t->i = t->j;
			line_from_terminal_to_lexer(t->s, t, -1);
		}
		else if (t->i == 0 && term_strlen_mas(t->mas_his) == 0)
			t->i = t->i;
		else if (t->mas_his[t->i])
		{
			if (t->sn != NULL && t->sn[0] != 0
				&& t->sn[0] != 4 && t->sn[0] != 10)
			{
				t->mas_his = strjoin_for_mas(term_strlen_mas(t->mas_his)
						+ 1, t, t->sn);
				t->j = t->j + 1;
				t->i = t->j;
				line_from_terminal_to_lexer(t->sn, t, -1);
			}
		}
	}
}

void	terminal_while(t_for_in_terminal *t)
{
	tputs(save_cursor, 1, term_putchar);
	while (1 == 1)
	{
		do_term(t);
		if (!term_strcmp(t->str, "\n") || !term_strcmp(t->str, "\4"))
			break ;
	}
	while_enter_term(t);
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
	write(1, TERMINALNAME, term_strlen(TERMINALNAME));
	t->i = t->j;
}

void	terminal(int argc, char const *argv[], char const *envp[])
{
	t_for_in_terminal	t;

	t.argc = argc;
	t.argv = argv;
	t.envp = envp;
	tcgetattr(0, &t.term);
	from_file(&t);
	t.i = term_strlen_mas(t.mas_his);
	t.term.c_lflag &= ~(ECHO);
	t.term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &t.term);
	tgetent(0, t.term_name);
	t.term_name = "xterm-256color";
	t.n = 0;
	t.j = t.i;
	t.peri = t.i;
	write(1, &t.str, 100);
	write(1, TERMINALNAME, term_strlen(TERMINALNAME));
	while (term_strcmp(t.str, "\4"))
		terminal_while(&t);
	write(1, "\n", 1);
	file_mas(t.mas_his, t.peri);
	return ;
}
