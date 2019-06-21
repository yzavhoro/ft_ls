#include <sys/stat.h>
#include "../inc/ft_ls.h"

t_file *fill_node(struct dirent *dp, t_flags flags)
{
	t_file			*new_f;
	struct stat		st;

	if (!DISPLAY_HIDDEN(flags) && dp->d_name[0] == '.')
	{
		return ;
	}
	new_f = (t_file*)malloc(sizeof(t_file));
	new_f->name = ft_strdup(dp->d_name);
	if (LONG_OUTPUT(flags)) {
		new_f->namelen = (unsigned int)ft_strlen(dp->d_name);
		new_f->type = dp->d_type;
		lstat(new_f->name, &st); //get file statistics
	}
	return (new_f);
}

//TODO upd this function later
#if 0
void count_params(t_params* params) {
	struct winsize	w;
	int				win_width;
	t_file			*tmp;

	ioctl(0, TIOCGWINSZ, &w);
	win_width = (int)w.ws_col;
	tmp = params->first;
	params->col_wdth = tmp->namelen;
	while (tmp)
	{
		if (tmp->namelen > params->col_wdth)
			params->col_wdth = tmp->namelen;
		tmp = tmp->next;
	}
	params->col_wdth++; /*including space*/
	params->cols = win_width / params->col_wdth;
	if (!params->cols)
		params->cols = 1;
}
#endif

t_file **read_dir(char *dir_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			**files_list;
	int				n;

	files_list = NULL;
	dirp = opendir(dir_name);
	if (dirp == NULL) //TODO handle error normally
	{
		ft_putendl("error while opening");
		return NULL;
	}
	while ((dp = readdir(dirp)) != NULL) {
		n++;
	}
	(void)closedir(dirp);
	files_list = (t_file**)malloc(sizeof(t_file*) * (n + 1));
	dirp = opendir(dir_name);
	n = 0;
	while ((dp = readdir(dirp)) != NULL) {
		files_list[n++] = fill_node(dp, flags);
	}
	files_list[n] = NULL;
	(void)closedir(dirp);	
	return files_list;
}

int main()//int ac, char **av)
{
	t_flags		flags = {0};
	t_subdirs	*subdirs = (t_subdirs*)malloc(sizeof(t_subdirs));

	subdirs->path = ".";
	subdirs->next = NULL;
	if (RECURSIVE_OUTPUT(flags))
		print_recursively(subdirs, flags);
	else
		print_simple(subdirs->path, flags);
	return (0);
}
