/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_toconv_supl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 08:15:45 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 08:45:44 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

void	hexprintshrinker(t_toggler *flg, unsigned int toconv, t_conv *cvut)
{
	if (flg->point == 1)
	{
		if (flg->hash == 1 && toconv != 0)
		{
			if (cvut->type == 'x')
				ft_putstr_fd("0x", 1);
			else
				ft_putstr_fd("0X", 1);
		}
		apply_width(numlen(toconv, cvut), cvut->wid, flg);
	}
	else if (flg->neg == 0)
	{
		if (flg->hash == 1 && toconv != 0)
		{
			if (cvut->type == 'x')
				ft_putstr_fd("0x", 1);
			else
				ft_putstr_fd("0X", 1);
			apply_width(numlen(toconv, cvut), cvut->wid, flg);
		}
		else
			apply_width(numlen(toconv, cvut), cvut->wid, flg);
	}
}

int	lengthhex(unsigned int toconv, t_conv *cvut, t_toggler *flg)
{
	if (cvut->wid < numlen(toconv, cvut))
		cvut->len = numlen(toconv, cvut);
	else
		cvut->len = cvut->wid;
	if (flg->hash == 1 && flg->point == 1 && toconv != 0 && flg->neg == 0)
		cvut->len += 2;
	return (cvut->len);
}

int	lengthprehex(unsigned int toconv, t_conv *cvut, t_toggler *flg)
{
	if (cvut->precis < numlen(toconv, cvut))
		cvut->len = numlen(toconv, cvut);
	else
		cvut->len = cvut->precis;
	if (flg->hash == 1 && flg->point == 1 && toconv != 0 && flg->neg == 0)
		cvut->len += 2;
	return (cvut->len);
}

int	lengthint(int toconv, t_conv *cvut, t_toggler *flg)
{
	if (cvut->wid < numlenneg(toconv, cvut))
		cvut->len = numlenneg(toconv, cvut);
	else
		cvut->len = cvut->wid;
	if (flg->hash == 1 && flg->point == 1 && toconv != 0 && flg->neg == 0)
		cvut->len += 2;
	return (cvut->len);
}

int	lengthpreint(int toconv, t_conv *cvut)
{
	if (cvut->precis < numlenneg(toconv, cvut))
		cvut->len = numlenneg(toconv, cvut);
	else
		cvut->len = cvut->precis;
	return (cvut->len);
}
