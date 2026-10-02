/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-sutt <lde-sutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:24:39 by dcasiell          #+#    #+#             */
/*   Updated: 2025/10/13 09:36:56 by lde-sutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb && size && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero (array, nmemb * size);
	return (array);
}
