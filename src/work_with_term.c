#include "minishell.h"

void del_settings_term(t_for_in_terminal *t)
{
	t->term.c_lflag |= (ECHO);
	t->term.c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, &t->term);
}

void do_settings_term(t_for_in_terminal *t)
{
	t->term.c_lflag &= ~(ECHO);
	t->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &t->term);
}