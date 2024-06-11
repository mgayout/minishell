/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/11 18:14:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include "../libft+/libft.h"
# include "../libft+/ft_printf+/ft_printf.h"
# include "../libft+/get_next_line+/get_next_line.h"

typedef struct s_global
{
	int				error;
	int				heredoc;
}					t_global;

extern t_global		g_global;

typedef struct s_exe
{
	int				pipefd[2];
	int				std_in;
	int				std_out;
	int				*pid;
	int				nb_cmd;
	int				status;
	bool			temp;
	struct s_pid	*child;
}					t_exe;

typedef struct s_pid
{
	struct s_exp	*lst;
	char			*arg1;
	char			**arg2;
	int				infile;
	int				outfile;
}					t_pid;

typedef struct s_exp
{
	int				id;
	char			*cmd;
	int				builtin;
	char			*arg;
	char			*infile;
	char			*outfile;
	bool			pipein;
	bool			pipeout;
	bool			heredoc;
	bool			append;
	struct s_exp	*next;
	struct s_exp	*prev;
}					t_exp;

typedef struct s_par
{
	int				id;
	int				status;
	struct s_lstr	*cmd;
	struct s_lstr	*arg;
	int				infile_count;
	struct s_lstr	*infile_lst;
	struct s_lstr	*heredoc_lst;
	struct s_lstr	*last_infile;
	int				outfile_count;
	struct s_lstr	*outfile_lst;
	struct s_lstr	*append_lst;
	struct s_lstr	*last_outfile;
	bool			pipein;
	bool			pipeout;
	bool			heredoc;
	bool			append;
	struct s_par	*next;
	struct s_par	*prev;
}					t_par;

typedef enum e_lex_type
{
	REDIR = 1,
	STRING,
	PIPE,
}	t_lex_type;

typedef enum e_lex_redir
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
}	t_lex_redir;

typedef enum e_lex_quote
{
	NO_QUOTE = 1,
	SQUOTE,
	DQUOTE,
}	t_lex_quote;

typedef struct s_lstr
{
	char			*str;
	int				id;
	bool			space;
	t_lex_quote		quote;
	struct s_lstr	*next;
	struct s_lstr	*prev;
}					t_lstr;

