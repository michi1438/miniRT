/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:05:04 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/20 10:05:37 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*freeandreplace(char *oldstr, char *stradd, int ind)
{
	char	*nptr;

	if (ind >= 0)
	{
		nptr = ft_strjoin("", &stradd[ind + 1]);
		if (oldstr != NULL)
		{
			free(oldstr);
			oldstr = NULL;
		}
		return (nptr);
	}
	else
	{
		nptr = ft_strjoin(oldstr, stradd);
		free (oldstr);
		return (nptr);
	}
}

int	readforterm(char *buf, int toggle)
{
	int	i;

	i = 0;
	if (toggle == 1)
	{
		while (buf[i] != '\0')
		{
			if (buf[i] == '\n')
				return (i);
			i++;
		}
		return (-1);
	}
	else
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (buf[i] == '\n' || buf[i] == '\0')
				return (i);
			i++;
		}
		return (-1);
	}
}

int	gnl_realloc(t_bufobj *bufobj, ssize_t new_len)
{
	ssize_t	i;
	char	*ptr;
	char	*dest;

	dest = malloc(new_len);
	if (dest == NULL)
	{
		if (bufobj->buf_allocated)
			free(bufobj->buf);
		return (0);
	}
	i = 0;
	ptr = bufobj->buf;
	while (i < bufobj->buf_size)
	{
		*(dest + i) = *(ptr + i);
		i ++;
	}
	if (bufobj->buf_allocated)
		free(bufobj->buf);
	bufobj->buf = dest;
	bufobj->buf_allocated = 1;
	return (1);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*ptr;
	const char		*ptr2;

	if (dest == 0 && src == 0)
	{
		return (dest);
	}
	i = 0;
	ptr = dest;
	ptr2 = src;
	while (i < n)
	{
		*(ptr + i) = *(ptr2 + i);
		i ++;
	}
	return (dest);
}
