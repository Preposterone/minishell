
#include "minishell.h"

void dollar5(t_for_in_lexer *lex)
{
	lex->i++;
	lex->dol_str = ft_itoa(g_all.exit_code);
	if (lex->dol_str != NULL)
	{
		lex->line = term_strjoin(lex->line, lex->dol_str);
		free(lex->dol_str);
		lex->dol_str = NULL;
	}
}

void dollar4(t_for_in_lexer *lex)
{
	lex->i++;
	lex->dol_str = term_strjoin(NULL, "him");
	if (lex->dol_str != NULL)
	{
		lex->line = term_strjoin(lex->line, lex->dol_str);
		free(lex->dol_str);
		lex->dol_str = NULL;
	}
}

void dollar3(t_for_in_lexer *lex)
{
	lex->dol_str = lexer_charjoin(lex->dol_str, lex->s[lex->i]);
	lex->i++;
	lex->dol_str = find_in_envp(lex, lex->dol_str);
	if (lex->dol_str != NULL)
	{
		lex->line = term_strjoin(lex->line, lex->dol_str);
		free(lex->dol_str);
		lex->dol_str = NULL;
	}
}

void dollar2(t_for_in_lexer *lex)
{
	lex->dollar = 1;
	while((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] >= 48 && lex->s[lex->i] <= 57) || (lex->s[lex->i] == '_'))
	{
		lex->dol_str = lexer_charjoin(lex->dol_str, lex->s[lex->i]);
		lex->i++;
	}
	lex->dol_str = find_in_envp(lex, lex->dol_str);
	if (lex->dol_str != NULL)
	{
		lex->line = term_strjoin(lex->line, lex->dol_str);
		free(lex->dol_str);
		lex->dol_str = NULL;
	}
}

void dollar(t_for_in_lexer *lex, t_for_in_parser **par)
{

	lex->i++;
	(*par)->j = (*par)->j;
	lex->dol_str = NULL;
	if ((lex->s[lex->i] >= 65 && lex->s[lex->i] <= 90) || (lex->s[lex->i] >= 97 && lex->s[lex->i] <= 122) || (lex->s[lex->i] == '_'))
		dollar2(lex);
	else
	{
		if (lex->s[lex->i] >= 48 && lex->s[lex->i] <= 57)
			dollar3(lex);
		else if (lex->s[lex->i] == '-')
			dollar4(lex);
		else if (lex->s[lex->i] == '?')
			dollar5(lex);
		else if (lex->s[lex->i] == '*')
			lex->i++;
		else
			lex->line = lexer_charjoin(lex->line, lex->s[lex->i - 1]);
	}
	lex->i--;
}
