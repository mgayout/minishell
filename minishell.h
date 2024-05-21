/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:16:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 16:51:22 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft+/libft.h"
# include "libft+/ft_printf+/ft_printf.h"
# include "libft+/get_next_line+/get_next_line.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef enum e_errors
{
	BEGIN_PIPE = 1,
	END_PIPE,
	END_TOKEN,
	NO_EOF_DQ,
	NO_EOF_Q,
}	t_errors;

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
	QUOTE,
}	t_lex_quote;

typedef struct s_env
{
	char			*name;
	char			**value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_lstr
{
	char			*str;
	int				id;
	bool			heredoc;
	bool			space;
	struct s_lstr	*next;
}					t_lstr;

typedef struct s_lex
{
	t_lex_type		type;
	struct s_lstr	*data;
	t_lex_redir		redir;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

typedef struct s_par
{
	int				id;
	int				status;
	struct s_lstr	*cmd;
	struct s_lstr	*arg;
	int				infile_count;
	struct s_lstr	*infile;
	int				outfile_count;
	struct s_lstr	*outfile;
	bool			pipein;
	bool			pipeout;
	bool			append;
	struct s_par	*next;
	struct s_par	*prev;
}					t_par;

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

typedef struct s_data
{
	char			**envp;
	struct s_env	*env;
	char			*prompt;
	char			*last_prompt;
	struct s_lex	*lexer;
	struct s_par	*parser;
	struct s_exp	*expander;
	struct s_exe	*exec;
	int				error;
}					t_data;

//MAIN

int		is_a_prompt(char *str);
void	minishell_loop(t_data *data);

//ENV

void	env(t_data *data);
void	fill_env(t_env **env, char *envp);
void	print_env(t_env *env);
t_env	*envlast(t_env *lst);
int		envsize(t_env *lst);
void	envadd_back(t_env **lst, t_env *new);

//CHECK_ERRORS

int		check_lexer(t_lex *lexer);
int		check_parser(t_par *parser);
void	print_errors(t_errors n);

//FREE

void	free_all(t_data *data);
void	free_env(t_env **env);
void	free_lex(t_lex **lexer);
void	free_par(t_par **parser);
void	free_exp(t_exp **expander);
void	free_exe(t_exe **exec);
void	free_tab(char **tabs);
void	free_lstr(t_lstr *lst);

#endif