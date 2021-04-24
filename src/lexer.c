#include "minishell.h"

char *free_null(char *l)
{
	if (l)
		free(l);
	return (NULL);
}

void put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par)
{
	if (lex->line && lex->line != NULL)
	{
		//printf("\n==%s", lex->line);
		if (lex->input == 1)
		{
			par[lex->l]->input = strjoin_pr_mas(term_strlen_mas(par[lex->l]->input) + 1, par[lex->l]->input, lex->line);
			lex->input = 0;
		}
		else if (lex->out == 1)
		{
			par[lex->l]->out = strjoin_pr_mas(term_strlen_mas(par[lex->l]->out) + 1, par[lex->l]->out, lex->line);
			lex->out = 0;
		}
		else if (lex->outend == 1)
		{
			par[lex->l]->outend = strjoin_pr_mas(term_strlen_mas(par[lex->l]->outend) + 1, par[lex->l]->outend, lex->line);
			lex->outend = 0;
		}
		else if (lex->pipe == 1)
		{
			//lex->l++;
			//par = par->next;
			//par = malloc((lex->l + 2)*sizeof(par));
			lex->pipe = 0;
		}
		else
		{
			printf("\n344 ================ %d\n", lex->l);
			//if (lex->j > 0)
				//printf("\nar == %s\n", par[lex->l]->arguments[0]);
			par[lex->l]->arguments = strjoin_pr_mas(term_strlen_mas(par[lex->l]->arguments) + 1, par[lex->l]->arguments, lex->line);
			//printf("\nar == %s\n", par[lex->l]->arguments[0]);
			printf("\n3+*******+\n");
			//printf("\n%s\n", par[lex->l]->arguments[0]);
		}
		//lex->mas_line = strjoin_lex_mas(term_strlen_mas(lex->mas_line) + 1, lex);
		lex->line = free_null(lex->line);
		lex->j++;
		//if (lex->j > 0)
			//printf("\nar == %s\n", par[lex->l]->arguments[0]);
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

void lexer(t_for_in_lexer *lex, t_for_in_parser **par)
{
	while (lex->s[lex->i] != '\0')
	{
		//if (lex->j > 0)
			//printf("\nar == %s\n", par[lex->l]->arguments[0]);
		if (lex->s[lex->i] == '"')
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != '"')
			{
				if (lex->s[lex->i] == '$')
				{
					lex->line = term_strjoin(lex->line, "<DOLLAR>");
					while(lex->fd == 1)
						lex->fd = 0;
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
			while(lex->fd == 1)
				lex->fd = 0;
			lex->fd = 1;
		}
		else if (lex->s[lex->i] == '|')
		{
			put_line_in_mas(lex, par);
			lex->pipe = 1;
			//lex->line = term_strjoin(lex->line, "<PIPE>");
			//put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] != '>')
		{
			put_line_in_mas(lex, par);
			lex->out = 1;
			//lex->line = term_strjoin(lex->line, "<OUT>");
			//put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] == '>')
		{
			put_line_in_mas(lex, par);
			lex->outend = 1;
			//lex->line = term_strjoin(lex->line, "<OUTTHE>");
			//put_line_in_mas(lex);
		}
		else if (lex->s[lex->i] == '<')
		{
			put_line_in_mas(lex, par);
			lex->input = 1;
			//lex->line = term_strjoin(lex->line, "<IN>");
			//put_line_in_mas(lex);
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
			//printf("\n3331\n");
			//if (lex->j > 0)
				//printf("\nar ==++ %s\n", par[lex->l]->arguments[0]);
			put_line_in_mas(lex, par);
			//if (lex->j > 0)
				//printf("\nar ==++ %s\n", par[lex->l]->arguments[0]);
			//printf("\n3332\n");
		}
		lex->i++;
	}
	//printf("\n333212\n");
	put_line_in_mas(lex, par);
	//printf("\n333311\n");
	int i;
	i = 0;

	/*while (lex->mas_line[i])
	{
		printf("\n%s\n", lex->mas_line[i]);
		i++;
	}
	printf("\n|%s\n", lex->mas_line[i]);*/

	//del_mas(lex);
	//go_to_pars();
}


void line_from_terminal_to_lexer(char *s, t_for_in_terminal *t)
{
	t_for_in_lexer lex;
	t_for_in_parser *par;

	lex.s = s;
	//lex.mas_his = t->mas_his;
	int i;
	i = -1;
	t->i = t->i;
	lex.i = 0;
	lex.j = 0;
	lex.fd = 0;
	lex.len = 0;
	lex.l = 0;

	lex.input = 0;
	lex.out = 0;
	lex.outend = 0;
	lex.pipe = 0;

	lex.mas_line = NULL;
	lex.line = NULL;
	par = (t_for_in_parser *)malloc(3 * sizeof(par));
	//par = (t_for_in_parser *)ft_calloc(3, sizeof(par));
	//printf("\n|%s|\n", lex.s);
	lexer(&lex, &par);
	free(par);
}