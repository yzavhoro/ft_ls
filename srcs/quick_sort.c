//
// Created by Yevheniia ZAVHORODNIA on 12/10/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "../inc/ft_ls.h"

void swap(t_file ** array, int idx_a, int idx_b)
{
	t_file* tmp;

	tmp = array[idx_a];
	array[idx_a] = array[idx_b];
	array[idx_b] = tmp;
}

int partition(t_file **array, int start, int end, int (*sorted)(t_file*, t_file*)) {
	t_file *pivot;
	int i;
	int j;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (!(sorted(array[j], pivot)))
		{
			i++;
			swap(array, i, j);
		}
		j++;
	}
	swap(array, i + 1, end);
	return (i + 1);
}

void quick_sort(t_file **array, int start, int end, int (*f)(t_file*, t_file*))
{
	int pi; //partitioning index

	if (start < end)
	{
		pi = partition(array, start, end, f);
		quick_sort(array, start, pi - 1, f);
		quick_sort(array, pi + 1, end, f);
	}
}