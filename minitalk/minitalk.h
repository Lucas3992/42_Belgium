/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:46:40 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/07/03 11:00:54 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct s_state
{
	unsigned char	octet;
	int				index;
}					t_state;

void	error(void);

int		ft_isdigit(int c);
int		ft_atoi(const char *str);

void	*ft_memset(void	*s, int c, size_t	n);

#endif