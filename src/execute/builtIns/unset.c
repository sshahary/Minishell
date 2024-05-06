/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:31:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:31:45 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	isvalidenv(char *name)
{
	int	i;

	i = 0;
	if (name[0] >= '0' && name[0] <= '9')
		return (0);
	while (name[i])
	{

		if (ft_isalnum(name[i]) || name[i] == '_')
			;
		else
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int		checkequal(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && env[i] && (str[i] == env[i]) && (env[i] != '='))
		i++;
	if ((str[i] == '\0') && (env[i] == '='))
		return (1);
	return (0);
}

int		envunset(char *str, char ***env)
{
	int	i;
	int	j;

	j = 0;
	while (((*env)[j]) != NULL)
		j++;
	if (j < 1)
		return (-1);
	i = -1;
	while ((*env)[++i] != NULL)
	{
		if (checkequal(str, (*env)[i]))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup((*env)[j - 1]);
			free((*env)[j - 1]);
			(*env)[j - 1] = NULL;
			return (1);
		}
	}
	return (1);
}


void	unset(t_mini *mini, t_cmds *cmds)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (cmds->args[i])
	{
		remove_char(cmds->args[i], '\'');
		res = isvalidenv(cmds->args[i]) && envunset(cmds->args[i], &(mini->env));
		i++;
	}
	if (res != 1)
		mini->exit_code = 1;
}

// int main() {
// 	// Create a sample environment
// 	char *env[] = {"VAR1=value1", "VAR2=value2", "VAR3=value3", NULL};
	
// 	// Create a sample t_mini struct
// 	t_mini mini;
// 	mini.preflag = 0;
// 	mini.exit_code = 0;
// 	mini.env = env;

// 	// Create a sample command
// 	t_cmds cmd;
// 	char *args[] = {"VAR1", "VAR2", NULL}; // Pass environment variables to unset
// 	cmd.args = args;
// 	mini.cmds = &cmd;

// 	// Call unset function
// 	unset(&mini);

// 	// Print the updated environment
// 	printf("Updated Environment:\n");
// 	for (int i = 0; env[i] != NULL; i++) {
// 		printf("%s\n", env[i]);
// 	}

// 	return 0;
// }