#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <time.h>
# include <stdint.h>

# define DISPLAY_HIDDEN(flags) ((flags).a)
# define REVERSE_SORT(flags) ((flags).r)
# define TIME_SORT(flags) ((flags).t)
# define RECURSIVE_OUTPUT(flags) ((flags).R)
# define LONG_OUTPUT(flags) ((flags).l)

typedef struct			s_flags {
	uint8_t				a:1,
						l:1,
						t:1,
						r:1,
						R:1,
						rsrvd:3;
}						t_flags;

typedef struct			s_file {
	char				*name;
	uint32_t			namelen;
	uint8_t				type;
}						t_file;

typedef struct			s_dir_info {
	uint32_t			total;
	t_file				**files;
	/* alignment params */
}						t_dir_info;

typedef struct			s_subdirs {
	struct s_subdirs	*next;
	char				*path;
}						t_subdirs;

void					print_recursively(t_subdirs * subdirs, t_flags flags);
t_file					**read_dir(char *dir_name, t_flags flags);
void					quick_sort(t_file **array, int start, int end, int (*f)(t_file*, t_file*));
void sort(t_file ** files);
t_file **to_array(t_file *list);

#endif
