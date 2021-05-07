#include "minishell.h"

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
		free((*par)->next);
		*par = (*par)->previous;
		j++;

	}
	free(*par);
}


void check_flags(t_for_in_lexer *lex)
{
	int i;
	char *s;

	i = 0;
	if (!lex->line)
		return ;
	s = (char *)ft_calloc(1, sizeof(char));
	i = -1;
	if (lex->line[0] == '-' && lex->line[1] != '-' && lex->line[1] != '\0')
	{
		i++;
		s = lexer_charjoin(s, lex->line[i]);
		while (lex->line[++i])
		{
			if ((lex->line[i] >= 65 && lex->line[i] <= 90) || (lex->line[i] >= 97 && lex->line[i] <= 122))
			{
				if (lex->line[i] < 127 && lex->flags_arg[(int)lex->line[i]] == 0)
					s = lexer_charjoin(s, lex->line[i]);
				if ((int)lex->line[i] < 127)
					lex->flags_arg[(int)lex->line[i]] = 1;
			}
			else
			{
				free(s);
				s = NULL;
				return ;
			}
		}
	}
	else
	{
		lex->flags_check = 0;
		free(s);
		s = NULL;
		return ;
	}
	if (s[1] == '\0')
	{
		free(s);
		s = NULL;
		s = (char *)ft_calloc(1, sizeof(char));
	}
	lex->flags_check = 1;
	free(lex->line);
	lex->line = NULL;
	lex->line = s;
}



void put_line_in_mas(t_for_in_lexer *lex, t_for_in_parser **par, t_for_in_terminal *t)
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
			(*par)->output = -2;
			(*par)->input = -2;
			lex->pipe = 0;
		}
		if (lex->input == 1)
		{
			if ((*par)->input > 0)
				close((*par)->input);
			(*par)->input = open(lex->line, O_RDONLY);
			if ((*par)->input != -1)
			{
				close((*par)->input);
				(*par)->input = open_RDONLY_file_redirect(lex->line);
				if ((*par)->input < 0)
					exit_minishell(CANT_OPEN_FILE, 1, t);
			}
			else
				exit_minishell(FILE_DONT_REAL, 1, t);
			lex->input = 0;
		}
		else if (lex->out == 1)
		{
			if ((*par)->output > 0)
				close((*par)->output);
			(*par)->output = open(lex->line, O_RDONLY);
			if ((*par)->output != -1)
			{
				close((*par)->output);
				(*par)->output = open_TRUNC_file_redirect(lex->line);
			}
			else
				(*par)->output = open_APPEND_file_redirect(lex->line);
			if ((*par)->output < 0)
				exit_minishell(CANT_OPEN_FILE, 1, t);
			lex->out = 0;
		}
		else if (lex->dollar == 1)
		{
			(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments) + 1, (*par)->arguments, lex->line);
			lex->dollar = 0;
		}
		else if (lex->outend == 1)
		{
			if ((*par)->output > 0)
				close((*par)->output);
			(*par)->output = open_APPEND_file_redirect(lex->line);
			if ((*par)->output < 0)
				exit_minishell(CANT_OPEN_FILE, 1, t);
			lex->outend = 0;
		}
		else
		{
			if (term_strlen_mas((*par)->arguments) == 1 || lex->flags_check == 1)
			{
				check_flags(lex);
			}
			if (lex->line != NULL && lex->line[0] != '\0')
				(*par)->arguments = strjoin_pr_mas(term_strlen_mas((*par)->arguments) + 1, (*par)->arguments, lex->line);
		}
		lex->line = free_null(lex->line);
		lex->j++;
	}
	else if (lex->outend == 1 || lex->out == 1 || lex->input == 1)
	{
		exit_minishell(RED_WHERE, 1, t);
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
	str = (char *)ft_calloc(1, sizeof(char));
	if (s == NULL || lex->envp == NULL)
	{
		if (s != NULL)
			free(s);
		return (NULL);
	}
	while (lex->envp[j] != NULL)
	{
		i = 0;
		while (lex->envp[j][i] && lex->envp[j][i] != '=')
		{
			str = lexer_charjoin(str, lex->envp[j][i++]);
		}
		if (!term_strcmp(str, s))
		{
			free(s);
			free(str);
			str = NULL;
			while (lex->envp[j][++i])
			{
				str = lexer_charjoin(str, lex->envp[j][i]);
			}
			return (str);
		}
		free(str);
		str = (char *)ft_calloc(1, sizeof(char));
		j++;
	}
	free(str);
	free(s);
	return (NULL);
}





