/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_toconv_supllll.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:44:59 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:46:31 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	testprintargint(int toconv, t_conv *cvut)
{
	t_toggler	*flg;

	flg = NULL;
	flg = flglying(cvut->conv_flags, flg);
	argintprt(flg, cvut, toconv);
	free(flg);
	return (cvut->prx_len);
}

void	dealwithplus(t_toggler *flg, t_conv *cvut, int toconv)
{
	int	i;

	i = 0;
	if (toconv >= 0 && flg->point == 0)
	{
		while (i++ < (cvut->wid - numlenneg(toconv, cvut)) - 1)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd('+', 1);
	}
	if (flg->point == 1)
		dealwithpoints(flg, toconv, cvut);
	if (toconv < 0 && flg->point != 1)
	{
		while (i++ < (cvut->wid - numlenneg(toconv, cvut)))
			ft_putchar_fd(' ', 1);
		ft_putchar_fd('-', 1);
	}
}

void	dealwithplneg(t_toggler *flg, t_conv *cvut, int toconv)
{
	if (flg->plus == 1)
		dealwithplus(flg, cvut, toconv);
	else if (flg->space == 1)
	{
		if (toconv >= 0 && flg->point == 1 && cvut->precis >= cvut->wid)
			ft_putchar_fd(' ', 1);
		else if (toconv >= 0 && cvut->wid < numlenneg(toconv, cvut))
			ft_putchar_fd(' ', 1);
		if (flg->point == 1)
			dealwithpoints(flg, toconv, cvut);
		else
			appwidspe(numlenneg(toconv, cvut), cvut->wid, flg, cvut);
		if (toconv < 0 && flg->point != 1)
			ft_putchar_fd('-', 1);
	}
}
