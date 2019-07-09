#include "../inc/ft_ls.h"
typedef int (*cmp_func)(t_file*, t_file*);

int compare_name(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) > 0);
}

int compare_time(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) > 0);
}

//TODO
int compare_name_rev(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) < 0);
}
//TODO
int compare_time_rev(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) < 0);
}

cmp_func get_cmp_func(t_flags flags) {
	if (flags.r) {
		if (flags.t) {
			return compare_time_rev;
		} else {
			return compare_name_rev;
		}
	} else {
		if (flags.t) {
			return compare_time;
		} else {
		return compare_name;
		}
	}
}