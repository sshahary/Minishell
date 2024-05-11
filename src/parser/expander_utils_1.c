/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:02:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/11 15:34:29 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	merge_helper(char **new, char ***array1, char **array2, int *i);

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0' && j < n)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*get_env(const char *name, char **env)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			return (&(env[i][name_len + 1]));
		}
		i++;
	}
	return (NULL);
}

void	print_cmds(t_mini *mini)
{
	int		i;
	t_cmds	*temp;

	temp = mini->cmds;
	while (temp)
	{
		i = 0;
		printf("Command:\t FD_IN: %d  FD_OUT: %d\n", \
		temp->fd_in, temp->fd_out);
		while (temp->args && temp->args[i])
		{
			printf("\tArg%d: <%s>\n", i, temp->args[i]);
			i++;
		}
		temp = temp->next;
	}
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
	merge_helper(new_array, array1, array2, i);
	*array1 = new_array;
}

static void	merge_helper(char **new, char ***array1, char **array2, int *i)
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
	{
		new[j] = array2[k];
		j++;
		k++;
	}
	l++;
	while ((*array1)[l])
	{
		new[j] = (*array1)[l++];
		j++;
	}
	new[j] = NULL;
}
