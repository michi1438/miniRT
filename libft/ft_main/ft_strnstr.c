/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:26:17 by mguerga           #+#    #+#             */
/*   Updated: 2022/10/28 16:31:53 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	buf;

	i = 0;
	j = 0;
	buf = 0;
	if (little[0] == '\0')
		return ((char *)(big));
	while (i < len && big[i] != '\0')
	{
		while (little[j] == big[i] && i < len)
		{
			i++;
			j++;
			buf++;
			if (little[j] == '\0')
				return ((char *)(&(big[i - j])));
		}	
		j = 0;
		i -= (buf - 1);
		buf = 0;
	}
	return (NULL);
}
