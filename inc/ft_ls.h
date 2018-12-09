#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <time.h>

# define DISPLAY_HIDDEN (g_params->flags.a == 1)

typedef struct			s_file {
	char				*name;
	char 				is_dir : 1;
	unsigned int		namelen;
	unsigned char		type;
	struct s_file		*next;
}						t_file;

typedef struct			s_ls_flags {
	char				a : 1;
}						t_ls_flags;

typedef struct			s_params {
	unsigned int		count;
	unsigned int		cols;
	unsigned int		col_wdth;
	t_file				*first;
	t_ls_flags			flags;
}						t_params;

typedef struct			s_subdirs {
	struct s_subdirs	*next;
	char				*name;
}						t_subdirs;

extern t_params * g_params;

void					print_with_width(const char *str, int width);
void					print_recursively(t_subdirs * subdirs);
t_file					*read_dir(char *dir_name);
#endif
