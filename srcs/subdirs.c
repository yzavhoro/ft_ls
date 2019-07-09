#include "../inc/ft_ls.h"

static void add_subdir(t_subdirs **list, char *path)
{
	t_subdirs	*new_sdir;
	t_subdirs	*tmp;

	new_sdir = (t_subdirs*)ft_memalloc(sizeof(t_subdirs));
	new_sdir->path = path;
	if (!*list)
		*list = new_sdir;
	else
	{
		tmp = *list;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = new_sdir;
	}
}

#define DIR 0 //TODO

t_subdirs *get_subdirs(t_file **files, char *path)
{
	t_subdirs *subdirs;
	int i;

	subdirs = NULL;
	i = 0;
	while (files[i])
	{
		if (files[i]->type == DIR) //TODO
		{
			add_subdir(&subdirs, ft_strnjoin(3, path, "/", files[i]->name));
		}
		i++;
	}
	return subdirs;
}

void parse_dirs(char **files, t_subdirs **subdirs)
{
	while (*files) {
		add_subdir(subdirs, *files++);
	}
}