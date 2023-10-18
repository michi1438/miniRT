/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:33:37 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/02 11:13:43 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*ndest;
	char	*nsrc;

	ndest = dst;
	nsrc = (char *)src;
	i = 0;
	if (dst > src && *nsrc != '\0')
	{
		while (len > 0)
		{
			ndest[len - 1] = nsrc[len - 1];
			len--;
		}
	}
	else if (src > dst)
	{
		while (i < len)
		{
			ndest[i] = nsrc[i];
			i++;
		}
	}
	return (dst);
}
