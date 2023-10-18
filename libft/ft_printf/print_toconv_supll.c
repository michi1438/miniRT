/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_toconv_supll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:40:03 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:45:59 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	testprintargstr(const char *toconv, t_conv *cvut)
{
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	strshrinker(flg, cvut, toconv);
	if (flg->neg == 1 && flg->point == 0)
		strcvutneg(flg, cvut, toconv);
	else if (flg->point == 1)
		cvutlenstr(cvut, toconv);
	else if (flg->point == 0 && flg->space == 0 && (int)ft_strlen(toconv))
	{
		if (cvut->wid > (int)ft_strlen(toconv))
			cvut->len = cvut->wid;
		else
			cvut->len = (int)ft_strlen(toconv);
	}
	else if ((cvut->wid == 0 || flg->space != 0) && (int)ft_strlen(toconv) > 0)
		cvut->len = (int)ft_strlen(toconv);
	free(flg);
	return (cvut->prx_len);
}

void	hexshrinker(unsigned int toconv, t_conv *cvut, t_toggler *flg)
{
	if (flg->point == 1)
		appwidspe(numlenneg(toconv, cvut), cvut->precis, flg, cvut);
	if (flg->neg == 0 || (flg->neg == 1 && flg->point == 1))
		ft_puthex_fd(toconv, 1, cvut);
	if (flg->neg == 1 && flg->point == 0)
	{
		if (flg->hash == 1 && toconv != 0)
		{
			if (cvut->type == 'x')
				ft_putstr_fd("0x", 1);
			else
				ft_putstr_fd("0X", 1);
			ft_puthex_fd(toconv, 1, cvut);
			apply_width(numlen(toconv, cvut), (cvut->wid - 2), flg);
		}
		else
		{
			ft_puthex_fd(toconv, 1, cvut);
			apply_width(numlen(toconv, cvut), cvut->wid, flg);
		}
	}
}

int	printarghex(unsigned int toconv, t_conv *cvut)
{
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	hexprintshrinker(flg, toconv, cvut);
	hexshrinker(toconv, cvut, flg);
	if (flg->point == 1)
	{
		if (flg->hash == 1 && toconv != 0)
			cvut->len = lengthprehex(toconv, cvut, flg) + 2;
		else
			cvut->len = lengthprehex(toconv, cvut, flg);
	}
	else
	{
		if (flg->hash == 1 && toconv != 0)
			cvut->len = lengthhex(toconv, cvut, flg) + 2;
		else
			cvut->len = lengthhex(toconv, cvut, flg);
	}
	free(flg);
	return (cvut->prx_len);
}

int	printargcha(int toconv, t_conv *cvut)
{
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	if (flg->neg == 0)
		apply_width(1, cvut->wid, flg);
	ft_putchar_fd((unsigned char) toconv, 1);
	if (flg->neg == 1)
		apply_width(1, cvut->wid, flg);
	if (cvut->wid > 1)
		cvut->len = cvut->wid;
	else
		cvut->len = 1;
	free(flg);
	return (cvut->prx_len);
}

int	printargptr(unsigned long toconv, t_conv *cvut)
{	
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	if (flg->neg == 0)
		apply_width((2 + numlen(toconv, cvut)), cvut->wid, flg);
	ft_putstr_fd("0x", 1);
	ft_puthex_fd(toconv, 1, cvut);
	if (flg->neg == 1)
		apply_width((2 + numlen(toconv, cvut)), cvut->wid, flg);
	if (cvut->wid > (2 + numlen(toconv, cvut)))
		cvut->len = cvut->wid;
	free(flg);
	return (cvut->prx_len);
}
