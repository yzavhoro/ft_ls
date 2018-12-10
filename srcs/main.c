#include <sys/stat.h>
#include "../inc/ft_ls.h"

t_params *g_params;

/*
 * function to add info
 * about read file to the list
 * of files in a directory
 */
void join_node(struct dirent *dp, t_file ** files_list)
{
	t_file			*new_f;
	struct stat		st;

	if (!files_list || (!DISPLAY_HIDDEN && dp->d_name[0] == '.'))
	{
		return ;
	}
	new_f = (t_file*)malloc(sizeof(t_file));
	new_f->name = ft_strdup(dp->d_name);
	new_f->namelen = (unsigned int)ft_strlen(dp->d_name);
	new_f->type = dp->d_type;
	lstat(new_f->name, &st);
	new_f->is_dir = ((st.st_mode & S_IFMT) == S_IFDIR);
	new_f->next = *files_list;
	*files_list = new_f;
}

//TODO upd this function later
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

/*
 * function to get list of files in a directory
 * (which is passed as an argument)
 */
t_file * read_dir(char *dir_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*files_list;

	files_list = NULL;
	dirp = opendir(dir_name);
	if (dirp == NULL) //TODO handle error normally
	{
		ft_putendl("error while opening");
		return NULL;
	}
	while ((dp = readdir(dirp)) != NULL)
		join_node(dp, &files_list);
	(void)closedir(dirp);
	return files_list;
}

//TODO memorise what this func was for and implement normal'no a ne kak oby4no
//void print_short(t_params *params)
//{
//	t_file *tmp;
//	int printed;
//	int skip;
//
//	printed = 0;
//	while (printed < params->count)
//	{
//	}
//}

int main()//int ac, char **av)
{
	g_params = (t_params*)ft_memalloc(sizeof(t_params));
//	ft_bzero(g_params, sizeof(t_params));
	t_subdirs * subdirs = (t_subdirs*)malloc(sizeof(t_subdirs));
	subdirs->name = ".";
	subdirs->next = NULL;
	print_recursively(subdirs);

    return (0);
}
