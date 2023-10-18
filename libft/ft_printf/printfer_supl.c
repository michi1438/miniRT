/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfer_supl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:07:58 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:47:28 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	numbertypes(t_conv *cvut, long long toconv, int i)
{
	if (cvut->type == 'p')
	{
		cvut->len = (numlen((long long)toconv, cvut) + 2);
		i += printargptr((long unsigned int)toconv, cvut);
	}
	if (cvut->type == 'x' || cvut->type == 'X')
	{
		i += printarghex((unsigned int)toconv, cvut);
	}
	if (cvut->type == 'd' || cvut->type == 'i')
		i += testprintargint((int)toconv, cvut);
	if (cvut->type == 'u')
		i += testprintarguns((unsigned int)toconv, cvut);
	return (i);
}

void	*create_cvut(const char *str, int i, t_conv *cvut)
{
	cvut = malloc(sizeof(t_conv));
	if (cvut == NULL)
		return (NULL);
	cvut->wid = width_counter(str, i);
	cvut->precis = precision_counter(str, i);
	cvut->conv_flags = flag_parser(str, i);
	cvut->type = type_reader(str, i);
	cvut->prx_len = proxylengthcnt(str, i);
	cvut->len = 0;
	return (cvut);
}		
