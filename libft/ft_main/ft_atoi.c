/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:07:52 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/03 14:24:01 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc(int i, const char *nptr);
int	trimatoi(const char *nptr, int *neg);

int	ft_atoi(const char *nptr)
{
	int	neg[2];
	int	i;

	neg[0] = 1;
	if (nptr[0] == '0' && nptr[1] == '\0')
		return (0);
	if (!(ft_isdigit(nptr[0])))
	{
		i = trimatoi(nptr, neg);
		if (i == 0)
			return (0);
	}
	else
		i = 0;
	while (ft_isdigit(nptr[i]))
		i++;
	i--;
	return (calc(i, nptr) * neg[0]);
}	

int	calc(int i, const char *nptr)
{
	int	mult;
	int	res;

	res = 0;
	mult = 1;
	while (i >= 0 && ft_isdigit(nptr[i]))
	{
		res += (nptr[i] - 48) * mult;
		mult *= 10;
		i--;
	}
	return (res);
}

int	trimatoi(const char *nptr, int *neg)
{
	int		i;
	int		j;
	char	n[2];

	i = 0;
	j = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	while (!(nptr[i] >= '0' && nptr[i] <= '9'))
	{
		i++;
		j++;
	}
	n[0] = nptr[i - 1];
	if (j > 1 || ((j == 1) && ((!(ft_isprint(n[0]))) || (ft_isalpha(n[0])))))
		return (0);
	if (nptr[i - 1] == '-')
		neg[0] = -1;
	return (i);
}
