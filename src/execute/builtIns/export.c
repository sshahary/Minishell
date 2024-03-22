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

void	export_variable(char **envp, const char *variable)
{
	int		key_length;
	char	*key;
	char	*equals_sign;
	char	*value;
	// Check if the variable has the format "key=value"
	
	equals_sign = ft_strchr(variable, '=');
	if (equals_sign != NULL)
	{
		// Calculate the length of the key
		key_length = equals_sign - variable;
		// Allocate memory for the key and value
		key = malloc(key_length + 1);
		value = ft_strdup(equals_sign + 1); // Skip '='
		// Copy key and value
		ft_strlcpy(key, variable, key_length);
		key[key_length] = '\0';
		// Set or update the environment variable
		setenv(key, value, 1);
		// Free allocated memory
		free(key);
		free(value);
	}
	else
		printf("Invalid format: %s\n", variable);
	// Invalid format
}
