#include "minishell.h"

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
					{
						lex->exit = 1;
						lex->line = free_null(lex->line);
						ft_puterrln(ERROR_E);
						return ;
					}
				}
				else
					lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
			{
				lex->exit = 1;
				lex->line = free_null(lex->line);
				ft_puterrln(M_QUOTES);
				return ;
			}
		}
		else if (lex->s[lex->i] == 39)
		{
			while (lex->s[++lex->i] != '\0' && lex->s[lex->i] != 39)
			{
				lex->line = lexer_charjoin(lex->line, lex->s[lex->i]);
			}
			if (lex->s[lex->i] == '\0')
			{
				lex->exit = 1;
				lex->line = free_null(lex->line);
				ft_puterrln(M_QUOTES);
				return ;
			}
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
			{
				lex->exit = 1;
				lex->line = free_null(lex->line);
				ft_puterrln(ERROR_E);
				return ;
			}
		}
		else if (lex->s[lex->i] == ';')
		{
			put_line_in_mas(lex, par);
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
			put_line_in_mas(lex, par);
		}
		if (lex->exit == 1)
			return ;
		lex->i++;
	}
	put_line_in_mas(lex, par);
	(*par)->next = ft_calloc(1, sizeof(t_for_in_parser));
	if (lex->exit == 1)
		return ;
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
	/*if(1 == 1)
	{
		open("src", O_RDWR);
		printf("\n%s\n", strerror(errno));
		return ;
	}*/
	//write(1, strerror(errno), strlen(strerror(errno)));
	t_for_in_lexer lex;
	t_for_in_parser *par;

	//printf("\ns = %s", s);
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

	lex.exit = 0;
	lex.line = (char *)ft_calloc(1, sizeof(char));
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
	//printf("\nstr = %s", lex.s);
	free(lex.flags_arg);
	//print_par(&par); //Для печати
	//(void)sh_envp;
	if (lex.exit == 0)
	{
		del_settings_term(t);	//Восстанавливаем терминал
		executor_secretary(&par, sh_envp, t); //->
		do_settings_term(t);	//Ломаем терминал
	}
	//printf("\nstr = %s", lex.s);
	del_free_par(&par); //Очистить par
	free(lex.t_p);
}
