#include "termcap.h"

void	terminal_do_two(t_for_in_terminal *t)
{
	if (t->i == ft_strlen_mas(t->mas_his))
	{
		if (t->s[0] != 0)
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

void	terminal_do(t_for_in_terminal *t)
{
	if (!strcmp(t->str, "\e[A"))
		terminal_do_if(t);
	else if (!strcmp(t->str, "\e[B"))
		terminal_do_elseif(t);
	else if (strcmp(t->str, key_backspace) && !strcmp(t->str, "\177"))
		terminal_do_two(t);
	else if (!strcmp(t->str, "\e[D"))
		write(1, "left", 0);
	else if (!strcmp(t->str, "\e[C"))
		write(1, "right", 0);
	else
	{
		terminal_do_write(t);
	}
}

void	terminal_while_sec_t(t_for_in_terminal *t)
{
	if (t->sn != NULL && t->sn[0] != 0
		&& t->sn[0] != 4 && t->sn[0] != 10)
	{
		t->mas_his = strjoin_for_mas(ft_strlen_mas(t->mas_his)
				+ 1, t->mas_his, t->sn);
		free((void *)t->sn);
		t->sn = NULL;
		t->j = t->j + 1;
		t->i = t->j;
	}
	else if (t->sn != NULL)
	{
		free((void *)t->sn);
		t->sn = NULL;
	}
}

void	terminal_while(t_for_in_terminal *t)
{
	tputs(save_cursor, 1, ft_putchar);
	do
	{
		ioctl(0, FIONREAD, &t->n);
		t->l = read(0, t->str, t->n);
		t->str[t->l] = 0;
		terminal_do(t);
	}
	while (strcmp(t->str, "\n") && strcmp(t->str, "\4"));
		terminal_while_sec(t);
}

void	terminal(int argc, char const *argv[], char const *envp[])
{
	t_for_in_terminal	t;

	t.argc = argc;
	t.argv = argv;
	t.envp = envp;
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
	while (strcmp(t.str, "\4"))
		terminal_while(&t);
	write(1, "\n", 1);
	file_mas(t.mas_his, t.peri);
	return ;
}
