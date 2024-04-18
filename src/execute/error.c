/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:26:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/18 13:01:30 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error(char *str, int status)
{
	t_mini error;
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	error.exit_code = status;
	exit(EXIT_FAILURE);
	return (0);
}
