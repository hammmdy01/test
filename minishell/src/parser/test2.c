/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:46:44 by hazali            #+#    #+#             */
/*   Updated: 2026/02/24 23:44:40 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

char	*get_var_value(char *var_name, t_minishell *shell)
{
	t_env	*tmp;
	char	*exit;

	if (ft_strcmp(var_name, "?") == 0)
	{
		exit = ft_itoa(shell->exit_s);
		return (exit);
	}
	tmp = shell->envlst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var_name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '"' || c == '\''
		|| c == '$' || c == '\0');
}

// char *extract_var_name(char *str, int *index)
// {
//     int start;
//     int len;
//     char *var_name;

//     (*index)++; // Skip the '$'
//     if(str[*index] == '?')
//     {
//         (*index)++;
//         return (ft_strdup("?"));
//     }
//     start = *index;
//     while (str[*index] && !is_special_char(str[*index]))
//         (*index)++;
//     len = *index - start;
//     if (len == 0)
//         return (ft_strdup("?"));
//     var_name = ft_substr(str, start, len);
//     return (var_name);
// }
char	*extract_var_name(char *str, int *index)
{
	int		start;
	int		len;
	char	*var_name;

	(*index)++; // Skip the '$'
	if (str[*index] == '?')
	{
		(*index)++;
		return (ft_strdup("?"));
	}
	start = *index;
	while (str[*index] && !is_special_char(str[*index]))
		(*index)++;
	len = *index - start;
	if (len == 0)
		return (ft_strdup("")); // ✅ Chaîne vide = $ seul
	var_name = ft_substr(str, start, len);
	return (var_name);
}

// char	*expand_variables(char *input, t_minishell *shell)
// {
// 	char	*result;
// 	char	*var_name;
// 	char	*var_value;
// 	char	*tmp;
// 	int		i;
// 	int		single_quote;
// 	int		double_quote;

// 	if (!input)
// 		return (NULL);
// 	result = ft_strdup("");
// 	i = 0;
// 	single_quote = 0;
// 	double_quote = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' && !double_quote)
// 		{
// 			single_quote = !single_quote;
// 			i++;
// 			continue ;
// 		}
// 		if (input[i] == '"' && !single_quote)
// 		{
// 			double_quote = !double_quote;
// 			i++;
// 			continue ;
// 		}
// 		if (input[i] == '$' && !single_quote)
// 		{
// 			var_name = extract_var_name(input, &i);
// 			if (ft_strcmp(var_name, "$") != 0) // Pas un $ seul
// 			{
// 				var_value = get_var_value(var_name, shell);
// 				tmp = result;
// 				result = ft_strjoin(result, var_value);
// 				free(tmp);
// 				free(var_value);
// 			}
// 			else
// 			{
// 				tmp = result;
// 				result = ft_strjoin(result, "$");
// 				free(tmp);
// 			}
// 			free(var_name);
// 		}
// 		else
// 		{
// 			// Caractère normal
// 			tmp = result;
// 			result = ft_strjoin_char(result, input[i]);
// 			free(tmp);
// 			i++;
// 		}
// 	}
// 	return (result);
// }

char *expand_variables(char *input, t_minishell *shell)
{
    char *result;
    char *var_name;
    char *var_value;
    char *tmp;
    int i;
    int single_quote;
    int double_quote;

    if (!input)
        return (NULL);
    result = ft_strdup("");
    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (input[i])
    {
        if (input[i] == '\'' && !double_quote)
        {
            single_quote = !single_quote;
            i++;
            continue;
        }
        if (input[i] == '\"' && !single_quote)
        {
            double_quote = !double_quote;
            i++;
            continue;
        }
        if (input[i] == '$' && !single_quote)
        {
            var_name = extract_var_name(input, &i);
            if (var_name[0] != '\0')  // ✅ Variable non vide
            {
                var_value = get_var_value(var_name, shell);
                tmp = result;
                result = ft_strjoin(result, var_value);
                free(tmp);
                free(var_value);
            }
            else  // ✅ var_name vide = $ seul
            {
                tmp = result;
                result = ft_strjoin(result, "$");
                free(tmp);
            }
            free(var_name);
        }
        else
        {
            // Caractère normal
            tmp = result;
            result = ft_strjoin_char(result, input[i]);
            free(tmp);
            i++;
        }
    }
    return (result);
}


// char	**expand_args(char **args, t_minishell *shell)
// {
// 	char	**expanded_args;
// 	int		i;

// 	if (!args)
// 		return (NULL);
// 	expanded_args = malloc(sizeof(char *) * (count_args(args) + 1));
// 	if (!expanded_args)
// 		return (NULL);
// 	i = 0;
// 	while (args[i])
// 	{
// 		expanded_args[i] = expand_variables(args[i], shell);
// 		i++;
// 	}
// 	expanded_args[i] = NULL;
// 	return (expanded_args);
// }

char **expand_args(char **args, t_minishell *shell)
{
    char **expanded_args;
    char **clean_args;
    int i;

    if (!args)
        return (NULL);
    
    // 1️⃣ Expand chaque arg
    expanded_args = malloc(sizeof(char *) * (count_args(args) + 1));
    if (!expanded_args)
        return (NULL);
    
    i = 0;
    while (args[i])
    {
        expanded_args[i] = expand_variables(args[i], shell);
        if (!expanded_args[i])
        {
            while (i > 0)
                free(expanded_args[--i]);
            free(expanded_args);
            return (NULL);
        }
        i++;
    }
    expanded_args[i] = NULL;
    
    // 2️⃣ ✅ NOUVEAU : Supprimer les args vides
    clean_args = remove_empty_args(expanded_args);
    
    // 3️⃣ Free les expanded_args (avant nettoyage)
    i = 0;
    while (expanded_args[i])
        free(expanded_args[i++]);
    free(expanded_args);
    
    return (clean_args);  // ✅ Peut être NULL si tout est vide
}

char	*ft_strjoin_char(char *s, char c)
{
	char *result;
	int len;
	int i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}