/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:47:56 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 22:50:41 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void	printexport(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDIN_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	addexport(char *path, char **new, int i)
{
	new[i] = ft_strdup(path);
	new[i + 1] = NULL;
}

int	checkexport(char *path, char ***env)
{
	int		i;
	char	**new;

	if (path[0] == '=' || path[0] == '\0' || ft_strlen(path) == 1)
		return (-1);
	i = -1;
	while ((*env)[++i] != NULL)
		if (!ft_strncmp((*env)[i], path, ft_strlen(path)))
		{
			(*env)[i] = ft_strdup(path);
			return (1);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (-1);
	i = -1;
	while ((*env)[++i])
		new[i] = ft_strdup((*env)[i]);
	addexport(path, new, i);
	*env = new;
	return (1);
}

int		isvalidnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

void	export(char **cmds, t_mini *mini)
{
	int		i;
	int		res;
	char 	**tmp;

	res = 0;
	i = 0;
	tmp = cmds;
	if (mini->preflag == 1)
		return;
	if (ft_dstrlen(cmds) == 1)
		printexport(mini->env);
	else
	{
		remove_char(cmds[1], '\'');
		while (cmds[++i])
		{
			if (isvalidnum(ft_strtok(tmp[i], '=')) == 0)
			{
				ft_iderr("export", tmp[i]);
				mini->exit_code = 1;
			}
			remove_char(cmds[i], '$');
			res = checkexport(cmds[i], &(mini->env));
		}
	}
	if (res != 1)
		mini->exit_code = 1;
}

// int main(int ac, char **args, char **env) {

//    (void)ac;
//    (void)args;
//    	 // Initialize your t_mini struct
//     t_mini mini;
//     mini.preflag = 0; // Example value, set your preferred flag value here
//     mini.env = env;
//     mini.exit_code = 0; // Initialize exit code

//     // Example command line arguments
//     char *cmds[] = {
//         "export",
//         "VAR=value",
//         NULL
//     };

//     // Call the export function
//     export(cmds, &mini);

//     // Print updated environment
//     printf("Updated Environment:\n");
//     printexport(mini.env);

//     return 0;
// }