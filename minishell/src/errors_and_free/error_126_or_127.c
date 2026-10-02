/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_126_or_127.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:10:55 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/20 12:29:45 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_not_found(const char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": command not found\n", 20);
}

void	print_no_such_file(const char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": No such file or directory\n", 28);
}

void	print_is_directory(const char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": Is a directory\n", 17);
}

void	print_permission_denied(const char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": Permission denied\n", 20);
}
