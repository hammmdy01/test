/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:50:20 by hazali            #+#    #+#             */
/*   Updated: 2026/02/17 10:22:34 by hazali           ###   ########.fr       */
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
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}					t_node_type;

typedef struct s_io_node
{
    t_io_type type;
    char    *value;
    char    **expand_value;
    int     HD;
    struct s_io_node *prev;
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


t_node ft_parsing(t_token *list_token);


#endif