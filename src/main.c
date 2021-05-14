/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:19:46 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 13:53:33 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Copy of incoming enviroment variables
 */

void	ft_envp_cpy(const char *envp[], t_envp *buf)
{
	int		i;
	char	**envp_cpy;
	char	*path;

	i = 0;
	while (envp[i])
		i++;
	envp_cpy = (char **)ft_calloc(i + 1, sizeof(char *));
	path = NULL;
	i = -1;
	while (envp[++i])
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = &envp_cpy[i][5];
		else if (!ft_strncmp(envp[i], "TERM=", 5))
			buf->sh_term = &envp_cpy[i][5];
	}
	buf->sh_envp = envp_cpy;
	buf->sh_path = path;
}

t_all	g_all;

int	main(int argc, char *argv[], char const *envp[])
{
	t_envp	sh_envp;

	ft_bzero(&g_all, sizeof(t_all));
	ft_bzero(&sh_envp, sizeof(sh_envp));
	sh_envp.truefd0 = 3;
	sh_envp.truefd1 = 4;
	dup2(0, sh_envp.truefd0);
	dup2(1, sh_envp.truefd1);
	ft_envp_cpy(envp, &sh_envp);
	terminal(argc, argv, &sh_envp);
	return (0);
}

/*
int main(void)
{
	char *s1;
	char *s2;

	s1 = ft_strdup("PePsi");
	s2 = ft_strdup("Pepsi");
	printf("S1: '%s'\tS2: '%s'\tResult of comparison:
	'%d'\n", s1, s2, ft_strcmpl(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("pepsi");
	s2 = ft_strdup("pepsi");
	printf("S1: '%s'\tS2: '%s'\tResult of comparison:
	'%d'\n", s1, s2, ft_strcmpl(s1, s2));
	free(s1);
	free(s2);
	s1 = ft_strdup("PEPSI");
	s2 = ft_strdup("pepsi");
	printf("S1: '%s'\tS2: '%s'\tResult of comparison:
	'%d'\n", s1, s2, ft_strcmpl(s1, s2));
	free(s1);
	free(s2);
	s1 = ft_strdup("Cola");
	s2 = ft_strdup("pEPsI");
	printf("S1: '%s'\tS2: '%s'\tResult of comparison:
	'%d'\n", s1, s2, ft_strcmpl(s1, s2));
	free(s1);
	free(s2);
	return 0;
}
*/
