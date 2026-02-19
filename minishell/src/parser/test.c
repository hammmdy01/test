/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:46:40 by hazali            #+#    #+#             */
/*   Updated: 2026/02/19 15:59:47 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*ft_parsing(t_token *list_token)
{
	t_token	*curren_list;
	t_node	*ast;

	curren_list = list_token;
	if (!curren_list)
		return (NULL);
	ast = ft_parse_expression(&curren_list, 0);
	if (!ast || curren_list)
	{
		ft_clear_ast(&ast);
		return (NULL);
	}
	return (ast);
}

t_node	*ft_parse_expression(t_token **list_token, int precedence)
{
	t_node			*left;
	t_node			*right;
	int				curr_precedence;
	t_token_type	type_operator;

	if (!*list_token)
		return (NULL);
	left = ft_parse_primary(list_token);
	if (!left)
		return (NULL);
	while (*list_token && ft_is_operator((*list_token)->type)
		&& (ft_get_precedence((*list_token)->type)) >= precedence)
	{
		type_operator = (*list_token)->type;
		curr_precedence = ft_get_precedence(type_operator);
		ft_next_token(list_token);
		right = ft_parse_expression(list_token, curr_precedence + 1);
		if (!right)
			return (ft_clear_ast(&left), NULL);
		left = ft_create_node(ft_token_to_node_type(type_operator), left,
				right);
		if (!left)
			return (ft_clear_ast(&right), ft_clear_ast(&left), NULL);
	}
	return (left);
}
t_node	*ft_parse_parentheses(t_token **list_token)
{
	t_node	*node;

	ft_next_token(list_token);
	node = ft_parse_expression(list_token, 0);
	if (!node || (*list_token) || (*list_token)->type != T_CLOSE_PARENT)
	{
		ft_putendl_fd("minishell: Syntax error: expected ')'", STDERR_FILENO);
		ft_clear_ast(&node);
		return (NULL);
	}
	ft_next_token(list_token);
	return (node);
}

t_node	*ft_parse_primary(t_token **list_token)
{
	if (!*list_token)
	{
		ft_putendl_fd("minishell: Syntax error: unexpected end of input",
			STDERR_FILENO);
		return (NULL);
	}
	if ((*list_token)->type == T_OPEN_PARENT)
	{
		return (ft_parse_parentheses(list_token));
	}
	else if ((*list_token)->type == T_WORD
		|| ft_is_redirection((*list_token)->type))
	{
		return (ft_parse_command(list_token));
	}
	return (ft_putendl_fd("minishell: Syntax error: unexpected token",
			STDERR_FILENO), NULL);
}

t_node	*ft_parse_command(t_token **list_token)
{
	t_node	*node;

	node = ft_create_cmd_node();
	if (!node)
		return (NULL);
	while (*list_token && ((*list_token)->type == T_WORD
			|| ft_is_redirection((*list_token)->type)))
	{
		if (!ft_parse_word_redir(node, list_token))
		{
			ft_clear_ast(&node);
			return (NULL);
		}
		if (*list_token && ((*list_token)->type == T_WORD || ft_is_redirection((*list_token)->type)))
			continue ;
		break ;
	}
	return (node);
}

int	ft_parse_word_redir(t_node *node, t_token **list_token)
{
	if (ft_is_redirection((*list_token)->type))
	{
		if (!ft_parse_io_redir(node, list_token))
			return (0);
	}
	else
	{
		if (!ft_parse_args(node, list_token))
			return (0);
	}
	return (1);
}

int	ft_count_args(t_token *list_token)
{
	int	count;

	count = 0;
	while (list_token && list_token->type == T_WORD)
	{
		count++;
		list_token = list_token->next;
	}
	return (count);
}

int	ft_parse_args(t_node *node, t_token **list_token)
{
	int	arg_count;
	int	i;

	arg_count = ft_count_args(*list_token);
	if (arg_count == 0)
		return (1);
	node->expand_args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!node->expand_args)
		return (0);
	i = 0;
	while (*list_token && (*list_token)->type == T_WORD)
	{
		node->expand_args[i] = ft_strdup((*list_token)->value);
		if (!node->expand_args[i])
		{
			while (i > 0)
				free(node->expand_args[--i]);
			free(node->expand_args);
			return (0);
		}
		i++;
		ft_next_token(list_token);
	}
	node->expand_args[i] = NULL;
	return (1);
}

// int	ft_parse_io_redir(t_node *node, t_token **list_token) V0
// {
// 	t_io_node	*io_node;

// 	io_node = ft_create_io_node(ft_token_to_io_type((*list_token)->type),
// 			(*list_token)->value);
// 	if (!io_node)
// 		return (0);
// 	ft_add_io_node(&node->io_list, io_node);
// 	ft_next_token(list_token);
// 	if (!*list_token || (*list_token)->type != T_WORD)
// 	{
// 		ft_putendl_fd("minishell: Syntax error: expected filename after redirection",
// 			STDERR_FILENO);
// 		return (0);
// 	}
// 	return (1);
// }

int	ft_parse_io_redir(t_node *node, t_token **list_token)
{
	t_token_type redir_type;
	t_io_node *tmp;
	int fd;
	
	while (*list_token && ft_is_redirection((*list_token)->type))
	{
		redir_type = (*list_token)->type;
		fd = (*list_token)->fd;
		ft_next_token(list_token);
		if (!list_token)
			return(0);
		if ((*list_token)->type != T_WORD)
			return (0);
		tmp = ft_create_io_node(ft_token_to_io_type(redir_type), (*list_token)->value, fd);
		if (!tmp)
			return (0);
		ft_add_io_node(&node->io_list, tmp);
		ft_next_token(list_token);		
	}
	return (1);
}

t_node	*ft_create_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->io_list = NULL;
	node->args = NULL;
	node->expand_args = NULL;
	return (node);
}

t_io_node	*ft_create_io_node(t_io_type type, char *value, int fd)
{
	t_io_node	*io_node;

	io_node = (t_io_node *)malloc(sizeof(t_io_node));
	if (!io_node)
		return (NULL);
	io_node->type = type;
    io_node->value = ft_strdup(value);
	io_node->fd = fd;
	if (!io_node->value)
	{
		free(io_node);
		return (NULL);
	}
	io_node->next = NULL; // pas oblige a mon avis
	return (io_node);
}

void	ft_next_token(t_token **list_token)
{
	if (*list_token)
		*list_token = (*list_token)->next;
}

int	ft_get_precedence(t_token_type type)
{
	if (type == T_PIPE)
		return (1);
	else if (type == T_AND || type == T_OR)
		return (2);
	return (0);
}

void	ft_syntax_error(t_token_type type)
{
	ft_putstr_fd("minishell: Syntax error near unexpected token `",
		STDERR_FILENO);
	if (type == T_EOF)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(ft_get_token_str(type), STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

t_node_type	ft_token_to_node_type(t_token_type type)
{
	if (type == T_PIPE)
		return (N_PIPE);
	else if (type == T_AND)
		return (N_AND);
	else if (type == T_OR)
		return (N_OR);
	else if (type == T_LESS)
		return (N_REDIR_IN);
	else if (type == T_GREAT)
		return (N_REDIR_OUT);
	else if (type == T_DLESS)
		return (N_HEREDOC);
	else if (type == T_DGREAT)
		return (N_APPEND);
	return (N_CMD);
}

t_io_type	ft_token_to_io_type(t_token_type type)
{
	if (type == T_LESS)
		return (IO_IN);
	else if (type == T_GREAT)
		return (IO_OUT);
	else if (type == T_DLESS)
		return (IO_HEREDOC);
	else if (type == T_DGREAT)
		return (IO_APPEND);
	return (IO_OUT);
}

t_node	*ft_create_cmd_node(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = N_CMD;
	node->left = NULL;
	node->right = NULL;
	node->io_list = NULL;
	node->args = NULL;
	node->expand_args = NULL;
	return (node);
}

void	ft_add_io_node(t_io_node **io_list, t_io_node *new_io)
{
	t_io_node	*current;

	if (!*io_list)
	{
		*io_list = new_io;
		return ;
	}
	current = *io_list;
	while (current->next)
		current = current->next;
	current->next = new_io;
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_io_list(t_io_node *io_list)
{
	t_io_node	*current;
	t_io_node	*temp;

	current = io_list;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
	}
}

void	ft_clear_ast(t_node **ast)
{
	if (!*ast)
		return ;
	ft_clear_ast(&(*ast)->left);
	ft_clear_ast(&(*ast)->right);
	if ((*ast)->expand_args)
		free_args((*ast)->expand_args);
	if ((*ast)->io_list)
		free_io_list((*ast)->io_list);
	free(*ast);
	*ast = NULL;
}