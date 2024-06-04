/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 16:20:05 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../minishell.h"

//EXPANDER

int		expander(t_data *data);
int		init_expander(t_data *data, t_exp **expander, t_par *parser);

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
void	print_exp(t_data *data);

//EXPANDER_FUNCTION

t_exp	*new_exp(void);
t_exp	*explast(t_exp *lst);
int		expsize(t_exp *lst);
void	expadd_back(t_exp **lst, t_exp *new);

#endif