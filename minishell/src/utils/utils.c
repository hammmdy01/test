/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:25:47 by hazali            #+#    #+#             */
/*   Updated: 2026/02/22 14:48:27 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/utils.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**env_array;
	t_env	*current;
	int		count;
	int		i;
	char	*tmp;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		env_array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	exec_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	exit_with_error(char *msg, int code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(code);
}

t_env *init_env_list(char **envp)
{
    t_env   *env_list;
    t_env   *new_node;
    char    *equal;
    int     i;

    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            new_node = malloc(sizeof(t_env));
            if (!new_node)
                return (NULL);
            new_node->key = ft_substr(envp[i], 0, equal - envp[i]);
            new_node->value = ft_strdup(equal + 1);
            new_node->next = NULL;
            
            // Ajouter à la fin de la liste
            if (!env_list)
                env_list = new_node;
            else
            {
                t_env *tmp = env_list;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new_node;
            }
        }
        i++;
    }
    return (env_list);
}