/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hammm <hammm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 05:24:06 by hazali            #+#    #+#             */
/*   Updated: 2026/02/19 01:24:48 by hammm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int			g_signum;

// static void	ft_handler_signum(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		// g_signum = signum;
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		rl_replace_line("", STDIN_FILENO);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }
// int	main(int ac, char **av, char **env)
// {
// 	// int				s;
// 	(void)env;
// 	(void)av;
// 	(void)ac;
// 	// t_minishell minishell;
// 	// t_token *token = NULL;
// 	// while (1)
// 	// {
// 	// 	signal(SIGINT, &ft_handler_signum);
// 	// 	signal(SIGQUIT, SIG_IGN);
// 	// 	minishell.line = readline("MINISHELL > ");
// 	// 	if (!minishell.line)
// 	// 		break ;
// 	// 	token = ft_lexer(minishell.line);
// 	// 	// if(token)
// 	// 	// {
// 	// 	// 	printf("%s", token->value);
// 	// 	// 	break;
// 	// 	// }
// 	// }
// 	// if (isatty(STDIN_FILENO))
// 	// 	write(2, "exit\n", 6);
// 	// return (0);
// 	while (1)
// 	{
// 		printf("MINISHELL > ");
// 	}
	
// }
// int main(void)
// {
//     char *line;
//     t_token *tokens;
//     // t_node  ast;
//     printf("=== MINISHELL LEXER TESTS ===\n\n");
    
//     while (1)
//     {
//         // Utiliser readline pour avoir l'historique et l'édition
//         line = readline("minishell> ");
        
//         // Ctrl+D (EOF)
//         if (!line)
//         {
//             printf("exit\n");
//             break;
//         }
        
//         // Ligne vide
//         if (!*line)
//         {
//             free(line);
//             continue;
//         }
        
//         // Ajouter à l'historique
//         add_history(line);
        
//         // Tokeniser
//         tokens = ft_lexer(line);
        
//         // ast = ft_parsing(tokens);
//         if (!tokens)
//         {
//             printf("❌ Syntax error detected\n");
//         }
//         else
//         {
//             print_tokens(tokens);
//             ft_clear_all_token(&tokens);
//         }
//         free(line);
//     }
    
//     // Nettoyer l'historique
//     rl_clear_history();
    
//     return (0);
// }

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_node	*ast;

	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║        🐚 MINISHELL - DEBUG MODE (LEXER + PARSER)        ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf("\n💡 Tips:\n");
	printf("  - Type 'exit' to quit\n");
	printf("  - Type 'clear' to clear screen\n");
	printf("  - Empty line = ignored\n\n");
	
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		
		// === LEXER ===
		printf("\n┌─── 📋 LEXER OUTPUT ───────────────────────────────────────\n");
		tokens = ft_lexer(line);
		if (!tokens)
		{
			printf("│ ❌ Syntax error detected in lexer\n");
			printf("└───────────────────────────────────────────────────────────\n\n");
			free(line);
			continue ;
		}
		print_tokens(tokens);
		printf("└───────────────────────────────────────────────────────────\n");
		
		// === PARSER ===
		printf("\n┌─── 🌳 PARSER OUTPUT ──────────────────────────────────────\n");
		ast = ft_parsing(tokens);
		if (!ast)
		{
			printf("│ ❌ Parsing failed\n");
			printf("└───────────────────────────────────────────────────────────\n\n");
			ft_clear_all_token(&tokens);
			free(line);
			continue ;
		}
		printf("│ ✅ Parsing successful!\n");
		printf("└───────────────────────────────────────────────────────────\n");
		
		// === AST DEBUG ===
		ft_print_ast(ast);
		
		// Cleanup
		ft_clear_all_token(&tokens);
		// TODO: add ft_clear_ast(ast) when you implement it
		free(line);
	}
	rl_clear_history();
	return (0);
}