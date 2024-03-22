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

void export_variable(char **envp, const char *variable) {
    // Check if the variable has the format "key=value"
    char *equals_sign = strchr(variable, '=');
    if (equals_sign != NULL) {
        // Calculate the length of the key
        int key_length = equals_sign - variable;
        // Allocate memory for the key and value
        char *key = malloc(key_length + 1);
        char *value = strdup(equals_sign + 1); // Skip '='

        // Copy key and value
        strncpy(key, variable, key_length);
        key[key_length] = '\0';

        // Set or update the environment variable
        setenv(key, value, 1);

        // Free allocated memory
        free(key);
        free(value);
    } else {
        // Invalid format
        printf("Invalid format: %s\n", variable);
    }
}
