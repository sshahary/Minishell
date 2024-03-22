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

void unset(char **envp, const char *name) {
    int i;
    int envp_len = 0;

    // Calculate the length of envp
    while (envp[envp_len] != NULL) {
        envp_len++;
    }

    // Search for the variable name and remove it
    for (i = 0; i < envp_len; i++) {
        if (strncmp(envp[i], name, strlen(name)) == 0 && envp[i][strlen(name)] == '=') {
            // Move subsequent environment variables to fill the gap
            while (envp[i] != NULL) {
                envp[i] = envp[i + 1];
                i++;
            }
            // Null-terminate the last element to mark the end of the array
            envp[i - 1] = NULL;
            return;
        }
    }
}
