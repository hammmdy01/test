/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:03:10 by hammm             #+#    #+#             */
/*   Updated: 2026/02/12 11:28:35 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(t_token_type type)
{
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (1);
	return (0);
}
int	ft_is_redirection(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT || type == T_DLESS
		|| type == T_DGREAT)
		return (1);
	return (0);
}

static void	ft_print_syntax_error(char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token_str)
		ft_putstr_fd(token_str, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

static char	*ft_get_token_str(t_token_type type)
{
	if (type == T_PIPE)
		return ("|");
	else if (type == T_AND)
		return ("&&");
	else if (type == T_OR)
		return ("||");
	else if (type == T_LESS)
		return ("<");
	else if (type == T_GREAT)
		return (">");
	else if (type == T_DLESS)
		return ("<<");
	else if (type == T_DGREAT)
		return (">>");
	else if (type == T_OPEN_PARENT)
		return ("(");
	else if (type == T_CLOSE_PARENT)
		return (")");
	return ("unknown");
}

static int	ft_check_first_token(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (ft_is_operator(tokens->type))
	{
		ft_print_syntax_error(ft_get_token_str(tokens->type));
		return (0);
	}
	if (tokens->type == T_CLOSE_PARENT)
	{
		ft_print_syntax_error(")");
		return (0);
	}
	return (1);
}

static int	ft_check_last_token(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (1);
	curr = tokens;
	while (curr->next)
		curr = curr->next;
	if (ft_is_operator(curr->type) || ft_is_redirection(curr->type))
	{
		ft_print_syntax_error(NULL);
		return (0);
	}
	return (1);
}

static int	ft_check_consecutive_tokens(t_token *curr)
{
	if (ft_is_operator(curr->type) && ft_is_operator(curr->next->type))
	{
		ft_print_syntax_error(ft_get_token_str(curr->next->type));
		return (0);
	}
	if (ft_is_operator(curr->type) && ft_is_redirection(curr->next->type))
	{
		ft_print_syntax_error(ft_get_token_str(curr->next->type));
		return (0);
	}
	if (ft_is_redirection(curr->type))
	{
		if (curr->next->type != T_WORD)
		{
			ft_print_syntax_error(ft_get_token_str(curr->next->type));
			return (0);
		}
	}
	return (1);
}

static int	ft_check_parentheses(t_token *tokens)
{
	t_token	*curr;
	int		open_count;

	open_count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == T_OPEN_PARENT)
		{
			open_count++;
			if (!curr->next || curr->next->type == T_CLOSE_PARENT)
			{
				ft_print_syntax_error(")");
				return (0);
			}
			if (curr->next && ft_is_operator(curr->next->type))
			{
				ft_print_syntax_error(ft_get_token_str(curr->next->type));
				return (0);
			}
		}
		else if (curr->type == T_CLOSE_PARENT)
		{
			open_count--;
			if (open_count < 0)
			{
				ft_print_syntax_error(")");
				return (0);
			}
		}
		curr = curr->next;
	}
	if (open_count != 0)
	{
		ft_print_syntax_error("(");
		return (0);
	}
	return (1);
}

int	ft_validate_syntax(t_token *tokens)
{
	t_token	*curr;

	if (!ft_check_first_token(tokens))
		return (0);
	if (!ft_check_last_token(tokens))
		return (0);
	if (!ft_check_parentheses(tokens))
		return (0);
	curr = tokens;
	while (curr && curr->next)
	{
		if (!ft_check_consecutive_tokens(curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}
