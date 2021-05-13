
#include "minishell.h"
t_all g_all;
//gcc -g main.c work_with_file.c ft_strjoin_for_mas.c ft_strjoin_for_line.c  terminal_up_down_fun.c terminal_main_fun.c gnl.c  -ltermcap && ./a.out
int main(int argc, char *argv[], char const *envp[])
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
	return 0;
}
/*
int main(int argc, char *argv[], char const *envp[])
{
	(void )argc;
	(void )argv;
	(void )envp;
	struct stat buf;
	char *place  = ft_strdup("./");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		printf("'%s' is a dir\n", place);
	free(place);
	place  = ft_strdup("/bin");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		printf("'%s' is a dir\n", place);
	free(place);
	place  = ft_strdup("../bin");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		printf("'%s' is a dir\n", place);
	free(place);
	place  = ft_strdup(".");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		printf("'%s' is a dir\n", place);
	free(place);
	place  = ft_strdup("./src/main.c");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) != S_IFDIR)
		printf("'%s' is not a dir\n", place);
	free(place);
	place  = ft_strdup("./stuff");
	stat(place, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		printf("'%s' is a dir\n", place);
	free(place);
}
 */
