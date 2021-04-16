/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:45:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/15 13:36:14 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>
#include  <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

void wr(char *s)
{
	write(1, s, strlen(s));
	write(1, "\n", 1);
}

/*

int  main(void)
{
	pid_t ch0 = 0, ch1 = 0;
	char buf[1000] = {0};
	wr("Parent starts");
	ch0 = fork();
	if (ch0 == 0)
		wr("I am a child");
	else
	{
		srand(time(NULL));
		sprintf(buf, "Parent calcuations: %d", rand());
		wr(buf);
	}
	int status = -1;
	ch1 = wait(&status);
	if (ch1 != -1)
	{
		sprintf(buf, "Child pid: %d, exited with status: %d", ch1, status);
		wr(buf);
	}
	exit(0);
}
*/
