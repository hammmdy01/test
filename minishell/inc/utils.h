/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:26:54 by hazali            #+#    #+#             */
/*   Updated: 2026/02/20 16:40:46 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

# include "minishell.h"

int		ft_strcmp(char *s1, char *s2);
void	free_split(char **split);
int		count_args(char **args);
// char	**env_list_to_array(t_env *env_list);
void	exec_error(char *cmd, char *msg);
void	exit_with_error(char *msg, int code);

// Debug functions for AST
void	ft_print_ast(t_node *ast);
void	ft_print_ast_compact(t_node *ast);

// Debug mode toggle
# define DEBUG_MODE 1

#endif