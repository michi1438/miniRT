/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optionctrl_supl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:17:34 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:44:37 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	numlen(unsigned long ln, t_conv *cvut)
{
	int	i;

	i = 0;
	if (ln == 0)
		return (1);
	i += 1;
	if (cvut->type == 'x' || cvut->type == 'X' || cvut->type == 'p')
	{
		while (ln != 0)
		{
			ln = ln / 16;
			i++;
		}
		return (i);
	}
	else
	{
		while (ln != 0)
		{
			ln = ln / 10;
			i++;
		}
		return (i);
	}
}

void	ft_puthex_fd(unsigned long ln, int fd, t_conv *cvut)
{
	char			v;

	if (ln < 16)
	{
		if (ln < 10)
		{
			v = (ln + '0');
			write (fd, &v, 1);
		}
		else
		{
			if (cvut->type == 'x' || cvut->type == 'p')
				v = ((ln - 10) + 'a');
			else
				v = ((ln - 10) + 'A');
			write (fd, &v, 1);
		}
	}
	else if (ln > 15)
	{
		ft_puthex_fd((ln / 16), fd, cvut);
		ft_puthex_fd((ln % 16), fd, cvut);
	}
}

void	ft_putuns_fd(unsigned int ln, int fd, t_conv *cvut)
{
	char			v;

	if (ln < 10)
	{
		v = (ln + '0');
		write (fd, &v, 1);
	}
	else if (ln > 9)
	{
		ft_putuns_fd((ln / 10), fd, cvut);
		ft_putuns_fd((ln % 10), fd, cvut);
	}
}
