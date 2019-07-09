#ifndef _COMPARE_H
#define _COMPARE_H

#include "../inc/ft_ls.h"

typedef int (*cmp_func)(t_file*, t_file*);

int compare_name(t_file *file1, t_file *file2);
int compare_time(t_file *file1, t_file *file2);
int compare_name_rev(t_file *file1, t_file *file2);
int compare_time_rev(t_file *file1, t_file *file2);

cmp_func get_cmp_func(t_flags flags);

#endif /* _COMPARE_H */