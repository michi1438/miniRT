/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 23:07:20 by mguerga           #+#    #+#             */
/*   Updated: 2022/10/30 13:06:00 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	v;
	long	ln;

	ln = (long)(n);
	if (ln < 0)
	{
		ln *= -1;
	}
	if (ln < 10 && ln >= 0)
	{
		v = (ln + '0');
		write (fd, &v, 1);
	}
	else if (ln > 9)
	{
		ft_putnbr_fd((ln / 10), fd);
		ft_putnbr_fd((ln % 10), fd);
	}
}
