
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
/*
//wait, pipes, dup2
int main(int argc, char const *argv[], char *envp[]) {
	int pid = fork();
	(void)argv;
	(void)argc;
	if (pid == 0)
	{
		int file = open("pingRslt.txt", O_WRONLY | O_CREAT, 0644);
		if (file == -1) {return 23;}
		int file2 = dup2(file, STDOUT_FILENO);
		close(file);
		(void)file2;

		char *args[] = {"ping", "-c", "1", "google.com", NULL};
		int err = execve("/sbin/ping",
				args,
				envp);
		if (err == -1) {
			perror("Not found");
			return(255);
		}
	} else {
		int waitstatus;
		wait(&waitstatus);
		if (WIFEXITED(waitstatus)) {
			int statcode = WEXITSTATUS(waitstatus);
			if (statcode == 0) {
				printf("Success\n");
			} else {
				printf("Fail\n");
			}
		}
		printf("Post processing \n");
	}

} */

/*
//Bash pipes
int main(int argc, char const *argv[], char *envp[]) {
	(void)argv;
	(void)argc;
	int fd[2];
	if (pipe(fd) == -1) {return 1;}
	int pid1 = fork();

	if (pid1 == 0) {
		char *args[] = {"ping", "-c", "1", "google.com", NULL};
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		int err = execve("/sbin/ping",
				args,
				envp);
		if (err == -1) {
			perror("Not found");
			close(1);
			return(255);
		}
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		char *args[] = {"grep", "packets", NULL};
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep",
				args,
				envp);
		close(0);
	}
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
 */
/*
int main(int argc, char const *argv[], char *envp[]) {
	(void)argv;
	(void)argc;

	int fd[3][2];
	for (size_t i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) < 0) {
			return 1;
		}
	}
	int pid1 = fork();

	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][1]);
		close(fd[2][0]);
		int x;
		read(fd[0][0], &x, sizeof(x));
		x += 5;
		write(fd[1][1], &x, sizeof(x));
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	int pid2 = fork();
	if (pid2 == 0) {
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x;
		read(fd[1][0], &x, sizeof(x));
		x += 5;
		write(fd[2][1], &x, sizeof(x));
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}

	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int x = 0;
	write(fd[0][1], &x, sizeof(x));
	read(fd[2][0], &x, sizeof(x));
	printf("%d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	(void)envp;
	return (0);
} */

/*
# define PROCESS_NUM 100

int main(int argc, char const *argv[], char *envp[]) {
	(void)argv;
	(void)argc;
	(void)envp;

	int pipes[PROCESS_NUM + 1][2];
	int pids[PROCESS_NUM];

	for (size_t i = 0; i < PROCESS_NUM + 1; i++) {
		if (pipe(pipes[i]) == -1) {
			perror("PIPES creating error"); }
	}
	for (size_t i = 0; i < PROCESS_NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Cannot create process");
			return (2);
		}
		if (pids[i] == 0) {
			for (size_t j = 0; j < PROCESS_NUM; j++)
			{
				if (i != j) {
					close(pipes[j][0]);	//read end
				}
				if (i+1 != j)
				{
					close(pipes[j][1]);	//write end
				}
				int x;
				if (read(pipes[i][0], &x, sizeof(x)) == -1 ) {
					perror("READ ERROR"); return 2;
				}
				printf("Process #%zu, caught y = %d\n", i, x);
				x++;
				if (write(pipes[i + 1][1], &x, sizeof(x)) == -1 ) {
					perror("WRITE ERROR"); return 2;
				}
				close(pipes[i][0]);
				close(pipes[i + 1][0]);
				return 0;
			}
		}
	}
	for (size_t j = 0; j < PROCESS_NUM; j++)
	{
		if (j != PROCESS_NUM) {
			close(pipes[j][0]);	//read end
		}
		else if (j != 0)
		{
			close(pipes[j][1]);	//write end
		}
	}
	int y = 5;
	printf("Sending %d through the pipes\n", y);
	if (write(pipes[0][1], &y, sizeof(y)) == -1 ) {
		perror("WRITE ERROR"); return 2;
	}
	if (read(pipes[PROCESS_NUM][0], &y, sizeof(y)) == -1) {
		perror("WRITE ERROR"); return 2;
	}
	printf("The final result is %d\n", y);
	close(pipes[0][1]);
	close(pipes[PROCESS_NUM][0]);
	for (size_t i = 0; i < PROCESS_NUM; i++) {
		wait(NULL);
	}
	return (0);
}
 */
