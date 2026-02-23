/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:26:54 by hazali            #+#    #+#             */
/*   Updated: 2026/02/23 12:38:49 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

# include "minishell.h"

typedef struct s_env t_env;

int		ft_strcmp(char *s1, char *s2);
void	free_split(char **split);
int		count_args(char **args);
// char	**env_list_to_array(t_env *env_list);
void	exec_error(char *cmd, char *msg);
void	exit_with_error(char *msg, int code);

// Debug functions for AST
void	ft_print_ast(t_node *ast);
void	ft_print_ast_compact(t_node *ast);
t_env *init_env_list(char **envp);

char *get_var_value(char *var_name, t_minishell *shell);
int is_special_char(char c);
char *extract_var_name(char *str, int *index);
char *ft_strjoin_char(char *s, char c);
char **expand_args(char **args, t_minishell *shell);



// Debug mode toggle
# define DEBUG_MODE 1

#endif