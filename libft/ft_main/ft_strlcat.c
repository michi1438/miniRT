/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:14:45 by mguerga           #+#    #+#             */
/*   Updated: 2022/10/30 10:54:21 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ind;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	ind = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size == 0)
		return (src_len);
	while (dst[i] != '\0')
		i++;
	while (src[ind] != '\0' && i < (size - 1))
		dst[i++] = src[ind++];
	dst[i] = '\0';
	if (dst_len > size)
		return (src_len + size);
	return (src_len + dst_len);
}
