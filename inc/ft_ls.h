#ifndef _FT_LS_H
# define _FT_LS_H

# include "../libftprintf/includes/get_next_line.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <time.h>
# include <stdint.h>
# include <stdio.h>

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
	uint32_t			permissions;
	uint8_t				alt_acs;
	uint32_t			links;
	char				*owner;
	char				*group;
	char				*timestamp; //TODO see how to store it
}						t_file;

typedef struct			s_dir_info {
	char				*dir_name;
	t_file				**files;
	uint32_t			total;
	uint32_t			n; /*nubmer of files*/
	struct				s_alignmet_params {
		uint32_t	links;
		uint32_t	file_size;
		uint8_t		owner;
		uint8_t		group;
		uint8_t		file_name;
	}					al_pars;
}						t_dir_info;

#define MAX_LINKS(di)		((di)->al_pars.links)
#define MAX_FILE_SIZE(di)	((di)->al_pars.file_size)
#define MAX_OWNER_NL(di)	((di)->al_pars.owner)
#define MAX_GROUP_NL(di)	((di)->al_pars.group)
#define MAX_FILE_NAME(di)	((di)->al_pars.file_name)

typedef struct			s_subdirs {
	struct s_subdirs	*next;
	char				*path;
}						t_subdirs;

void					print_recursively(t_subdirs * subdirs, t_flags flags);
void					read_dir(t_dir_info *dir_info, t_flags flags);
void					quick_sort(t_file **array, int start, int end, int (*f)(t_file*, t_file*));
t_subdirs				*get_subdirs(t_file **files, char *path);
void					print(t_flags flags, t_subdirs *dirs);

#endif /* _FT_LS_H */
