/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:43:19 by mguerga           #+#    #+#             */
/*   Updated: 2022/10/30 15:06:54 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*trans(int i, long buf, int *neg);
int		parselong(long ln, int *neg);

char	*ft_itoa(int n)
{
	int		buf;
	int		neg[1];
	long	ln;

	neg[0] = 1;
	buf = (long)(n);
	ln = (long)(n);
	return (trans(parselong(ln, neg), buf, neg));
}

char	*trans(int i, long buf, int *neg)
{
	char	*ptr;

	ptr = malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	while (i > 0)
	{
		ptr[i - 1] = (((buf % 10) * neg[0]) + '0');
		buf = buf / 10;
		i--;
	}
	if (neg[0] == -1)
		ptr[0] = '-';
	return ((char *)(ptr));
}

int	parselong(long ln, int *neg)
{
	int	i;

	i = 0;
	if (ln == 0)
		return (1);
	if (ln < 0)
	{
		neg[0] = -1;
		i++;
	}
	ln *= neg[0];
	while (ln > 0)
	{
		ln = ln / 10;
		i++;
	}
	return (i);
}
