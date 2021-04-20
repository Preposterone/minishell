
#include "termcap.h"

int how_many_space(char *s)
{
	int i;
	int j;
	int f;

	i = 0;
	f = 0;
	j = 0;
	while (s[i] != '\0' && s[i])
	{
		if (s[i] >= 33 && f == 0)
		{
			f = 2;
			j++;
		}
		else if (f == 2 && s[i] <= 32)
			f = 0;
		i++;
	}
	return (j);
}

int len_words(char *s, int y)
{
	int i;
	int j;
	int f;

	i = 0;
	f = 0;
	j = 0;
	while (s[i] != '\0' && s[i])
	{
		if (s[i] >= 33 && f == 0)
		{
			f = 2;
			if (j == y)
			{
				y = 0;
				while (s[i] != '\0' && s[i] && s[i++] > 32)
					y++;
				return (y);
			}
			j++;
		}
		else if (f == 2 && s[i] <= 32)
			f = 0;
		i++;
	}
	return (j);
}

char *take_word_from_array(char *s, int y, int k, char *line)
{
	int i;
	int j;
	int f;

	i = 0;
	f = 0;
	j = 0;
	while (s[i] != '\0' && s[i])
	{
		if (s[i] >= 33 && f == 0)
		{
			f = 2;
			if (j == y)
			{
				y = 0;
				line = (char *)malloc(k * sizeof(char));
				while (s[i] != '\0' && s[i] && s[i] > 32)
					line[y++] = s[i++]; 
				return (line);
			}
			j++;
		}
		else if (f == 2 && s[i] <= 32)
			f = 0;
		i++;
	}
	return (NULL);
}
	
void line_from_terminal_to_lexer(char *s, t_for_in_terminal *t, int i)
{
	char **line;
	int i;

	t->len = how_many_space(s);
	line = (char **)malloc(t->len * sizeof(char *));
	if (!line)
		return ;
	while (++i < t->len)
		line[i] = take_word_from_array(s, i, len_words(s, i), line[i]);
	i = -1;
	//parser(t, line);
	while (++i < t->len)
	{
		if (line)
		{
			free((void *)line[i]);
			line[i] = NULL;
		}
	}
	if (line)
	{
		free((void **)line);
		line = NULL;
	}
}