/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_hdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:47:36 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/21 12:47:37 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*in_loop(char **words, char *out, int i)
{
	char	*tmp;

	tmp = ft_strjoin(out, " ");
	free(out);
	if (!tmp)
		return (free_array(words), NULL);
	out = tmp;
	tmp = ft_strjoin(out, words[i]);
	free(out);
	if (!tmp)
		return (free_array(words), NULL);
	out = tmp;
	return (out);
}

static char	*exp_token(const char *line, t_shell *ms)
{
	char	**words;
	char	*out;
	int		i;

	out = NULL;
	i = 0;
	words = expand_one_token(line, ms);
	if (!words)
		return (NULL);
	while (words[i])
	{
		if (!out)
			out = ft_strdup(words[i]);
		else
			out = in_loop(words, out, i);
		i++;
	}
	if (!out)
		out = ft_strdup("");
	free_array(words);
	return (out);
}

int	inside_hdoc(t_shell *ms, char **line, t_redir *redirect, int w_fd)
{
	char	*text;

	if (redirect->hdoc_quoted == 0)
		text = exp_token(*line, ms);
	else
		text = ft_strdup(*line);
	free(*line);
	*line = NULL;
	if (text == NULL)
		return (1);
	if (write(w_fd, text, ft_strlen(text)) < 0)
	{
		free(text);
		return (1);
	}
	write(w_fd, "\n", 1);
	free(text);
	return (0);
}

int	hdoc_stop(char *line, t_redir *redir)
{
	if (ft_strcmp(line, redir->target) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}
