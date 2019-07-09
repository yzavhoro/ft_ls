#include "../inc/ft_ls.h"
#include "compare.h"

//TODO call get_cmp_func once and keep the pointer somewhere till the
//programm end as it won't change
static void sort(t_dir_info *dir_info, t_flags flags)
{
	quick_sort(dir_info->files, 0, dir_info->n - 1, get_cmp_func(flags));
}

static t_subdirs *print_simple(char *path, t_flags flags)
{
	t_dir_info	*dir_info;
	t_subdirs	*subdirs;

	dir_info = (t_dir_info*)ft_memalloc(sizeof(t_dir_info));
	read_dir(dir_info, flags); //TODO
	sort_dir(dir_info, flags);
	print_dir(dir_info, flags); //TODO
	if (RECURSIVE_OUTPUT(flags)) {
		subdirs = get_subdirs(dir_info->files, path);
	}
	return subdirs;
}

void print(t_flags flags, t_subdirs *dirs)
{
	t_subdirs *subdirs;

	while (dirs) {
		subdirs = print_simple(dirs->path, flags);
		if (RECURSIVE_OUTPUT(flags)) {
			print_recursively(subdirs, flags);
		}
		dirs = dirs->next;
	}
}