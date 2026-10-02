/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:47:57 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:47:58 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha_or(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else
		return (0);
}

int	is_valid_var(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!ft_isalpha_or(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha_or(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*extract_key(const char *arg)
{
	int		i;
	char	*key;

	if (!arg)
		return (NULL);
	if (!ft_strchr(arg, '='))
		key = ft_strdup(arg);
	else
	{
		i = 0;
		while (arg[i] && arg[i] != '=')
			i++;
		key = ft_substr(arg, 0, i);
	}
	return (key);
}

char	*extract_value(const char *arg)
{
	int		i;
	char	*value;

	if (!arg)
		return (NULL);
	if (!ft_strchr(arg, '='))
		value = NULL;
	else
	{
		i = 0;
		while (arg[i] && arg[i] != '=')
			i++;
		if (arg[i + 1] == '\0')
			value = ft_strdup("");
		else
			value = ft_substr(arg, i + 1, ft_strlen(arg) - (i + 1));
		if (!value)
			return (NULL);
	}
	return (value);
}

int	parse_env(const char *arg, char **key, char **value, bool *eq)
{
	*key = NULL;
	*value = NULL;
	*eq = false;
	if (!arg)
		return (1);
	*key = extract_key(arg);
	if (!*key)
		return (1);
	if (ft_strchr(arg, '='))
	{
		*eq = true;
		*value = extract_value(arg);
		if (*value == NULL)
		{
			free(*key);
			return (1);
		}
	}
	return (0);
}
