
#include "minishell.h"
t_all g_all;

//gcc -g main.c work_with_file.c ft_strjoin_for_mas.c ft_strjoin_for_line.c  terminal_up_down_fun.c terminal_main_fun.c gnl.c  -ltermcap && ./a.out

int main(int argc, char const *argv[], char const *envp[])
{
	t_envp	sh_envp;

	ft_bzero(&g_all, sizeof(t_all));
	ft_envp_cpy(envp, &sh_envp);

	terminal(argc, argv, &sh_envp);
	return 0;
}

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
