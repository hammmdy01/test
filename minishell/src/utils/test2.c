/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:43:41 by hazali            #+#    #+#             */
/*   Updated: 2026/02/24 23:44:00 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/utils.h"

static int count_non_empty_args(char **args)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (args[i])
    {
        if (args[i][0] != '\0')  // ✅ Compte seulement les non vides
            count++;
        i++;
    }
    return (count);
}

// Crée un nouveau tableau sans les args vides
char **remove_empty_args(char **args)
{
    char **result;
    int count;
    int i;
    int j;

    if (!args)
        return (NULL);

    count = count_non_empty_args(args);
    
    // ✅ Si tous les args sont vides, retourne NULL
    if (count == 0)
        return (NULL);

    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    while (args[i])
    {
        if (args[i][0] != '\0')  // ✅ Copie seulement les non vides
        {
            result[j] = ft_strdup(args[i]);
            if (!result[j])
            {
                while (j > 0)
                    free(result[--j]);
                free(result);
                return (NULL);
            }
            j++;
        }
        i++;
    }
    result[j] = NULL;
    return (result);
}
