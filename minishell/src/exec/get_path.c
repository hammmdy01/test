/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:04 by hazali            #+#    #+#             */
/*   Updated: 2026/02/20 16:52:18 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_paths_env(char **envp)
{
	int		i;
	char	*path_value;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			return (ft_split(path_value, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char **paths;
	char *full_path;
	int i;

    i = -1;
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
    paths = get_paths_env(envp);
    if (!paths)
        return (NULL);
    while (paths[++i])
    {
        full_path = build_full_path(paths[i], cmd);
        if (full_path && access(full_path, X_OK) == 0)
            return (free_split(paths),full_path);
        free(full_path);
    }
    free_split(paths);
    return (NULL);
}
