#include "termcap.h"

char	*ft_strjoin_n(char *s2, char *r, int i)
{
	r = malloc(sizeof(char) * (strlen(s2) + 1));
	if (!r)
		return (NULL);
	i = -1;
	while (s2[++i] && s2[i] != '\n')
		r[i] = s2[i];
	r[i] = '\0';
	//if (s2)
		//free((void *)s2);
	return (r);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*r;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (!s1)
		return (ft_strjoin_n(s2, r, i));
	r = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		r[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j] && s2[i] != '\n')
		r[i++] = s2[j];
	r[i] = '\0';
	//if (s1)
		//free((void *)s1);
	//if (s2)
		//free((void *)s2);
	return (r);
}

char	*str_delet_last_char(char *s1)
{
	char			*r;
	unsigned int	i;

	if (!s1 && strlen(s1) == 1)
		return (NULL);
	r = malloc(sizeof(char) * (strlen(s1)));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i + 1] && i < strlen(s1) - 1)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	//if (s1)
		//free((void *)s1);
	return (r);
}


char	*ft_strjoin_n_str(char *s2, char *r, int i)
{
	r = malloc(sizeof(char) * (strlen(s2) + 1));
	if (!r)
		return (NULL);
	i = -1;
	while (s2[++i] && s2[i] != '\n')
		r[i] = s2[i];
	r[i] = '\0';
	return (r);
}

char	*ft_strjoin_str(char *s1, char *s2)
{
	char			*r;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (!s1)
		return (ft_strjoin_n_str(s2, r, i));
	r = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		r[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j] && s2[i] != '\n')
		r[i++] = s2[j];
	r[i] = '\0';
	//if (s1)
		//free((void *)s1);
	return (r);
}
