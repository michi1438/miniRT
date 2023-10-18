/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_toconv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:20:39 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 08:44:49 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	testprintarguns(unsigned int toconv, t_conv *cvut)
{
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	if (flg->neg == 0)
		if (flg->plus == 0 && flg->space == 0)
			apply_width(numlen(toconv, cvut), cvut->wid, flg);
	if (flg->point == 1)
		appwidspe(numlenneg(toconv, cvut), cvut->precis, flg, cvut);
	ft_putuns_fd(toconv, 1, cvut);
	if (flg->neg == 1 && flg->point == 0)
		apply_width(numlen(toconv, cvut), cvut->wid, flg);
	if (flg->point == 1)
		cvut->len = lengthprehex(toconv, cvut, flg);
	else
		cvut->len = lengthhex(toconv, cvut, flg);
	free(flg);
	return (cvut->prx_len);
}

void	spcplunopoint(t_toggler *flg, int toconv, t_conv *cvut)
{
	int	nlen;	

	nlen = numlenneg(toconv, cvut);
	if (flg->space == 1 || flg->plus == 1)
	{
		if (toconv > 0 && cvut->precis > cvut->wid)
			cvut->len += 1;
		if (toconv == 0 && cvut->wid <= cvut->precis)
			cvut->len += 1;
	}
	else if (cvut->precis <= cvut->wid && cvut->wid >= numlenneg(toconv, cvut))
	{
		cvut->len = cvut->wid;
		if (flg->space == 0 && flg->plus == 0 && toconv < 0)
			if (cvut->wid < cvut->precis && cvut->precis > nlen)
				cvut->len += 1;
	}
	if (cvut->wid < nlen && nlen > cvut->precis)
	{
		cvut->len = numlenneg(toconv, cvut);
		if (flg->space == 1 || flg->plus == 1)
			if (flg->point == 1 && toconv > 0)
				cvut->len += 1;
	}
}

void	cvut_lenpoint(t_toggler *flg, t_conv *cvut, int toconv)
{
	if (cvut->precis >= cvut->wid)
	{
		if (cvut->precis >= numlenneg(toconv, cvut))
		{
			if (toconv < 0)
				cvut->len = cvut->precis + 1;
			if (toconv >= 0)
				cvut->len = cvut->precis;
		}
		else
			cvut->len = numlenneg(toconv, cvut);
		spcplunopoint(flg, toconv, cvut);
	}
}

void	simple_cvutlen(t_toggler *flg, t_conv *cvut, int toconv)
{
	if (flg->point == 1)
		cvut_lenpoint(flg, cvut, toconv);
	else if ((flg->space == 1 || flg->plus == 1) && toconv >= 0)
	{
		cvut->len = lengthint(toconv, cvut, flg) + 1;
		if (cvut->wid > numlenneg(toconv, cvut))
			cvut->len = cvut->wid;
	}
	else
	{
		if (flg->point == 1)
			cvut->len = lengthpreint(toconv, cvut);
		else
			cvut->len = lengthint(toconv, cvut, flg);
	}
}

void	argintprt(t_toggler *flg, t_conv *cvut, int toconv)
{
	if (flg->plus == 0 && flg->space == 0 && flg->neg == 0)
		if (flg->zero == 0 || (flg->zero == 1 && toconv >= 0))
			apply_width(numlenneg(toconv, cvut), cvut->wid, flg);
	if (toconv < 0 && flg->plus == 0 && flg->space == 0 && flg->point == 0)
	{
		ft_putchar_fd('-', 1);
		if (flg->zero == 1)
			appwidspe(numlenneg(toconv, cvut), cvut->wid, flg, cvut);
	}		
	else if (flg->space == 0 && flg->plus == 0)
		dealwithpoints(flg, toconv, cvut);
	if (flg->space == 1 || flg->plus == 1)
		dealwithplneg(flg, cvut, toconv);
	ft_putnbr_fd(toconv, 1);
	if (flg->neg == 1 && flg->point == 0)
		apply_width(numlenneg(toconv, cvut), cvut->wid, flg);
	simple_cvutlen(flg, cvut, toconv);
}
