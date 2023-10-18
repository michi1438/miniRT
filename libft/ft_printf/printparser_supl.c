/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printparser_supl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:11:24 by xbeheydt          #+#    #+#             */
/*   Updated: 2023/04/19 08:47:57 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	proxylengthcnt(const char *str, int i)
{
	int	cnt;

	cnt = 1;
	while (!(ft_isalpha(str[i])) && str[i++] != '%')
		cnt++;
	return (cnt);
}
