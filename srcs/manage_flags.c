//
// Created by Yevheniia ZAVHORODNIA on 12/11/18.
//

#include "../inc/ft_ls.h"

#define IS_FLAG(argv) ((argv)[0] == '-' && (argv)[1])

void invalid_flag(char f) {
	ft_printf("ft_ls: illegal option: -- %c\n", f);
	ft_putendl("usage: ft_ls [-Ralrt] [file ...]");
	exit(0);
}

void set_flags(char *arg)
{
	int i;
	int j;

	char * flags = "Ralrt"; //TODO remove
	if (!arg)
		return;
	i = 0;
	while(arg[i]) {
		j = 0;
		while (arg[i] != flags[j])
			j++;
		if (j == 6)
			invalid_flag(arg[i]);
		g_params->flags |= (1 << j);
		i++;
	}
}

int parse_flags(char **argv)
{
	int i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i] && IS_FLAG(argv[i]))
	{
		set_flags(argv[i] + 1);
		i++;
	}
	return (i); //i is to know how many args to skip to get to directories
}