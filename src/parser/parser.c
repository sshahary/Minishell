/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:57:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/09 00:39:34 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_mini *mini)
{
	if (!lexer(mini))
	{
		free_tokens(mini->tokens);
		return (0);
	}
	
	free_tokens(mini->tokens);
	return (1);
}

