/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:50:20 by hazali            #+#    #+#             */
/*   Updated: 2026/02/18 13:26:33 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}					t_io_type;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_AND,
	N_OR,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_HEREDOC,
	N_APPEND
}					t_node_type;

typedef struct s_io_node
{
    t_io_type type;
    char    *value;
    struct s_io_node *next;
}   t_io_node;

typedef struct s_node
{
	t_node_type		type;
	t_io_node		*io_list;
	char			*args;
	char			**expand_args;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


t_node *ft_parsing(t_token *list_token);
t_node *ft_parse_expression(t_token **list_token, int precedence);
t_node *ft_parse_primary(t_token **list_token);
t_node *ft_parse_command(t_token **list_token);


#endif