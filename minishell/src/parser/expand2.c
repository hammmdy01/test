/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:31:46 by hazali            #+#    #+#             */
/*   Updated: 2026/02/25 04:42:36 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_variables(char *input, t_minishell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		i;
	int		single_quote;
	int		double_quote;

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
			continue ;
		}
		if (input[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			i++;
			continue ;
		}
		if (input[i] == '$' && !single_quote)
		{
			var_name = extract_var_name(input, &i);
			if (var_name[0] != '\0') // ✅ Variable non vide
			{
				var_value = get_var_value(var_name, shell);
				tmp = result;
				result = ft_strjoin(result, var_value);
				free(tmp);
				free(var_value);
			}
			else // ✅ var_name vide = $ seul
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
