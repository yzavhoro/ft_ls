//
// Created by Yevheniia ZAVHORODNIA on 12/9/18.
//

#include "../inc/ft_ls.h"

void sort(t_file * files){
	char *a = files->name;
	if (a[0] == 12)
		ft_putendl("NOTHING");
}

void print(t_file *files){
	while(files){
		ft_putendl(files->name);
		files = files->next;
	}
}

void add_subdir(t_subdirs ** list, char *name){
	t_subdirs *new_sdir;
	t_subdirs *tmp;

	if (!list)
		return;
	new_sdir = (t_subdirs*)malloc(sizeof(t_subdirs));
	new_sdir->name = name;
	new_sdir->next = NULL;
	if (!*list)
		*list = new_sdir;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sdir;
	}
}

t_subdirs *get_subdirs(t_file *files, char *path) {
	t_subdirs *subdirs = NULL;
	while (files){
		if (files->is_dir) {
			add_subdir(&subdirs, ft_strjoin(ft_strjoin(path, "/"), files->name));
		}
		files = files->next;
	}
	return subdirs;
}

void print_recursively(t_subdirs * subdirs) {
	if (!subdirs)
		return ;
	while (subdirs)
	{
		ft_printf("\n%s:\n", subdirs->name);
		t_file* files = read_dir(subdirs->name);
		sort(files);
		print(files);
		print_recursively(get_subdirs(files, subdirs->name));
		subdirs = subdirs->next;
	}
}