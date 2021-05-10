#include "minishell.h"

static int	ft_print_arr_prepend(char **arr, char *prepend)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd(prepend,1);
		ft_putendl_fd(arr[i], 1);
	}
	return (0);
}

/*
	Mark each name to be passed to child processes in the environment.
	The return status is zero unless an invalid option is supplied,
	one of the names is not a valid shell variable name.
*/
/**
 *
 * @param args is a key=value pair
 * where @key has syntax:	xx123=
 * 							xxxx=
 * 							_123=
 * 							_xxx123=
 */
int ft_do_export(char **args, t_envp *sh_envp)
{
	int		i;
	int		equalslocation;
	char	*key;

	i = -1;
	if (!args[0])
		return (ft_print_arr_prepend(sh_envp->sh_envp, "declare -x "));
	while (args[++i])
	{
		equalslocation = ft_strchr_index(args[i], '=') + 1;
		// add check for alphabetic characters as key
		if (equalslocation != -1 && (ft_isstralpha(args[i], equalslocation)
									 || args[i][0] == '_'))
		{
			key = ft_strndup(args[i], equalslocation);
			ft_update_envp_elem(key, &args[i][equalslocation], sh_envp);
			free(key);
		}
		else
		{
			if (equalslocation > 0)
				return (1);//TODO: print export error invalid arg
		}
	}
	return (0);
}
