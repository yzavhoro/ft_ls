//
// Created by Yevheniia ZAVHORODNIA on 12/9/18.
//

#include "../inc/ft_ls.h"
#include "compare.h"

void print_recursively(t_subdirs *dirs, t_flags flags) {
	t_dir_info	*dir_info;
	t_subdirs	*subdirs;

	while (dirs)
	{
		dir_info = (t_dir_info*)ft_memalloc(sizeof(t_dir_info));
		printf("\n%s:\n", dirs->path);
		read_dir(dir_info, flags); //TODO
		sort(dir_info, flags);
		print(dir_info, flags); //TODO
		subdirs = get_subdirs(dir_info->files, dirs->path);
		print_recursively(subdirs, flags);
		list_free(subdirs); //TODO
		dirs = dirs->next;
	}
}