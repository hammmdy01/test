/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:46:49 by hazali            #+#    #+#             */
/*   Updated: 2026/02/19 15:31:30 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_fd_redirection(char **line, t_token **list)
{
	int		fd;
	int		i;
	char	*start;
	t_token	*token;

	i = 0;
	start = *line;
	while (ft_isdigit((*line)[i]))
		i++;
	fd = ft_atoi(start);
	*line += i;
	if (!ft_strncmp(*line, ">>", 2))
		token = ft_new_token(NULL, T_DGREAT);
	else if (!ft_strncmp(*line, "<<", 2))
		token = ft_new_token(NULL, T_DLESS);
	else if (**line == '>')
		token = ft_new_token(NULL, T_GREAT);
	else if (**line == '<')
		token = ft_new_token(NULL, T_LESS);
	else
		return (0);
	if (!token)
		return (0);
	token->fd = fd;
	ft_add_token(list, token);
	if (!ft_strncmp(*line, ">>", 2) || !ft_strncmp(*line, "<<", 2))
		*line += 2;
	else
		(*line)++;
	return (1);
}

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->fd = -1; // pas sur sur
	return (new_token);
}

void	ft_add_token(t_token **lst, t_token *new_token)
{
	t_token	*current;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	current = *lst;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = new_token;
	new_token->prev = current;
}

void	ft_clear_all_token(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	if (!current)
		return ;
	while (current)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t' || *s == '<'
		|| *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}