void dollar(t_for_in_lexer *lex, t_for_in_parser **par)
{
	char *s;

	lex->i++;
	(*par)->j = (*par)->j;
	s = NULL;
	if ((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] == '_'))
	{
		lex->dollar = 1;
		while((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] >= 48 && lex->s[lex->i] <= 57) || (lex->s[lex->i] == '_'))
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




void lexer(t_for_in_lexer *lex, t_for_in_parser **par,  t_for_in_terminal *t, t_envp *sh_envp)
{
	t_for_in_parser *t_p;

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
						exit_minishell(ERROR_E, 1, t);
				}
				else
					lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit_minishell(M_QUOTES, 1, t);
		}
		else if (lex->s[lex->i] == 39)
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != 39)
			{
				lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
				exit_minishell(M_QUOTES, 1, t);
		}
		else if (lex->s[lex->i] == '$')
		{
			dollar(lex, par);
		}
		else if (lex->s[lex->i] == '|')
		{
			put_line_in_mas(lex, par, t);
			lex->pipe = 1;
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] != '>')
		{
			put_line_in_mas(lex, par, t);
			lex->out = 1;
		}
		else if (lex->s[lex->i] == '>' && lex->s[lex->i + 1] == '>')
		{
			put_line_in_mas(lex, par, t);
			lex->outend = 1;
			lex->i++;
		}
		else if (lex->s[lex->i] == '<')
		{
			put_line_in_mas(lex, par, t);
			lex->input = 1;
		}
		else if (lex->s[lex->i] == 92)
		{
			if (lex->s[lex->i + 1] != '\0')
				lex->line = lexer_charjoin(lex->line, lex->s[++lex->i]);
			else
				exit_minishell(ERROR_E, 1, t);
		}
		else if (lex->s[lex->i] == ';')
		{
			put_line_in_mas(lex, par, t);
			/*(void)sh_envp;
			(void)t;
			(void)t_p;*/
			del_settings_term(t);	//Восстанавливаем терминал
			executor_secretary(par, sh_envp, t); //->
			del_free_par(par); //Очистить par
			do_settings_term(t);	//Ломаем терминал
			free(lex->t_p);
			(*par) = ft_calloc(1, sizeof(t_for_in_parser));
			(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
			lex->t_p = *par;
			(*par) = (*par)->next;
			(*par)->key = 1;
			(*par)->previous = lex->t_p;
			(*par)->arguments = (char **)ft_calloc(1, sizeof(char *));
			(*par)->output = -2;
			(*par)->input = -2;
		}
		else if (lex->s[lex->i] != ' ' && lex->s[lex->i] != 10)
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
		else if (lex->s[lex->i] == ' ' && lex->line && lex->line != NULL)
		{
			put_line_in_mas(lex, par, t);
		}
		lex->i++;
	}
	put_line_in_mas(lex, par, t);
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
		*par = (*par)->previous;
	}
}

void line_from_terminal_to_lexer(char *s, t_for_in_terminal *t, t_envp *sh_envp)
{
	t_for_in_lexer lex;
	t_for_in_parser *par;

	lex.s = s;
	int i;
	i = 0;
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
	lex.t_p = par;
	par = par->next;
	par->key = 1;
	par->previous = lex.t_p;
	lex.flags_arg = (int *)ft_calloc(128, sizeof(int));
	lex.i = 0;
	while(lex.i < 127)
		lex.flags_arg[lex.i++] = 0;
	lex.i = 0;
	lex.flags_check = 0;

	par->arguments = (char **)ft_calloc(1, sizeof(char *));
	par->output = -2;
	par->input = -2;
	lexer(&lex, &par, t, sh_envp);

	free(lex.flags_arg);
	// print_par(&par); //Для печати
	// (void)sh_envp;
	del_settings_term(t);	//Восстанавливаем терминал
	executor_secretary(&par, sh_envp, t); //->
	del_free_par(&par); //Очистить par
	do_settings_term(t);	//Ломаем терминал
	free(lex.t_p);
}
