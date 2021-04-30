#include "minishell.h"

void	exit_mistake()
{
	write(1, ERROR_LEXER, term_strlen(ERROR_LEXER));
	exit(0);
}

char *free_null(char *l)
{
	if (l)
		free(l);
	return (NULL);
}

void del_masiv(char **l)
{
	int i;

	i = 0;
	if (l != NULL)
	{
		while (l[i] != NULL)
		{
			l[i] = free_null(l[i]);
			i++;
		}
		free(l);
	}
}




void check_flags(t_for_in_lexer *lex)
{
	int i;
	int *h;
	char *s;

	i = 0;
	if (!lex->line)
		return ;
	h = (int *)ft_calloc(128, sizeof(int));
	s = (char *)ft_calloc(1, sizeof(char));
	while(i < 127)
		h[i++] = 0;
	i = -1;
	if (lex->line[0] == '-' && lex->line[1] != '-' && lex->line[1] != '\0')
	{
		i++;
		s = lexer_charjoin(s, lex->line[i]);
		while (lex->line[++i])
		{
			if ((lex->line[i] >= 65 && lex->line[i] <= 90) || (lex->line[i] >= 97 && lex->line[i] <= 122))
			{
				if (lex->line[i] < 127 && h[(int)lex->line[i]] == 0)
					s = lexer_charjoin(s, lex->line[i]);		
				if ((int)lex->line[i] < 127)
					h[(int)lex->line[i]] = 1;
			}
			else
			{
				free(s);
				free(h);
				s = NULL;
				return ;
			}
		}
	}
	else
	{
		free(s);
		free(h);
		s = NULL;
		return ;
	}
	free(lex->line);
	free(h);
	lex->line = NULL;
	lex->line = s;
}



void put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par)
{
	t_for_in_parser *t_p;

	if (lex->line && lex->line != NULL)
	{
		if (lex->pipe == 1)
		{
			t_p = *par;
			(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
			(*par)->next->key = (*par)->key + 1;
			*par = (*par)->next;
			(*par)->previous = t_p;
			(*par)->arguments = (char **)ft_calloc(1, sizeof(char *));
			(*par)->out = (char **)ft_calloc(1, sizeof(char *));
			(*par)->outend = (char **)ft_calloc(1, sizeof(char *));
			(*par)->input = (char **)ft_calloc(1, sizeof(char *));
			lex->pipe = 0;
		}
		if (lex->input == 1)
		{
			(*par)->input = strjoin_pr_mas(term_strlen_mas((*par)->input) + 1, (*par)->input, lex->line);
			lex->input = 0;
		}
		else if (lex->out == 1)
		{
			(*par)->out = strjoin_pr_mas(term_strlen_mas((*par)->out) + 1, (*par)->out, lex->line);
			lex->out = 0;
		}
		else if (lex->dollar == 1)
		{
			(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments) + 1, (*par)->arguments, lex->line);
			lex->dollar = 0;
		}
		else if (lex->outend == 1)
		{
			(*par)->outend = strjoin_pr_mas(term_strlen_mas((*par)->outend) + 1, (*par)->outend, lex->line);
			lex->outend = 0;
		}
		else
		{
			if (term_strlen_mas((*par)->arguments) == 1)
				check_flags(lex);
			(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments) + 1, (*par)->arguments, lex->line);
		}
		lex->line = free_null(lex->line);
		lex->j++;
	}
	else if (lex->outend == 1 || lex->out == 1 || lex->input == 1)
	{
		write(1, NO_FILE_PUT, term_strlen(NO_FILE_PUT));
		exit(0);
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


char *find_in_envp(t_for_in_lexer *lex, char *s)
{
	int i;
	int j;
	char *str;

	j = 0;
	str = NULL;
	if (s == NULL || lex->envp == NULL)
	{
		if (s != NULL)
			free(s);
		return (NULL);
	}
	while (lex->envp[j] != NULL)
	{
		i = 0;
		while (s[i] != '\0' && lex->envp[j][i] != '\0' && s[i] == lex->envp[j][i])
		{
			i++;
		}
		if (s[i] == '\0' && lex->envp[j][i])
		{
			while (lex->envp[j][++i])
			{
				str = lexer_charjoin(str, lex->envp[j][i]);
			}
			free(s);
			return (str);
		}
		j++;
	}
	free(s);
	return (NULL);
}





void dollar(t_for_in_lexer *lex, t_for_in_parser **par)
{
	char *s;

	lex->i++;
	(*par)->j = (*par)->j;
	s = NULL;
	if ((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] == '-'))
	{
		lex->dollar = 1;
		while((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] >= 48 && lex->s[lex->i] <= 57) || (lex->s[lex->i] == '-'))
		{
			s = lexer_charjoin(s, lex->s[lex->i]);
			lex->i++;
		}
		s = find_in_envp(lex, s);
		if (s != NULL)
		{
			lex->line = term_strjoin(lex->line, s);
			free(s);
			s = NULL;
		}
	}
	else
	{
		if (lex->s[lex->i] >= 48 && lex->s[lex->i] <= 57)
		{
			s = lexer_charjoin(s, lex->s[lex->i]);
			lex->i++;
			s = find_in_envp(lex, s);
			if (s != NULL)
			{
				lex->line = term_strjoin(lex->line, s);
				free(s);
				s = NULL;
			}
		}
		else if (lex->s[lex->i] == '-')
		{
			lex->i++;
			s = term_strjoin(NULL, "him");
			if (s != NULL)
			{
				lex->line = term_strjoin(lex->line, s);
				free(s);
				s = NULL;
			}
		}
		else if (lex->s[lex->i] == '?')
		{
			lex->i++;
			s = ft_itoa(g_all.exit_code);
			if (s != NULL)
			{
				lex->line = term_strjoin(lex->line, s);
				free(s);
				s = NULL;
			}
		}
		else if (lex->s[lex->i] == '*')
		{
			lex->i++;
		}
		else
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i - 1]);
	}
	lex->i--;
}




