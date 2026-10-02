/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:43:29 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 10:59:13 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_cmd_node(t_token **token)
{
	t_ast	*leaf;
	t_cmds	*cmd;

	if (!token || !*token)
		return (NULL);
	cmd = parse_command(token);
	if (!cmd)
		return (NULL);
	leaf = create_ast_cmd(cmd);
	if (!leaf)
		return (free_cmd_list(cmd), NULL);
	return (leaf);
}

t_ast	*connect_node_to_left_and_right(t_ast *left, t_ast *right)
{
	t_ast	*pipe_node;

	if (!left || !right)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipe_node = create_ast_pipe(left, right);
	if (!pipe_node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	return (pipe_node);
}

t_ast	*consume_check_connect(t_token **token, t_ast *tree)
{
	t_ast	*new_root;
	t_ast	*right_leaf;

	if (!consume_pipe(token))
		return (free_ast(tree), NULL);
	if (!*token || !is_valid_for_cmd(*token))
	{
		msg_error((char *)which_token_error(*token), NULL, NULL, 0);
		return (free_ast(tree), NULL);
	}
	right_leaf = parse_cmd_node(token);
	if (!right_leaf)
		return (free_ast(tree), NULL);
	new_root = connect_node_to_left_and_right(tree, right_leaf);
	if (!new_root)
		return (NULL);
	return (new_root);
}

static t_ast	*create_ast_tree(t_token **token)
{
	t_ast	*tree;

	if (!token || !*token || (*token)->type == T_EOF)
		return (NULL);
	if (!is_valid_for_cmd(*token))
	{
		msg_error((char *)which_token_error(*token), NULL, NULL, 0);
		return (NULL);
	}
	tree = parse_cmd_node(token);
	if (!tree)
		return (NULL);
	while (*token && (*token)->type == T_PIPE)
	{
		tree = consume_check_connect(token, tree);
		if (!tree)
			return (NULL);
	}
	if (!*token || (*token)->type != T_EOF)
		return (free_ast(tree), NULL);
	return (tree);
}

int	build_ast_then_free_tokens(t_shell *ms, t_token **tokens, int empty_input)
{
	t_token	*head;

	head = NULL;
	if (tokens && *tokens)
		head = *tokens;
	ms->tree = create_ast_tree(tokens);
	if (!ms->tree)
	{
		if (head)
			free_tokens(head);
		if (tokens)
			*tokens = NULL;
		if (empty_input == 0)
			ms->last_exit_code = 2;
		return (0);
	}
	if (head)
		free_tokens(head);
	if (tokens)
		*tokens = NULL;
	return (1);
}
