/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ef_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:41:38 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/13 09:41:39 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes_fd, int n_pipes)
{
	int	i;

	if (!pipes_fd)
		return ;
	i = 0;
	while (i < n_pipes)
	{
		if (pipes_fd[i])
			free(pipes_fd[i]);
		i++;
	}
	free(pipes_fd);
}

void	close_all_pipes(int **pipes_fd, int n_pipes)
{
	int	i;

	if (!pipes_fd)
		return ;
	i = 0;
	while (i < n_pipes)
	{
		if (pipes_fd[i])
		{
			close(pipes_fd[i][0]);
			close(pipes_fd[i][1]);
		}
		i++;
	}
}

void	close_and_free_pipes(int **pipes_fd, int n_pipes)
{
	close_all_pipes(pipes_fd, n_pipes);
	free_pipes(pipes_fd, n_pipes);
}
