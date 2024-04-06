/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:38:43 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ctrl_c_handler(int signum) {
    printf("\nCtrl+C pressed, quitting...\n");
    exit(0);
}

int main(int argc, char *argv[], char **env) {
    Command cmd;
    memset(&cmd, 0, sizeof(Command)); // Initialize the struct with zeros

    if (argc < 2) {
        printf("Usage: %s [command]\n", argv[0]);
        return 1;
    }

    strncpy(cmd.command, argv[1], MAX_COMMAND_LENGTH - 1); // Copy command to the struct

    // Copy arguments to the struct
    for (int i = 2; i < argc; i++) {
        cmd.arguments[cmd.num_arguments++] = argv[i];
    }

    // Copy environment variables to the struct
    for (int i = 0; env[i] != NULL && i < 100; i++) {
        cmd.environment_variables[cmd.num_environment_variables++] = env[i];
    }

    signal(SIGINT, ctrl_c_handler); // Register the handler for Ctrl+C

    if (strncmp(cmd.command, "echo", 4) == 0) {
        echo(cmd.num_arguments, cmd.arguments);
    } else if (strncmp(cmd.command, "cd", 2) == 0) {
        if (cmd.num_arguments < 2) {
            printf("Usage: cd [directory]\n");
        } else {
            cd(cmd.arguments[0]);
        }
    } else if (strncmp(cmd.command, "pwd", 3) == 0) {
        pwd();
    } else if (strncmp(cmd.command, "unset", 5) == 0) {
        if (cmd.num_arguments < 2) {
            printf("Usage: unset [variable]\n");
        } else {
            unset(env, cmd.arguments[0]);
        }
    } else if (strncmp(cmd.command, "export", 6) == 0) {
        if (cmd.num_arguments < 2) {
            printf("Usage: export [variable=value]\n");
        } else {
            export_variable(env, cmd.arguments[0]);
        }
    } else {
        printf("Command not found: %s\n", cmd.command);
        return 1;
    }

    return 0;
}
