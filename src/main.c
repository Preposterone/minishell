
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


// Pipe test
/*
int main(void) {
	int fd[2];
	// fd[0] - read
	// fd[1] - write
	if (pipe(fd) == -1) {
		printf("An error occured when opening the pipe \n");
		return (1);
	}
	int id = fork();

	if (id == 0) {
		close(fd[0]);
		int x;
		printf("Input a num: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	} else {
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);
} */
/*
int main(void) {
	int arr[] = {1,2,3,4,1,10, 70};
	int arrSize = sizeof(arr) / sizeof(int);
	int fd[2];
	int start, end;
	if (pipe(fd) == -1) {
		perror("pipe error");
		return 1;
	}
	int id = fork();
	if (id == -1) {
		perror("fork error");
		return 2;
	} else if (id == 0) {
		start = 0;
		end = arrSize/2;
	} else {
		start = arrSize / 2;
		end = arrSize;
	}

	int sum = 0;
	int i;
	for (i = start; i < end ; i++) {
		sum += arr[i];
	}
	printf("Calculated partial sum: %d\n", sum);

	if (id == 0) {
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	} else {
		int sumFrCh;
		close(fd[1]);
		read(fd[0], &sumFrCh, sizeof(sumFrCh));
		close(fd[0]);
		int total = sum + sumFrCh;
		printf("Total sum is %d\n", total);
		wait(NULL);
	}
}
 *//*
#include <time.h>
int main(void) {
	int p1[2]; // Child to parent
	int p2[2];  // parent to child
	if (pipe(p1) == -1 || pipe(p2) == -1) {
		perror("An error occured when opening the pipe \n");
		return (1);
	}
	printf("Forking\n");
	int pid = fork();
	if (pid == -1) {return 2;}

	if (pid == 0) {
		//child process
		close(p1[0]);
		close(p2[1]);
		int x;
		if (read(p2[0], &x, sizeof(x)) == -1) {return 3;}
		printf("Recieived %d\n", x);
		x *= 4;
		if(write(p1[1], &x, sizeof(x)) ==-1)	{return 4;}
		printf("Wrote %d\n", x);
		close(p1[1]);
		close(p2[0]);
	} else {
		close(p1[1]);
		close(p2[0]);
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1) {return 5;}

		// printf("Wrote %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1)	{return 6;}
		printf("Result is %d\n", y);
		close(p1[0]);
		close(p2[1]);
		wait(NULL);
	}
	close(p1[0]);
	close(p1[1]);
	return (0);
}
 */
