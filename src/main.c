
#include "termcap.h"

//gcc -g main.c work_with_file.c ft_strjoin_for_mas.c ft_strjoin_for_line.c  terminal_up_down_fun.c terminal_main_fun.c gnl.c  -ltermcap && ./a.out

int main(int argc, char const *argv[], char const *envp[])
{
	terminal(argc, argv, envp);
    return 0;
}