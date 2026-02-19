/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:26:54 by hazali            #+#    #+#             */
/*   Updated: 2026/02/19 01:24:23 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

int	ft_strcmp(char *s1, char *s2);


// Debug functions for AST
void	ft_print_ast(t_node *ast);
void	ft_print_ast_compact(t_node *ast);

// Debug mode toggle
# define DEBUG_MODE 1

#endif