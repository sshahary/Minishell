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

int	pwd()
{
	char	*pwd;
	int		ret;
	t_mini	*mini;

	ret = EXIT_SUCCESS;
	pwd = getcwd(0, MAX_PATH_LENGTH);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	mini->exit_code = 0;
}

// int	main(void)
// {
// 	int	fd = 1;
// 	pwd(fd);
// }
