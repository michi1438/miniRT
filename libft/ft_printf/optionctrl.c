/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optionctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:11:31 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 08:42:56 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	*flglying(char *flag, t_toggler *flg)
{
	int	i;

	i = 0;
	flg = set_flags(flg);
	while (flag[i] != '\0')
	{
		if (flag[i] == '#')
			flg->hash = 1;
		if (flag[i] == '0')
			flg->zero = 1;
		if (flag[i] == '-')
			flg->neg = 1;
		if (flag[i] == ' ')
			flg->space = 1;
		if (flag[i] == '+')
			flg->plus = 1;
		if (flag[i] == '.')
			flg->point = 1;
		i++;
	}
	return (flg);
}

void	*set_flags(t_toggler *flg)
{
	flg = malloc(sizeof(t_toggler));
	if (flg == NULL)
		return (NULL);
	flg->hash = 0;
	flg->zero = 0;
	flg->neg = 0;
	flg->space = 0;
	flg->plus = 0;
	flg->point = 0;
	return (flg);
}

void	apply_width(int size, int width, t_toggler *flg)
{
	int	i;

	i = 0;
	if (width != 0 || (!(width <= size)))
	{
		while (i < (width - size))
		{
			if (flg->point == 1 && (width < size))
				ft_putchar_fd('0', 1);
			else if (flg->zero == 0 || (flg->zero == 1 && flg->neg == 1))
				ft_putchar_fd(' ', 1);
			else if (flg->zero == 1 && flg->neg == 0 && flg->point == 0)
				ft_putchar_fd('0', 1);
			i++;
		}
	}
}

void	appwidspe(int size, int width, t_toggler *flg, t_conv *cvut)
{
	int	i;

	i = 0;
	if (cvut->precis < width && cvut->type == 's')
		while (i++ < (width - cvut->precis))
			ft_putchar_fd(' ', 1);
	if (width != 0 || (!(width <= size)))
	{
		while (i < (width - size))
		{
			if (flg->point == 1 && size != 0 && cvut->type == 's')
				ft_putchar_fd(' ', 1);
			else if (flg->point == 1 && size != 0)
				ft_putchar_fd('0', 1);
			else if (flg->point == 1 && size == 0)
				ft_putchar_fd(' ', 1);
			else if (flg->zero == 0 || (flg->zero == 1 && flg->neg == 1))
				ft_putchar_fd(' ', 1);
			else if (flg->zero == 1 && flg->neg == 0 && flg->point == 0)
				ft_putchar_fd('0', 1);
			i++;
		}
	}
}

int	numlenneg(long long ln, t_conv *cvut)
{
	int	i;

	i = 0;
	if (ln == 0)
		return (1);
	if (ln < 0)
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
