#include "termcap.h"

char *free_null(char *l)
{
	if (l)
		free(l);
	return (NULL);
}

void put_line_in_mas(t_for_in_lexer *lex)
{
	if (lex->line && lex->line != NULL)
	{
		//printf("\n==%s", lex->line);
		lex->mas_line = strjoin_lex_mas(term_strlen_mas(lex->mas_line) + 1, lex);
		lex->line = free_null(lex->line);
		lex->j++;
	}
}

void del_mas(t_for_in_lexer *lex)
{
	int i;

	i = 0;
	while (lex->mas_line[i])
	{
		free((void *)lex->mas_line[i]);
		lex->mas_line[i] = NULL;
		i++;
	}
	free((void **)lex->mas_line);
	lex->mas_line = NULL;
}

void lexer(t_for_in_lexer *lex)
{
	while (lex->s[lex->i] != '\0')
	{
		if (lex->s[lex->i] == '"')
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != '"')
			{
				if (lex->s[lex->i] == '$')
				{
					lex->line = term_strjoin(lex->line, "<DOLLAR>");
				}
				else if (lex->s[lex->i] == 92)
				{
					if (lex->s[lex->i + 1] != '\0')
						lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
					else
						exit(0);
				}
				else
					lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit(0);
		}
		else if (lex->s[lex->i] == 39) //'
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != 39)
			{
				lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit(0);
		}
		else if (lex->s[lex->i] == '$')
		{
			lex->line = term_strjoin(lex->line, "<DOLLAR>");
			lex->fd = 1;
		}
		else if (lex->s[lex->i] == '|')
		{
			put_line_in_mas(lex);
			lex->line = term_strjoin(lex->line, "<PIPE>");
			put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] != '>')
		{
			put_line_in_mas(lex);
			lex->line = term_strjoin(lex->line, "<OUT>");
			put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] == '>')
		{
			put_line_in_mas(lex);
			lex->line = term_strjoin(lex->line, "<OUTTHE>");
			put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '<')
		{
			put_line_in_mas(lex);
			lex->line = term_strjoin(lex->line, "<IN>");
			put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == 92)
		{
			if (lex->s[lex->i + 1] != '\0')
				lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
			else
				exit(0);
		}
		else if (lex->s[lex->i] == ';')
			lex->i = lex->i;//go_to_pars();
		else if (lex->s[lex->i] != ' ' && lex->s[lex->i] != 10)
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
		else if (lex->s[lex->i] == ' ' && lex->line && lex->line != NULL)
		{
			put_line_in_mas(lex);
		}
		lex->i++;
	}
	put_line_in_mas(lex);
	int i;
	i = 0;
	while (lex->mas_line[i])
	{
		printf("\n%s\n", lex->mas_line[i]);
		i++;
	}
	printf("\n|%s\n", lex->mas_line[i]);
	del_mas(lex);
	//go_to_pars();
}


void line_from_terminal_to_lexer(char *s, t_for_in_terminal *t)
{
	t_for_in_lexer lex;

	lex.s = s;
	//lex.mas_his = t->mas_his;
	int i;
	i = -1;
	t->i = t->i;
	lex.i = 0;
	lex.j = 0;
	lex.fd = 0;
	lex.len = 0;
	lex.mas_line = NULL;
	lex.line = NULL;
	//printf("\n|%s|\n", lex.s);
	lexer(&lex);
}