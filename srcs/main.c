#include <sys/stat.h>
#include "../inc/ft_ls.h"

#define CHECK_MAX(curr, max) if ((curr) > (max)) (max) = (curr);

t_file *fill_node(struct dirent *dp, t_flags flags, int *n)
{
	t_file			*new_f;
	struct stat		st;

	if (!DISPLAY_HIDDEN(flags) && dp->d_name[0] == '.')
	{
		return ;
	}
	(*n)++;
	new_f = (t_file*)malloc(sizeof(t_file));
	new_f->name = ft_strdup(dp->d_name);
	if (LONG_OUTPUT(flags)) {
		new_f->namelen = (unsigned int)ft_strlen(dp->d_name);
		new_f->type = dp->d_type;
		lstat(new_f->name, &st); //get file statistics
	}
	return (new_f);
}

void	read_dir(t_dir_info *di, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			**files_list;

	di->n = 0;
	dirp = opendir(di->dir_name);
	if (dirp == NULL) //TODO handle error normally
	{
		ft_putendl("error while opening");
		return ;
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		// TODO deside whether to keep the commented line below
		// if (DISPLAY_HIDDEN(flags) || dp->d_name[0] != '.')
			di->n++;
	}
	(void)closedir(dirp);
	files_list = (t_file**)malloc(sizeof(t_file*) * (di->n + 1));
	dirp = opendir(di->dir_name);
	di->n = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		files_list[di->n] = fill_node(dp, flags, &di->n);
	}
	files_list[di->n] = NULL;
	(void)closedir(dirp);
}

static void usage()
{
	printf("usage: ft_ls [-Raltr] [file ...]\n");
	exit(0);
}

static void illegal_option(char c)
{
	printf("ft_ls: illegal option -- %c\n", c);
	usage();
}

static void parse_flags(char *arg, t_flags *flags)
{
	++arg;
	while (*arg)
	{
		switch (*arg) {
			case 'a':
				flags->a = 1;
				break;
			case 'l':
				flags->l = 1;
				break;
			case 't':
				flags->t = 1;
				break;
			case 'r':
				flags->r = 1;
				break;
			case 'R':
				flags->R = 1;
				break;
			default:
				illegal_option(*arg);
		}
	}
}

#define IS_FLAG(c) ((c)[0] == '-' && (c)[1])

static void parce_args(char **argv, t_flags * flags, t_subdirs **subdirs)
{
	while (*argv) {
		if (IS_FLAG(*argv)) {
			parse_flags(*argv++, &flags);
		}
		else {
			parse_dirs(argv, subdirs);
			break;
		}
	}
	if (!*subdirs) {
		*subdirs = (t_subdirs *)malloc(sizeof(t_subdirs));
		(*subdirs)->path = ".";
		(*subdirs)->next = NULL;
	}
}

int main(int argc, char **argv)
{
	t_flags		flags = {0};
	t_subdirs	*subdirs = NULL;

	parce_args(++argv, &flags, &subdirs);
	print(flags, subdirs);
	return (0);
}
