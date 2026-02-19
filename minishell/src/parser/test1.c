/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazali <hazali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:44:32 by hammm             #+#    #+#             */
/*   Updated: 2026/02/19 15:54:56 by hazali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_node_type_str(t_node_type type)
{
	if (type == N_CMD)
		return ("CMD");
	else if (type == N_PIPE)
		return ("PIPE");
	else if (type == N_AND)
		return ("AND");
	else if (type == N_OR)
		return ("OR");
	else if (type == N_REDIR_IN)
		return ("REDIR_IN");
	else if (type == N_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == N_HEREDOC)
		return ("HEREDOC");
	else if (type == N_APPEND)
		return ("APPEND");
	return ("UNKNOWN");
}

static char	*get_io_type_str(t_io_type type)
{
	if (type == IO_IN)
		return ("<");
	else if (type == IO_OUT)
		return (">");
	else if (type == IO_HEREDOC)
		return ("<<");
	else if (type == IO_APPEND)
		return (">>");
	return ("?");
}

static void	print_io_list(t_io_node *io_list, int indent)
{
	t_io_node	*current;
	int			i;

	current = io_list;
	while (current)
	{
		i = 0;
		while (i++ < indent)
			printf("  ");
		printf("  📄 IO: ");
		
		// Afficher le fd si ce n'est pas le fd par défaut
		if (current->fd != 0 && current->fd != 1)
			printf("%d", current->fd);
		
		printf("%s %s\n", get_io_type_str(current->type), current->value);
		current = current->next;
	}
}

static void	print_command_args(char **args, int indent)
{
	int	i;
	int	j;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (j++ < indent)
			printf("  ");
		printf("  💬 Arg[%d]: \"%s\"\n", i, args[i]);
		i++;
	}
}

static void	print_ast_recursive(t_node *node, int depth, char *prefix)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i++ < depth)
		printf("  ");
	printf("%s", prefix);
	printf("🌳 [%s]\n", get_node_type_str(node->type));
	
	if (node->type == N_CMD)
	{
		if (node->expand_args)
			print_command_args(node->expand_args, depth);
		if (node->io_list)
			print_io_list(node->io_list, depth);
	}
	
	if (node->left)
	{
		i = 0;
		while (i++ < depth)
			printf("  ");
		printf("  ⬅️  LEFT:\n");
		print_ast_recursive(node->left, depth + 1, "");
	}
	
	if (node->right)
	{
		i = 0;
		while (i++ < depth)
			printf("  ");
		printf("  ➡️  RIGHT:\n");
		print_ast_recursive(node->right, depth + 1, "");
	}
}

void	ft_print_ast(t_node *ast)
{
	printf("\n");
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║              📊 AST DEBUG - TREE STRUCTURE                ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
	printf("\n");
	
	if (!ast)
	{
		printf("  ⚠️  AST is NULL (empty or error in parsing)\n\n");
		return ;
	}
	
	print_ast_recursive(ast, 0, "");
	
	printf("\n");
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                     ✅ END OF AST                         ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
	printf("\n");
}

void	ft_print_ast_compact(t_node *ast)
{
	if (!ast)
	{
		printf("AST: (null)\n");
		return ;
	}
	printf("AST: ");
	if (ast->type == N_CMD)
		printf("CMD(%s)", ast->args ? ast->args : "");
	else if (ast->type == N_PIPE)
		printf("PIPE");
	else if (ast->type == N_AND)
		printf("AND");
	else if (ast->type == N_OR)
		printf("OR");
	else
		printf("%s", get_node_type_str(ast->type));
	printf("\n");
}

