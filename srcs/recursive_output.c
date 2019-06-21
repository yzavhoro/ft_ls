//
// Created by Yevheniia ZAVHORODNIA on 12/9/18.
//

#include "../inc/ft_ls.h"

static int compare(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) > 0);
}

static void sort(t_file **files)
{
	int len;

	len = 0;
	while(files[len])
		len++;
	quick_sort(files, 0, len - 1, compare);
}

static void print(t_file **files){
	int i;

	i = 0;
	while(files[i]){
		ft_putendl(files[i]->name);
		i++;
	}
}

void add_subdir(t_subdirs ** list, char *name){
	t_subdirs *new_sdir;
	t_subdirs *tmp;

	if (!list)
		return;
	new_sdir = (t_subdirs*)malloc(sizeof(t_subdirs));
	new_sdir->path = name;
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

/*
 * function gets list of all contents in a directory
 * and creates another list including only subdirectories
 */
t_subdirs *get_subdirs(t_file **files, char *path) {
	t_subdirs *subdirs = NULL;
	int i;

	i = 0;
	while (files[i]){
		if (files[i]->is_dir) {
			add_subdir(&subdirs, ft_strjoin(ft_strjoin(path, "/"), files[i]->name));
		}
		i++;
	}
	return subdirs;
}

void print_recursively(t_subdirs * subdirs, t_flags flags) {
	t_dir_info dir_info;

	if (!subdirs)
		return ;
	while (subdirs)
	{
		ft_printf("\n%s:\n", subdirs->path);
		t_file** files = read_dir(subdirs->path, flags);
		sort(files);
		print(files);
		print_recursively(get_subdirs(files, subdirs->path));
		subdirs = subdirs->next;
	}
}