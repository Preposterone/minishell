#include "minishell.h"

void	lex22(t_for_in_lexer *lex)
{
	if (lex->s[lex->i - 1] == '"' && lex->s[lex->i] == '"')
	{
		lex->line = lexer_charjoin(lex->line, '1');
		lex->line[0] = '\0';
	}
	lexer22(lex);
}

void	lexer42(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->if_i == 0 && lex->s[lex->i] == '>' && lex->s[lex->i + 1] != '>')
	{
		put_line_in_mas(lex, par);
		lex->out = 1;
		lex->if_i = 1;
	}
	if (lex->if_i == 0 && lex->s[lex->i] == '>' && lex->s[lex->i + 1] == '>')
	{
		put_line_in_mas(lex, par);
		lex->outend = 1;
		lex->if_i = 1;
		lex->i++;
	}
}

void	lexer62(t_for_in_lexer *lex)
{
	if (lex->exit == 1)
	{
		free(lex->line);
		return ;
	}
	if (lex->ex_red != 0)
	{
		lex->ex_red = 0;
		return ;
	}
}
