/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:17:40 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 22:17:40 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	int	args_count(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	echo(t_cmds *cmds, t_mini *mini)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (args_count(cmds->args) > 1)
	{
		while (cmds->args[i] && ft_strncmp(cmds->args[i], "-n", 2) == 0)
		{
			newline = 1;
			i++;
		}
		while (cmds->args[i])
		{
			printf("%s", cmds->args[i]);
			if (cmds->args[i + 1] && cmds->args[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (newline == 0)
		printf("\n");
	mini->exit_code = 0;
}