typedef struct s_lex
{
	t_lex_type		type;
	struct s_lstr	*data;
	t_lex_redir		redir;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_data
{
	char			**envp;
	struct s_env	*env;
	struct s_env	*export;
	char			*prompt;
	char			*last_prompt;
	struct s_lex	*lexer;
	struct s_par	*parser;
	struct s_exp	*expander;
	struct s_exe	*exec;
}				t_data;

//MAIN
void	print_error(char *error_msg, int error_code);
int		minishell_loop(t_data *data);
void	init_data(t_data *data);
int		init_prompt(t_data *data);
//ENV
t_env	*init_env(char **envp);
void	fill_env(t_env **env, char *envp);
t_env	*init_export(t_env *env, char **envp);
void	fill_export(t_env **export, char *target);
//EXPORT
int		export_missing(t_env *env, t_env *export);
void	find_export_target(t_env **export, char **envp);
int		is_before(t_env **export, char *target, char *envp);
int		is_in_export(t_env **export, char *target);
//ENV_FUNCTION
t_env	*envlast(t_env *lst);
int		envsize(t_env *lst);
void	envadd_back(t_env **lst, t_env *new);
//SIGNALS
void	sigint_handler(int signum);
void	sigint_handler_heredoc(int signum);
void	setup_signal_handlers(bool heredoc);
void	handle_signal(t_data *data, char *prompt);
//LEXER
int		lexer(t_data *data);
int		add_new_t_lex(t_data *data, t_lex **lexer, int i, bool space);
int		check_quote(t_data *data);
//LEX_TYPE
int		token_type(t_lex *lexer, char *prompt);
int		string_type(t_data *data, int i, t_lex *lexer, bool space);
//LEX_QUOTE
int		data_noquote(t_lex *lexer, char *prompt, bool space);
int		data_squote(t_lex *lexer,
			char *prompt, bool space);
int		data_dquote(t_lex *lexer,
			char *prompt, bool space);
//LEX_UTILS
int		count_quotes(char *prompt);
//LEX_FUNCTION
t_lex	*new_lex(void);
t_lex	*lexlast(t_lex *lst);
int		lexsize(t_lex *lst);
void	lexadd_back(t_lex **lst, t_lex *new);
//LSTR_FUNCTION
t_lstr	*new_lstr(void);
t_lstr	*lstrlast(t_lstr *lst);
int		lstrsize(t_lstr *lst);
void	lstradd_back(t_lstr **lst, t_lstr *new);
char	*lstrjoin(t_lstr *lst);
//CHECK_LEXER
int		check_lexer(t_data *data, t_lex *lexer);
int		error_type(t_data *data, int n);
//PARSER
int		parser(t_data *data);
t_lex	*init_parser(t_data *data, t_lex *lexer);
int		parser_type(t_data *data, t_par *new, t_lex *lexer);
//PARSER_INIT
void	first_elem(t_data *data, t_par *new, t_lex *lexer);
void	infile_parser(t_par *parser, t_lex *lexer);
void	outfile_parser(t_par *parser, t_lex *lexer);
void	cmd_arg_parser(t_par *parser, t_lex *lexer);
//PARSER_FUNCTION
t_par	*new_par(void);
int		parsize(t_par *parser);
t_par	*parlast(t_par *lst);
void	paradd_back(t_par **lst, t_par *new);
//CHECK_PARSER
int		check_parser(t_data *data, t_par *parser);
void	check_heredoc(t_par *parser);
int		check_infile(t_data *data, t_par *parser);
int		print_check_infile(char *file);
int		check_outfile(t_data *data, t_par *parser, t_lex_redir n);
int		create_outfile(t_lstr *last, char *file, t_lex_redir n);
int		check_last_infile(t_data *data, t_par *parser);
int		check_last_outfile(t_data *data, t_par *parser);
void	wrong_heredoc(char *stop);
void	handle_signal_heredoc(char *prompt);
//EXPANDER
void	expander(t_data *data);
void	init_expander(t_data *data, t_exp **expander, t_par *parser);
//EXPANDER_INIT
char	*dollar_exp(t_data *data, t_lstr *lst);
//EXPANDER_ENV
char	*modify_lstr(t_data *data, char *str);
char	*modify_str(char *new, char *str, int i);
char	*search_var(t_data *data, char *str, int i);
char	*strjoinjoin(char *begin, char *new, char *end, char *str);
//EXPANDER_UTILS
int		count_dollar(char *str);
char	**copy_tab(char **old);
int		is_a_builtin(char *cmd);
//EXPANDER_FUNCTION
t_exp	*new_exp(void);
t_exp	*explast(t_exp *lst);
int		expsize(t_exp *lst);
void	expadd_back(t_exp **lst, t_exp *new);
//EXEC
void	exec(t_data *data);
void	exec_cmd_file(t_data *data);
void	exec_pipeline(t_data *data);
//EXEC_INIT
t_exe	*init_exe(t_exp *expander);
t_pid	init_child(t_data *data);
//EXEC_FILE_CMD
void	open_file_cmd(t_data *data, t_pid child);
int		infile_cmd(t_data *data, t_pid child);
int		outfile_cmd(t_data *data, t_pid child);
//EXEC_FILE_PIPELINE
void	open_file_pipeline(t_data *data, t_pid child);
void	infile_pipeline(t_data *data, t_pid child);
void	outfile_pipeline(t_data *data, t_pid child);
//EXEC_UTILS
int		init_heredoc(t_data *data, char *stop);
//EXEC_CMD
void	children(t_data *data, t_pid child);
char	*create_arg1(t_data *data, char *str);
t_env	*search_path(t_data *data);
char	**create_arg2(t_pid child);
//BUILTINS
void	exec_builtins(t_data *data, t_pid child);
//ECHO
void	echo_builtin(t_data *data, t_pid child);
int		echo_arg(t_exp *lst);
int		is_an_option(char *arg);
char	*echo_new_arg(char	*old_arg);
//CD
void	cd_builtin(t_data *data, t_pid child);
int		is_a_directory(char *str);
//PWD
void	pwd_builtin(t_data *data, t_pid child);
int		pwd_error(char *arg);
//EXPORT
void	export_builtin(t_data *data, t_pid child);
void	init_new_export(t_data *data, char *arg);
void	init_new_env(t_data *data, char *arg);
void	find_pos_export(t_data *data, t_env *new);
void	add_new_export(t_env *pos, t_env *new);
//EXPORT_UTILS
void	check_export_arg(t_data *data, char **args);
int		check_name_arg(char **arg);
void	print_export(t_data *data);
//UNSET
void	unset_builtin(t_data *data, t_pid child);
void	search_pos(t_data *data, char *arg);
void	remove_var(t_data *data, t_env *tmp, int n);
void	remove_all(t_data *data, t_env *tmp, int n);
void	remove_first(t_data *data, t_env *tmp, int n);
void	remove_last(t_env *tmp);
//ENV
void	env_builtin(t_data *data, t_pid child);
//EXIT
void	exit_builtin(t_data *data, t_pid child);
void	print_exit(t_data *data, char *arg, int status);
//FREE
void	free_all(t_data *data, int status);
void	free_env(t_env *env);
void	free_lex(t_lex **lexer);
void	free_lstr(t_lstr **lstr);
void	free_par(t_par **parser);
void	free_exp(t_exp **expander);
void	free_exe(t_exe **exec);
void	free_tab(char **tabs);

#endif