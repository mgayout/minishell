/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:55:30 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/03 14:20:15 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

//PARSER

int		parser(t_data *data);
int		init_parser(t_par **parser, t_lex *lexer);
int		parser_type(t_par *new, t_lex *lexer);
void	print_par(t_data *data);

//PARSER_INIT

void	first_elem(t_par *new, t_lex *lexer);
void	infile_parser(t_par *parser, t_lex *lexer);
void	outfile_parser(t_par *parser, t_lex *lexer);
void	cmd_arg_parser(t_par *parser, t_lex *lexer);

//PARSER_FUNCTION

t_par	*new_par(void);
int		parsize(t_par *parser);
t_par	*parlast(t_par *lst);
void	paradd_back(t_par **lst, t_par *new);

#endif