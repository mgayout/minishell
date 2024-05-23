/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:44 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 14:40:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*modify_expander(t_data *data, char *str)
{
	int	i;

	while (count_dollar(str))
	{
		i = 0;
		while (str[i] != '$')
			i++;
		if (str[i + 1] == '$')
			str = strjoinjoin(ft_substr(str, 0, i), NULL, ft_substr(str, i + 2, ft_strlen(str) - (i + 2)));
		else if (str[i + 1] == '?')
			str = modify_str(ft_itoa(data->error), str, i);	
		else if (!ft_strchr(" \n\0\"'", str[i + 1]))
			str = modify_str(search_var(data, str, i + 1), str, i);
		else
			return(str);
	}
	return(str);
}

char	*modify_str(char *new, char *str, int i)
{
	char	*begin;
	char	*end;
	int		j;
	
	begin = ft_substr(str, 0, i);
	j = i + 1;
	while (str[j] && !ft_strchr("'\"\n$ ", str[j]))
		j++;
	end = ft_substr(str, j, ft_strlen(str) - j);
	return (strjoinjoin(begin, new, end));
}

char	*search_var(t_data *data, char *str, int i)
{
	t_env	*env;
	char	*new;
	char	*var;
	int		j;
	int		k;
	
	j = i;
	while (str[j] && !ft_strchr("'\"\n$ ", str[j]))
		j++;
	var = ft_substr(str, i, j - i);
	env = data->env;
	while (env && ft_strncmp(var, env->name, ft_strlen(env->name) + 1) != 0)
		env = env->next;
	k = 0;
	new = NULL;
	while (env->value[k])
	{
		if (!new)
			new = ft_strdup(env->value[k]);
		else
			new = ft_strjoin(ft_strjoin(new, ":"), env->value[k]);
		k++;
	}
	return (new);
}

char	*strjoinjoin(char *begin, char *new, char *end)
{
	if (begin && new && end)
		return (ft_strjoin(ft_strjoin(begin, new), end));
	else if (!begin && new && end)
		return (ft_strjoin(new, end));
	else if (begin && !new && end)
		return (ft_strjoin(begin, end));
	else if (begin && new && !end)
		return (ft_strjoin(begin, new));
	else if (begin && !new && !end)
		return (begin);
	else if (!begin && new && !end)
		return (new);
	else if (!begin && !new && end)
		return (end);
	else
		return (NULL);
}
