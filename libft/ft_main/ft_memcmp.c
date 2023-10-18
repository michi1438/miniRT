/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:56:22 by mguerga           #+#    #+#             */
/*   Updated: 2022/10/27 13:16:27 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)(s1))[i] != ((unsigned char *)(s2))[i])
			return (((unsigned char *)(s1))[i] - ((unsigned char *)(s2))[i]);
		i++;
	}
	return (0);
}
