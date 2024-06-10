/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:44 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 16:31:31 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*modify_lstr(t_data *data, char *str)
{
	char	*new;
	int		i;

	new = ft_strdup(str);
	while (count_dollar(new))
	{
		i = 0;
		while (new[i] != '$')
			i++;
		if (new[i + 1] == '$')
			new = strjoinjoin(ft_substr(new, 0, i), NULL,
					ft_substr(new, i + 2, ft_strlen(new) - (i + 2)), new);
		else if (new[i + 1] == '?')
			new = strjoinjoin(ft_substr(new, 0, i), ft_itoa(g_global.error),
					ft_substr(new, i + 2, ft_strlen(new) - (i + 2)), new);
		else if (!ft_strchr(" \n\0\"'", new[i + 1]))
			new = modify_str(search_var(data, new, i + 1), new, i);
		else
			return (new);
	}
	return (new);
}

char	*modify_str(char *new, char *str, int i)
{
	char	*begin;
	char	*end;
	int		j;

	if (i == 0)
		begin = NULL;
	else
		begin = ft_substr(str, 0, i);
	j = i + 1;
	while (str[j] && !ft_strchr("'\"\n$ ", str[j]))
		j++;
	if (j == (int)ft_strlen(str))
		end = NULL;
	else
		end = ft_substr(str, j, ft_strlen(str) - j);
	return (strjoinjoin(begin, new, end, str));
}

char	*search_var(t_data *data, char *str, int i)
{
	t_env	*env;
	char	*new;
	char	*var;
	int		j;

	j = i;
	while (str[j] && !ft_strchr("'\"\n$ ", str[j]))
		j++;
	var = ft_substr(str, i, j - i);
	env = data->env;
	while (env && ft_strncmp(var, env->name, ft_strlen(env->name) + 1) != 0)
		env = env->next;
	new = NULL;
	if (env)
		new = ft_strdup(env->value);
	free(var);
	return (new);
}

char	*strjoinjoin(char *begin, char *new, char *end, char *str)
{
	free(str);
	if (begin && new && end)
		return (ft_strjoin_free(ft_strjoin_free(begin, new, 3), end, 3));
	else if (!begin && new && end)
		return (ft_strjoin_free(new, end, 3));
	else if (begin && !new && end)
		return (ft_strjoin_free(begin, end, 3));
	else if (begin && new && !end)
		return (ft_strjoin_free(begin, new, 3));
	else if (begin && !new && !end)
		return (begin);
	else if (!begin && new && !end)
		return (new);
	else if (!begin && !new && end)
		return (end);
	else
		return (NULL);
}
