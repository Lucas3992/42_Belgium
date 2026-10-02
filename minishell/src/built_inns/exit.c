/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcasiell <dcasiell@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 09:40:49 by lde-sutt          #+#    #+#             */
/*   Updated: 2025/10/16 14:08:09 by dcasiell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(long long nb, int d, int sign)
{
	if (sign == 1 && nb > (LLONG_MAX - d) / 10)
		return (1);
	if (sign == -1 && - nb < (LLONG_MIN + d) / 10)
		return (1);
	return (0);
}

static int	ft_atoll_safe(const char *s, long long *out)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	while (is_space(s[i]))
		i++;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (ft_isdigit(s[i]))
	{
		if (check_overflow(nb, s[i] - '0', sign))
			return (0);
		nb = nb * 10 + (s[i] - '0');
		i++;
	}
	*out = nb * sign;
	return (1);
}

int	is_llong_str(const char *s, long long *out)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	while (is_space(s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	return (ft_atoll_safe(s, out));
}

static int	exit_numeric(char **argv, int in_pipe, t_shell *ms)
{
	msg_error("exit: ", argv[1], ": numeric argument required", 2);
	ms->exit_status = 2;
	ms->should_exit = !in_pipe;
	if (in_pipe)
		exit(2);
	return (2);
}

int	exit_ms(char **argv, int in_pipe, t_shell *ms)
{
	long long	code;

	if (!in_pipe)
		ft_putstr_fd("exit\n", 2);
	if (!argv[1])
	{
		ms->should_exit = true;
		ms->exit_status = ms->last_exit_code;
		return (ms->exit_status);
	}
	if (!is_llong_str(argv[1], &code))
		return (exit_numeric(argv, in_pipe, ms));
	if (argv[2])
	{
		ft_puterr("minishell: exit: too many arguments\n");
		return (1);
	}
	ms->should_exit = true;
	ms->exit_status = (unsigned char)code;
	if (in_pipe)
		exit(ms->exit_status);
	return (ms->exit_status);
}
