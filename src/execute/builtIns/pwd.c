/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:34:46 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 22:41:36 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int pwd(int fd) {
    char *cwd = getcwd(NULL, 0); // Allocate memory for the current working directory
    if (cwd == NULL) {
        // Handle error, if any
        return 0; // Return 0 to indicate failure
    }
    
    // Write the current working directory to the specified file descriptor
    write(fd, cwd, strlen(cwd));
    write(fd, "\n", 1);

    free(cwd); // Free the memory allocated by getcwd
    return 1; // Return 1 to indicate success
}

// int	main(void)
// {
// 	int	fd = 1;
// 	pwd(fd);
// }
