#include "minishell.h"

int			ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s || s == NULL || !s[i])
	{
		return (0);
	}
	while (s[i] && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int			ft_strlen_mas(char **s)
{
	int i;

	i = 0;
	if (!s || !s[i] ||  s[0] == NULL)
		return (0);
	while (s[i] && s[i] != NULL)
		i++;
	return (i);
}

char **strjoin_for_mas(int len, char **s, char *line)
{
	int i;
	char **new_s;

	i = 0;
	if (!(new_s = (char **)malloc((len + 1) * sizeof(char *))))
		return NULL;
	while (s && s[i] != NULL && i < len)
	{
		if (!(new_s[i] = (char *)malloc((ft_strlen(s[i]) + 1) * sizeof(char))))
			return NULL;
		new_s[i] = ft_strjoin(NULL, s[i]);
		if (s[i])
			free((void *)s[i]);
		i++;
	}
	if (!(new_s[i] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char))))
		return NULL;
	new_s[i] = ft_strjoin(NULL, line);
	new_s[++i] = NULL;
	if (s)
		free((void **)s);
	return (new_s);
}