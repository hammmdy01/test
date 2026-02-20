/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:47:01 by hazali            #+#    #+#             */
/*   Updated: 2026/02/20 12:41:10 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute(t_node *ast, t_minishell *shell)
{
	if (!ast)
		return (0);
	if (ast->type == N_PIPE)
		return (exec_pipe(ast, shell));
	else if (ast->type == N_CMD)
		return (exec_simple_cmd(ast, shell));
	else if (ast->type == N_AND || ast->type == N_OR)
		return (exec_and_or(ast, shell));
	return (0);
}