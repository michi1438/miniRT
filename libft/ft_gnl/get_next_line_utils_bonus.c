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
