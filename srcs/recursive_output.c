//
// Created by Yevheniia ZAVHORODNIA on 12/9/18.
//

#include "../inc/ft_ls.h"

int compare(t_file *file1, t_file *file2){
	return (ft_strcmp(file1->name, file2->name) > 0);
}

void sort(t_file ** files){
	int len;

	len = 0;
	while(files[len])
		len++;
	quick_sort(files, 0, len - 1, compare);
//	char *a = files->name;
//	if (a[0] == 12)
//		ft_putendl("NOTHING");
}

void print(t_file **files){
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

t_file **to_array(t_file *list) {
	int		len;
	t_file	*tmp;
	t_file	**array;
	int		i;

	len = 0;
	tmp = list;
	while (tmp && ++len)
		tmp = tmp->next;
	array = (t_file**)malloc(sizeof(t_file*) * (len + 1));
	i = 0;
	tmp = list;
	while (i < len) {
		array[i++] = tmp;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return array;
}

void print_recursively(t_subdirs * subdirs) {
	if (!subdirs)
		return ;
	while (subdirs)
	{
		ft_printf("\n%s:\n", subdirs->name);
		t_file** files = to_array(read_dir(subdirs->name));
		sort(files);
		print(files);
		print_recursively(get_subdirs(files, subdirs->name));
		subdirs = subdirs->next;
	}
}