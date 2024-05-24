/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:55:30 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 15:37:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

//PARSER

void	parser(t_data *data);
int		init_parser(t_par *parser, t_lex *lexer);
int		last_parser(t_par *parser);
void	print_par(t_data *data);

//PARSER_INIT

void	first_string(t_par *parser, t_lex *lexer);
void	infile_parser(t_par *parser, t_lex *lexer);
void	outfile_parser(t_par *parser, t_lex *lexer);
void	cmd_arg_parser(t_par *parser, t_lex *lexer);

//PARSER_FUNCTION

t_par	*new_par(void);
int		parsize(t_par *parser);

#endif