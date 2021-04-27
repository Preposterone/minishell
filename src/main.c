
#include "minishell.h"

//gcc -g main.c work_with_file.c ft_strjoin_for_mas.c ft_strjoin_for_line.c  terminal_up_down_fun.c terminal_main_fun.c gnl.c  -ltermcap && ./a.out

int main(int argc, char const *argv[], char const *envp[])
{
	t_envp	sh_envp;

	ft_envp_cpy(envp, &sh_envp);
<<<<<<< HEAD
	terminal(argc, argv, &sh_envp);
    return 0;
}
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	const char *src = "system of a down";
	const char *dst = "12";
	int n = 6;
	printf("%d\n", strncmp(src, dst, n));
	printf("%d\n", ft_strncmp(src, dst, n));
	printf("%d\n", strncmp("system of a down", "12", 6));
	printf("%d\n", ft_strncmp("system of a down", "12", 6));
	return (0);
}*/


/* exectuor test
int main(int argc, char const *argv[], char const *envp[])
{
	t_envp	sh_envp;
	(void)argv;
	(void)argc;
	ft_envp_cpy(envp, &sh_envp);
	char *cmd = "cat";
	char **args = malloc(2 * sizeof(char *));
//	args[0] = ft_strdup("leakcheck");
	args[0] = NULL;
	args[1] = NULL;
	char *cmdpath = expander(cmd, sh_envp.sh_path);
	executor(cmd, args, cmdpath, &sh_envp);
	return (0);
}*/

/* expander test
=======
	terminal(argc, argv, envp);
	return 0;
}
	char	cmd[100];
	ft_envp_cpy(envp, &sh_envp);
	while (true)
	{
		ft_bzero(&cmd, 100);
		scanf("%s", cmd);
		cmdpath = expander(cmd, sh_envp.sh_path);
		if (!cmdpath)
		{
			printf("Not found.\n");
			break;
		}
		else
			printf("%s\n", cmdpath);
		free(cmdpath);
	}
	return (0);
}*/
