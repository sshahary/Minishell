/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:40:11 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/01 14:40:22 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	merge_arrays_helper(char **new, char ***array1, char **array2, int *i)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	l = (*i);
	while (j < l)
	{
		new[j] = (*array1)[j];
		j++;
	}
	k = 0;
	while (array2[k])
		new[j++] = array2[k++];
	l++;
	j--;
	while ((*array1)[l])
		new[j] = (*array1)[l++];
}

void	merge_arrays(char ***array1, char **array2, int *i)
{
	char	**new_array;
	int		size1;
	int		size2;

	size1 = 0;
	size2 = 0;
	while ((*array1)[size1])
		size1++;
	while (array2[size2])
		size2++;
	new_array = malloc(sizeof(char *) * (size1 + size2));
	if (!new_array)
		return ;
	merge_arrays_helper(new_array, array1, array2, i);
	new_array[size1 + size2] = NULL;
	(*i) = (*i) + size2 - 1;
	*array1 = new_array;
}
