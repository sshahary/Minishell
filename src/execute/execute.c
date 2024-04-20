/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/20 03:31:27 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ctrl_c_handler(int signum) {
	printf("\nCtrl+C pressed, quitting...\n");
	exit(0);
}

 

// int execute(void)
// {
// 	t_command cmd;
// 	ft_memset(&cmd, 0, sizeof(t_mini)); // Initialize the struct with zeros

// 	if (argc < 2) {
// 		printf("Usage: %s [command]\n", argv[0]);
// 		return 1;
// 	}

// 	strncpy(cmd.command, argv[1], MAX_COMMAND_LENGTH - 1); // Copy command to the struct

// 	// Copy arguments to the struct
// 	for (int i = 2; i < argc; i++) {
// 		cmd.arguments[cmd.num_arguments++] = argv[i];
// 	}

// 	// Copy environment variables to the struct
// 	for (int i = 0; env[i] != NULL && i < 100; i++) {
// 		cmd.environment_variables[cmd.num_environment_variables++] = env[i];
// 	}

// 	signal(SIGINT, ctrl_c_handler); // Register the handler for Ctrl+C

// 	if (strncmp(cmd.command, "echo", 4) == 0) {
// 		echo(cmd.num_arguments, cmd.arguments);
// 	} else if (strncmp(cmd.command, "cd", 2) == 0) {
// 		if (cmd.num_arguments < 2) {
// 			printf("Usage: cd [directory]\n");
// 		} else {
// 			cd(cmd.arguments[0]);
// 		}
// 	} else if (strncmp(cmd.command, "pwd", 3) == 0) {
// 		pwd();
// 	} else if (strncmp(cmd.command, "unset", 5) == 0) {
// 		if (cmd.num_arguments < 2) {
// 			printf("Usage: unset [variable]\n");
// 		} else {
// 			unset(env, cmd.arguments[0]);
// 		}
// 	} else if (strncmp(cmd.command, "export", 6) == 0) {
// 		if (cmd.num_arguments < 2) {
// 			printf("Usage: export [variable=value]\n");
// 		} else {
// 			export_variable(env, cmd.arguments[0]);
// 		}
// 	} else {
// 		printf("Command not found: %s\n", cmd.command);
// 		return 1;
// 	}

// 	return 0;
// }

void	builtin(char  **cmd)
{
	t_mini	shell;
	if (ft_strncmp(cmd[0], "echo", 4))
		echo((int)cmd[0], cmd);
	else if (ft_strncmp(cmd[0], "cd", 2))
		cd(cmd[1]);
	else if (ft_strncmp(cmd[0], "env", 3))
		env(shell.env, 0);
	else if (ft_strncmp(cmd[0], "pwd", 3))
		pwd();
	else if (ft_strncmp(cmd[0], "unset", 5))
		unset(shell.env, cmd[0]);
	else if (ft_strncmp(cmd[0], "export", 6))
		export(shell.env, cmd[0]);
	else
		ft_error(*shell.env,"command not found", 127);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// void executed_command(char **cmd) {
// 	execvp(cmd[0], cmd);
// 	perror("execvp"); // This will print an error if execvp fails
// 	exit(EXIT_FAILURE);
// }


// static void multi_execute_cmd(char ***cmds, int num_cmds)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_cmds)
// 	{
// 		single_execute_cmd(cmds[i]);
// 	}
// }

// static void single_execute_cmd(char **cmd)
// {
// 	pid_t pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{ // Child process
// 		if (execvp(cmd[0], cmd) == -1)
// 		{
// 			perror("execvp");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{ // Parent process
// 		int status;
// 		if (waitpid(pid, &status, 0) == -1)
// 		{
// 			perror("waitpid");
// 			exit(EXIT_FAILURE);
// 		}
// 		// Optionally, you can check the exit status of the child process here
// 	}
// }

// void execute_command(t_mini *mini)
// {
// 	int	i;

// 	i = 0;
// 	if (!parser(mini))
// 	{
// 		free_cmds(mini);
// 		return;
// 	}
// 	while (i < (char)mini->input)
// 	{
// 		single_execute_cmd(mini->cmds);
// 		i++;
// 	}
// 	multi_excute_cmd(mini->cmds, mini->input);
// }