void lexer(t_for_in_lexer *lex, t_for_in_parser **par)
{
	while (lex->s[lex->i] != '\0')
	{
		if (lex->s[lex->i] == '"')
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != '"')
			{
				if (lex->s[lex->i] == '$')
				{
					dollar(lex, par);
				}
				else if (lex->s[lex->i] == 92)
				{
					if (lex->s[lex->i + 1] != '\0')
						lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
					else
						exit_mistake();
				}
				else
					lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit_mistake();
		}
		else if (lex->s[lex->i] == 39)
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != 39)
			{
				lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit_mistake();
		}
		else if (lex->s[lex->i] == '$')
		{
			dollar(lex, par);
		}
		else if (lex->s[lex->i] == '|')
		{
			put_line_in_mas(lex, par);
			lex->pipe = 1;
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] != '>')
		{
			put_line_in_mas(lex, par);
			lex->out = 1;
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] == '>')
		{
			put_line_in_mas(lex, par);
			lex->outend = 1;
			lex->i++;
		}
		else if (lex->s[lex->i] == '<')
		{
			put_line_in_mas(lex, par);
			lex->input = 1;
		}
		else if (lex->s[lex->i] == 92)
		{
			if (lex->s[lex->i + 1] != '\0')
				lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
			else
				exit_mistake();
		}
		else if (lex->s[lex->i] == ';')
		{
			put_line_in_mas(lex, par);
			//executor(par->arguments[0],&par->arguments[1],expander(par->arguments[0], sh_envp->sh_path), sh_envp);
			//del_free_par(&par); //не запускать эту фунцию, когда есть функция печати
			/*par = ft_calloc(1, sizeof(t_for_in_parser));
			par->next = ft_calloc(1, sizeof(t_for_in_parser));
			par = par->next;
			par->key = 1;
			par->previous = t_p;


			par->arguments = (char **)ft_calloc(1, sizeof(char *));
			par->out = (char **)ft_calloc(1, sizeof(char *));
			par->outend = (char **)ft_calloc(1, sizeof(char *));
			par->input = (char **)ft_calloc(1, sizeof(char *));*/

		}
		else if (lex->s[lex->i] != ' ' && lex->s[lex->i] != 10)
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
		else if (lex->s[lex->i] == ' ' && lex->line && lex->line != NULL)
		{
			put_line_in_mas(lex, par);
		}
		lex->i++;
	}
	put_line_in_mas(lex, par);
	(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
}


