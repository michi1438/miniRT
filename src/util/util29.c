/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util26.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

double	get_resolution(void)
{
	double	resolution;

	resolution = RESOLUTION;
	if (getenv("RESOLUTION"))
	{
		resolution = atof(getenv("RESOLUTION"));
		printf("picked up resolution from env: %f\n", resolution);
	}
	else
	{
		printf("using hardcoded resolution: %f\n", resolution);
	}
	return (resolution);
}
