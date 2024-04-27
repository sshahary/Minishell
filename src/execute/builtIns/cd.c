/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:17:07 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 22:47:51 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// static int	cdhome(char *path, char **cmds, char **env)
static int	cdhome(char *path, t_mini *mini)
{

	if (mini->cmds->args[1][1] == '~')
	{
		ft_execute_err_2("cd", mini->cmds->args[1], "No such file or directory");
		mini->exit_code = 1;
	}
	path = find_command_path("HOME", mini->env);
	if (chdir(path) == -1)
		ft_execute_err_1("cd", "HOME not set");
	return (1);
}
// static int			cdenv(char *path, char **cmds, char **env)
static int			cdenv(char *path, t_mini *mini)
{
	path = find_command_path(&(mini->cmds->args[1][1]), mini->env);
	if (chdir(path) == -1)
		chdir(find_command_path("HOME", mini->env));
	return (1);
}

// static void		setoldpwd(char **env)
static void		setoldpwd(t_mini *mini)
{
	char	*cur;
	char	*old;
	char	*tmp;

	tmp = malloc(sizeof(char) * MAX_PATH_LENGTH);
	cur = ft_strjoin("PWD=", getcwd(tmp, MAX_PATH_LENGTH));
	old = ft_strjoin("OLDPWD=", find_command_path("PWD", mini->env));
	checkexport(cur, &mini->env);
	checkexport(old, &mini->env);
	free(cur);
	// free(old);			//check for free later
}
// void	cd(char **args, char **env)
void	cd(t_mini *mini)
{
	char	*path;
	int		res;

	path = 0;
	res = 0;
	printf("jdhudgudf0");
	if (mini->cmds->args[1] != NULL && mini->cmds->args[1][0] != '~' && mini->cmds->args[1][0] != '$')
	{
		path = mini->cmds->args[1];
		if (chdir(path) == -1)
			res = ft_execute_err_2("cd", path, strerror(errno));
		setoldpwd(mini);
	}
	else if (mini->cmds->args[1] == NULL || mini->cmds->args[1][0] == '~')
		cdhome(path, mini);
	else if (mini->cmds->args[1][0] == '$')
		cdenv(path, mini);
	if (res == -1)
		mini->exit_code = 1;
	else
		mini->exit_code = 0;
}

//tests

// int main()
// {
// 	t_mini *mini = malloc(sizeof(t_mini));
// 	if (mini == NULL) {
// 		// Handle allocation failure
// 		return 1;
// 	}

// 	// Set up mock environment variables (replace with real values if needed)
// 	mini->env[0] = "HOME=/Users/sshahary";
// 	mini->env[1] = "PWD=/Users/sshahary/Projects/mshell/src/execute/builtins";
// 	mini->env[2] = NULL;  // Null-terminated environment

// 	// Test cases (add more as needed)
// 	printf("** Test 1: Change directory to an existing path **\n");
// 	mini->cmds = malloc(sizeof(t_cmds));
// 	if (mini->cmds == NULL) {
// 		// Handle allocation failure
// 		free(mini);
// 		return 1;
// 	}

// 	mini->cmds->args = malloc(sizeof(char*) * 3);
// 	if (mini->cmds->args == NULL) {
// 		// Handle allocation failure
// 		free(mini->cmds);
// 		free(mini);
// 		return 1;
// 	}

// 	mini->cmds->args[0] = strdup("cd");
// 	mini->cmds->args[1] = strdup("../handlers/");
// 	mini->cmds->args[2] = NULL;  // Null-terminated argument list

// 	cd(mini);  // Assuming cd is defined somewhere

// 	printf("Exit code: %d\n", mini->exit_code);

// 	// Free allocated memory
// 	free(mini->cmds->args[1]);
// 	free(mini->cmds->args);
// 	free(mini->cmds);
// 	free(mini);

// 	return 0;
// }
