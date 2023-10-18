/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_toconv_suplll.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:42:01 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:46:17 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	dealwithpospoints(t_toggler *flg, t_conv *cvut, int toconv)
{
	int	nlen;
	int	wminp;
	int	i;

	i = 0;
	if (flg->point == 1 && toconv >= 0)
	{
		if (flg->plus == 1)
			cvut->wid -= 1;
		nlen = numlenneg(toconv, cvut);
		wminp = cvut->wid - cvut->precis;
		if (nlen - cvut->wid < wminp && wminp > 0)
			while (i++ < cvut->wid - cvut->precis)
				ft_putchar_fd(' ', 1);
		else if (cvut->wid - (cvut->precis <= numlenneg(toconv, cvut)) > 0)
			while (i++ < cvut->wid - numlenneg(toconv, cvut))
				ft_putchar_fd(' ', 1);
		if (flg->plus == 1)
		{
			ft_putchar_fd('+', 1);
			cvut->wid += 1;
		}
		appwidspe(numlenneg(toconv, cvut), cvut->precis, flg, cvut);
	}
}

void	dealwithpoints(t_toggler *flg, int toconv, t_conv *cvut)
{
	int	i;

	i = 0;
	dealwithpospoints(flg, cvut, toconv);
	if (flg->point == 1 && toconv < 0)
	{
		if ((cvut->wid - (cvut->precis >= numlenneg(toconv, cvut)) - 1 > 0))
		{
			while (i++ < (cvut->wid - cvut->precis) - 1)
				ft_putchar_fd(' ', 1);
			ft_putchar_fd('-', 1);
		}
		else if (cvut->wid - (cvut->precis < numlenneg(toconv, cvut)) > i)
		{
			while (i++ < (cvut->wid - numlenneg(toconv, cvut)))
				ft_putchar_fd(' ', 1);
			ft_putchar_fd('-', 1);
		}
		else
			ft_putchar_fd('-', 1);
		appwidspe(numlenneg(toconv, cvut) - 1, cvut->precis, flg, cvut);
	}
}

void	strshrinker(t_toggler *flg, t_conv *cvut, const char *toconv)
{
	int	i;

	i = 0;
	if (flg->point == 1 && (int)ft_strlen(toconv) != 0 && cvut->precis != 0)
	{
		if ((int)ft_strlen(toconv) != 0 && flg->neg == 0)
			appwidspe(ft_strlen(toconv), cvut->wid, flg, cvut);
		while (i < (int)ft_strlen(toconv) && i < cvut->precis)
		{
			ft_putchar_fd(toconv[i], 1);
			i++;
		}
		if ((int)ft_strlen(toconv) == 0 || flg->neg == 1)
			appwidspe(ft_strlen(toconv), cvut->wid, flg, cvut);
	}
	else if (flg->point == 1 && (int)ft_strlen(toconv) == 0 && cvut->wid > 0)
		appwidspe(ft_strlen(toconv), cvut->wid, flg, cvut);
	if (flg->neg == 0 && flg->point == 0)
		appwidspe(ft_strlen(toconv), cvut->wid - ft_strlen(toconv), flg, cvut);
	if (flg->point == 0)
		ft_putstr_fd((char *)(toconv), 1);
	if (flg->point == 0 && flg->neg == 0)
		cvut->len = cvut->wid;
}

void	cvutlenstr(t_conv *cvut, const char *toconv)
{
	int	convlen;

	if (cvut->precis != 0 && (int)strlen(toconv) != 0)
	{
		convlen = (int)ft_strlen(toconv);
		if ((int)ft_strlen(toconv) < cvut->wid)
			cvut->len = cvut->wid;
		else if (convlen < cvut->precis && cvut->precis < cvut->wid)
			cvut->len = (int)ft_strlen(toconv);
		else if (cvut->precis <= (int)ft_strlen(toconv))
			cvut->len = cvut->precis;
		if (cvut->precis < cvut->wid && (int)ft_strlen(toconv) != 0)
			cvut->len = cvut->wid;
	}
	else if ((int)ft_strlen(toconv) == 0 && cvut->wid > 0)
		cvut->len = cvut->wid;
	else
		cvut->len = 0;
}

void	strcvutneg(t_toggler *flg, t_conv *cvut, const char *toconv)
{
	apply_width(ft_strlen(toconv), cvut->wid, flg);
	if (cvut->wid > (int)ft_strlen(toconv))
		cvut->len = cvut->wid;
	else
		cvut->len = (int)ft_strlen(toconv);
}
