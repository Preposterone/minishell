
#include "minishell.h"

//gcc -g main.c work_with_file.c ft_strjoin_for_mas.c ft_strjoin_for_line.c  terminal_up_down_fun.c terminal_main_fun.c gnl.c  -ltermcap && ./a.out

int main(int argc, char const *argv[], char const *envp[])
{
	t_envp	sh_envp;

	ft_envp_cpy(envp, &sh_envp);
	terminal(argc, argv, envp);
	return 0;
}

/*
int	main(int argc, char *argv[], const char *envp[])
{
	t_envp	sh_envp;
	char	*cmdpath;
	char	cmd[100];

	(void)argv;
	(void)argc;
	ft_bzero(&sh_envp, sizeof(sh_envp));
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
