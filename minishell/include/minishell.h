/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:36:09 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/23 12:16:25 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <termio.h>
# include <term.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <stdbool.h>
# include <limits.h>

typedef struct s_shell	t_shell;
typedef struct s_exec	t_exec;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_LT,
	T_GT,
	T_DLT,
	T_DGT,
	T_EOF,
}	t_token_type;

typedef enum e_bi
{
	T_ECHO,
	T_CD,
	T_ENV,
	T_EXIT,
	T_EXPORT,
	T_PWD,
	T_UNSET,
	T_DOT,
	T_NOT_BUILTIN,
}	t_bi;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC
}	t_redir_type;

typedef enum e_ast_type
{
	CMD_NODE,
	PIPE_NODE
}	t_ast_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	char			*raw;
	int				hdoc_quoted;
	int				hdoc_fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*raw;
	struct s_token	*next;
}					t_token;

typedef struct s_cmds
{
	char			**args;
	char			*path;
	bool			builtin;
	t_bi			type;
	t_redir			*redir;
}					t_cmds;

typedef struct s_ast
{
	t_ast_type		type;
	t_cmds			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_var
{
	char			*key;
	char			*value;
	bool			has_eq;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct s_exp
{
	char			*in;
	char			*current;
	char			**out;
	int				i;
	int				sq;
	int				dq;
	int				quote_flag;
	int				out_len;
	int				last_status;
	t_var			*env;
}					t_exp;

struct s_exec
{
	t_shell	*ms;
	t_ast	*tree;
	t_var	*env;
	pid_t	*child;
	int		index;
	int		n_cmds;
	int		pipe_i;
	int		carry_fd;
	bool	in_pipe;
	bool	parent_exec;
	int		s_stdin;
	int		s_stdout;
	int		fd_in;
	int		fd_out;
	int		last_pid;
};

struct s_shell
{
	t_ast	*tree;
	t_var	*env;
	t_exp	*exp;
	int		last_exit_code;
	bool	should_exit;
	int		exit_status;
	char	**legacy_env;
};

typedef struct s_hdoc
{
	int	p[2];
	int	saved;
	int	saw_delim;
	int	saw_eof;
}	t_hdoc;

//		BUILTS-INNS
//	CD
int				cd(char **args, t_shell *ms);
//	CMD
char			*get_full_path(t_shell *ms, t_cmds *cmd);
int				exec_builtin(t_ast *tree, t_shell *ms, int in_p);
// DOT
int				dot(char **args);
// ECHO
int				echo(char **args);
// ENV 
int				env_cmd(char **args, t_shell *ms);
// EXIT
int				exit_ms(char **args, int in_p, t_shell *ms);
int				str_is_digit(char *str);
int				get_error_code(int status);
// EXPORT
int				export(char **args, t_shell *ms);
int				export_no_args(t_shell *ms);
int				export_loop(char **args, t_shell *ms, int i);
//	UNSET
int				unset(char **args, t_shell *ms);
//	PWD
int				pwd(t_shell *ms);
//-----------------------------------------------------------------------------
//		ERRORS_AND_FREE
char			*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
const char		*which_token_error(t_token *token);
int				cleanup(t_exec *ex, int status);
int				msg_error(char *msg, char *arg, char *msg_end, int return_code);
int				get_error_code(int status);
int				free_pwd_and_msg(char *oldpwd,
					char *target, int code, char *args);
int				print_resolve_error_set_error_code(t_exec *ex,
					char *name, int error_code);
t_var			*free_node_and_return(t_var *node, char *key);
void			free_words_tail(char **words, int i, int size);
void			msg_error_exit(char *msg, int exit_c, t_shell *ms);
void			free_pipes(int **pipes_fd, int n_pipes);
void			close_all_pipes(int **pipes_fd, int n_pipes);
void			close_and_free_pipes(int **pipes_fd, int n_pipes);
void			free_cmd_list(t_cmds *list);
void			*free_redir(t_redir *redir, char *msg);
void			free_ast(t_ast *ast);
void			free_tokens(t_token *first);
void			free_var_list(t_var **first);
void			free_array(char **array);
void			free_ex(t_exp *ex);
void			free_ms(t_shell *ms, t_token *tokens);
void			free_exec(t_exec *exec);
void			print_cmd_not_found(const char *s);
void			print_no_such_file(const char *s);
void			print_is_directory(const char *s);
void			print_permission_denied(const char *s);
void			ft_puterr(const char *s);
void			if_no_path(char *name, t_shell *ms, int *error_code);
//-----------------------------------------------------------------------------
//	EXECUTION
char			*classify_direct_path(char *path, int *error_code);
char			*resolve_command_path(t_shell *ms, t_cmds *cmd,
					int *error_code);
int				exec(t_shell *ms);
int				pipe_exec(t_ast *tree, t_exec *ex);
int				cmd_exec(t_ast *tree, t_exec *ex);
int				exec_branch(t_ast *tree, t_exec *ex);
int				is_executable(char *path);
int				is_directory(char *path);
int				has_slash(char *str);
int				handle_empty_cmd(t_exec *ex, t_cmds *cmd);
int				resolve_or_report(t_exec *ex, t_cmds *cmd);
int				path_unset_or_empty(t_shell *ms);
int				save_stdio(t_exec *ex);
int				restore_stdio(t_exec *ex);
int				apply_carry_fdin(t_exec *ex);
int				run_exec_and_cleanup(t_shell *ms);
int				path_unset_or_empty(t_shell *ms);
void			set_child_signals(void);
void			close_pipe(int *p);
//-----------------------------------------------------------------------------
//	MAIN
char			**var_to_env(t_shell *ms);
int				get_line_and_history(t_shell *ms, char **out);
void			create_env(char **env, t_shell *ms);
//-----------------------------------------------------------------------------
//	TOKENS
int				is_operator(char c);
int				is_space(char c);
int				skip_spaces(const char *str, int start);
int				add_word_or_op(const char *line, int i, t_token **first);
void			add_token(t_token **first, t_token *new);
void			remove_token(t_token **first, t_token *prev, t_token *current);
t_token			*cut_in_operator_token(const char *line, int i);
t_token			*cut_in_word_tokens(const char *line, int start, int end);
t_token			*tokenize_line(const char *line);
t_token			*create_word_token(char *value);
t_token			*create_op_token(t_token_type t_type);
t_token			*create_eof_token(void);
t_token			*insert_word(t_token *current, char *value);
t_token_type	get_op_type(const char *line, int i);
//-----------------------------------------------------------------------------
//	PARSING
char			*remove_quotes_from_string(const char *str);
int				get_array_size(char **av);
int				is_valid_for_cmd(t_token *token);
int				build_ast_then_free_tokens(t_shell *ms,
					t_token **tokens, int empty_input);
void			copy_array(char **dest, char **src, int size);
t_ast			*create_ast_cmd(t_cmds *cmd);
t_ast			*create_ast_pipe(t_ast *left, t_ast *right);
t_cmds			*init_cmd(void);
t_cmds			*parse_command(t_token	**token);
//-----------------------------------------------------------------------------
//	EXPANSIONS
char			**ft_split2(const char *s, char sep1, char sep2);
char			*reset_and_keep_str(t_exp *ex);
char			*transform_dollar_value(t_exp *ex, int len, int qmark);
char			**expand_one_token(const char *str, t_shell *ms);
int				skip_exp(t_token *prev, t_token *current);
int				join_strings(t_exp *ex, const char *str);
int				push_str(t_exp *ex, char *str);
int				add_char(t_exp *ex, char c);
int				apply_words(t_token *current, char **words,
					int size, t_token **out_last);
int				handle_literal_dollar(t_exp *ex);
int				handle_dollar_sq(t_exp *ex);
int				handle_dollar_dq(t_exp *ex);
int				handle_dollar_zero(t_exp *ex);
int				handle_dollar(t_exp *ex);
int				handle_expandable_word(t_token **f,
					t_token **p, t_token **c, t_shell *ms);
int				ultimate_merger(t_exp *ex, const char *value, int dq);
int				ultimate_expand_tokens(t_token **tokens, t_shell *ms);
void			init_exp(t_exp *new, t_shell *ms, char *in);
void			skip_quote(t_exp *ex);
//-----------------------------------------------------------------------------
//	REDIRECTIONS
char			*remove_all_quotes(const char *s);
int				redirect(t_shell *ms, t_cmds *current, int *fd_in, int *fd_out);
int				redirect_choice(t_shell *ms,
					t_redir *r, int *fd_in, int *fd_out);
int				parse_redir(t_token **token, t_cmds *new);
int				assign_redir(t_token *token, t_redir *new);
int				is_redir(t_token *token);
int				has_any_quote(const char *s);
int				validate_redirect_target(const char *shown, char **target);
int				fill_redir_target(t_redir *new, t_token *tok);
int				open_file_redir(t_redir *r, int *fd_in, int *fd_out);
int				redirect_in(t_redir *redirect, int *fd_in);
int				redirect_out(t_redir *redirect, int *fd_out);
int				redirect_app(t_redir *redirect, int *fd_out);
int				do_redirects_and_dup(t_exec *ex, t_cmds *cmd);
int				dup_fds_if_needed(t_exec *ex);
void			close_fd_redirect(int *fd_in, int *fd_out);
void			add_redir_node(t_redir **first, t_redir *new_redir);
t_redir			*init_redir(void);
t_redir			*parse_one_redir(t_token **tokens);
//-----------------------------------------------------------------------------
//	HDOC
int				hdoc_read_loop(t_shell *ms, t_redir *redir, t_hdoc *doc);
int				hdoc_restore_stdin(t_hdoc *doc);
int				hdoc_open(t_hdoc *doc);
int				hdoc_stop(char *line, t_redir *redir);
int				redirect_hdoc(t_shell *ms, t_redir *redir, int *fd_in);
int				hdoc_limit(t_redir *new, const char *value);
int				prepare_all_heredocs(t_shell *ms);
int				inside_hdoc(t_shell *ms,
					char **line, t_redir *redirect, int w_fd);
void			hdoc_warn_eof(const char *wanted);
void			close_all_heredocs(t_cmds *cmd);
void			close_all_heredocs_from_ast(t_ast *tree);
//-----------------------------------------------------------------------------
//	SIGNALS
extern int				g_sig;
int				update_last_ms_exit_code(t_shell *ms);
void			handle_sigint(int sig);
void			setup_signals_heredoc(void);
void			setup_signals_interactive(void);
void			setup_signals(void);
//-----------------------------------------------------------------------------
//	CHILDS
void			wait_childs(t_exec *exec, t_shell *shell);
//-----------------------------------------------------------------------------
//	UTILITIES
char			*reset_and_keep_str(t_exp *ex);
char			**reset_and_keep_array(t_exp *ex);
char			*extract_key(const char *arg);
char			*extract_value(const char *arg);
int				ft_lstsize(t_var *lst);
int				ft_isalpha_or(int c);
int				is_valid_var(char *str);
int				env_value_update(t_var *node, const char *value);
int				env_add_back(t_shell *ms,
					const char *key, const char *value, bool eq);
int				env_insert(t_shell *ms,
					const char *key, const char *value, bool eq);
int				check_pwd(t_shell *ms);
int				parse_env(const char *arg, char **key, char **value, bool *eq);
int				handle_sq(char c, int *sq, int dq);
int				handle_dq(char c, int *dq, int sq);
int				dup_empty(t_exp *ex);
int				ft_lstsize_eq(t_var *lst);
int				consume_pipe(t_token **token);
void			norm_shlvl(t_shell *ms);
void			if_flag(void);
void			init_zero(int *a, int *b, int *c, int *d);
void			is_builtin(t_shell *ms, t_cmds *cmd);
t_var			*ft_lstlast(t_var *lst);
t_var			*env_find_key(t_var *list, const char *key);
t_var			*env_new_pair(const char *key, const char *value, bool eq);
//-----------------------------------------------------------------------------

#endif