void print_par(t_for_in_parser **par)
{
	int i;
	printf("\nStart\n");
	while (*par != NULL)
	{
		i = 0;
		printf("\nkey = %d\n", (*par)->key);
		while ((*par)->arguments != NULL && (*par)->arguments[i] != NULL)
		{
			printf("arguments = %s\n", (*par)->arguments[i]);
			i++;
		}
		i = 0;
		while ((*par)->out != NULL && (*par)->out[i] != NULL)
		{
			printf("out = %s\n", (*par)->out[i]);
			i++;
		}
		i = 0;
		while ((*par)->outend != NULL && (*par)->outend[i] != NULL)
		{
			printf("outend = %s\n", (*par)->outend[i]);
			i++;
		}
		i = 0;
		while ((*par)->input != NULL && (*par)->input[i] != NULL)
		{
			printf("input = %s\n", (*par)->input[i]);
			i++;
		}
		*par = (*par)->previous;
	}
}

void del_free_par(t_for_in_parser **par)
{
	int i;
	int j;

	j = 0;
	while (*par != NULL)
	{
		i = 0;
		while ((*par)->arguments != NULL && (*par)->arguments[i] != NULL)
		{
			free((*par)->arguments[i]);
			(*par)->arguments[i] = NULL;
			i++;
		}
		free((*par)->arguments);
		i = 0;
		while ((*par)->out != NULL && (*par)->out[i] != NULL)
		{
			free((*par)->out[i]);
			(*par)->out[i] = NULL;
			i++;
		}
		free((*par)->out);
		i = 0;
		while ((*par)->outend != NULL && (*par)->outend[i] != NULL)
		{
			free((*par)->outend[i]);
			(*par)->outend[i] = NULL;
			i++;
		}
		free((*par)->outend);
		i = 0;
		while ((*par)->input != NULL && (*par)->input[i] != NULL)
		{
			free((*par)->input[i]);
			(*par)->input[i] = NULL;
			i++;
		}
		free((*par)->input);

		free((*par)->next);
		*par = (*par)->previous;
		j++;

	}
	free(*par);
}

void line_from_terminal_to_lexer(char *s, t_for_in_terminal *t, t_envp *sh_envp)
{
	t_for_in_lexer lex;
	t_for_in_parser *par;
	t_for_in_parser *t_p;

	lex.s = s;
	int i;
	i = -1;
	t->i = t->i;
	lex.envp = t->envp;
	lex.i = 0;
	lex.j = 0;
	lex.fd = 0;
	lex.len = 0;
	lex.l = 0;

	lex.input = 0;
	lex.out = 0;
	lex.outend = 0;
	lex.pipe = 0;
	lex.dollar = 0;

	lex.mas_line = NULL;
	lex.line = NULL;

	par = ft_calloc(1, sizeof(t_for_in_parser));
	par->next = ft_calloc(1, sizeof(t_for_in_parser));
	t_p = par;
	par = par->next;
	par->key = 1;
	par->previous = t_p;


	par->arguments = (char **)ft_calloc(1, sizeof(char *));
	par->out = (char **)ft_calloc(1, sizeof(char *));
	par->outend = (char **)ft_calloc(1, sizeof(char *));
	par->input = (char **)ft_calloc(1, sizeof(char *));
	lexer(&lex, &par);

	//print_par(&par); //Для печати
	(void)sh_envp;
	//executor(par->arguments[0],&par->arguments[1],expander(par->arguments[0], sh_envp->sh_path), sh_envp);
	del_free_par(&par); //не запускать эту фунцию, когда есть функция печати

	free(t_p);
}


























