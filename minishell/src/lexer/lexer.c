/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:46:53 by hazali            #+#    #+#             */
/*   Updated: 2026/02/18 11:41:26 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_lexer(char *line)
{
    t_token *token_list;
    int error;

    error = 0;
    token_list = NULL;
    while (*line)
    {
        if (error)
            return (ft_clear_all_token(&token_list), NULL);
        
        while (*line && ft_isspace(*line))
            line++;
        
        if (!*line)  
            break;
            
        if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2)
            || !ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2))
            error = (!ft_handle_separator(&line, &token_list));
        else if (*line == '<' || *line == '>' || *line == '|'
                 || *line == '(' || *line == ')')
            error = (!ft_handle_separator(&line, &token_list));
        else
            error = (!ft_append_word(&line, &token_list));
    }
    
    if (token_list && !ft_validate_syntax(token_list))
        return (ft_clear_all_token(&token_list), NULL);
    return (token_list);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_handle_separator(char **ptr_line, t_token **token_list)
{
	if (!ft_strncmp(*ptr_line, "<<", 2))
		return (ft_append_separator(T_DLESS, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, ">>", 2))
		return (ft_append_separator(T_DGREAT, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, "<", 1))
		return (ft_append_separator(T_LESS, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, ">", 1))
		return (ft_append_separator(T_GREAT, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, "(", 1))
		return (ft_append_separator(T_OPEN_PARENT, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, ")", 1))
		return (ft_append_separator(T_CLOSE_PARENT, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, "&&", 2))
		return (ft_append_separator(T_AND, ptr_line, token_list));
	else if (!ft_strncmp(*ptr_line, "||", 2))
		return (ft_append_separator(T_OR, ptr_line, token_list));
	else
		return (ft_append_separator(T_PIPE, ptr_line, token_list));
}

int	ft_append_separator(t_token_type type, char **ptr_line,
		t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_add_token(token_list, token);
	(*ptr_line)++;
	if (type == T_DGREAT || type == T_DLESS || type == T_OR || type == T_AND)
		(*ptr_line)++;
	return (1);
}

int	ft_append_word(char **ptr_line, t_token **token_list)
{
	char *tmp_line;
	char *value;
	t_token *token;
	size_t i;

	tmp_line = *ptr_line;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_WORD);
	if (!token)
		return (free(value), 0);
	*ptr_line += i;
	return (ft_add_token(token_list, token), 1);
}
void print_tokens(t_token *tokens)
{
    t_token *curr = tokens;
    static const char *type_names[] = {
        "WORD", "LESS", "GREAT", "DLESS", "DGREAT",
        "PIPE", "OPEN_PARENT", "CLOSE_PARENT", "AND", "OR"
    };
    
    printf("=== TOKENS ===\n");
    while (curr)
    {
        printf("[%s]", type_names[curr->type]);
        if (curr->value)
            printf(" '%s'", curr->value);
        printf("\n");
        curr = curr->next;
    }
    printf("==============\n");
}
