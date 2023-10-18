/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:43:26 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/03 18:01:28 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ftrim(char const *s1, char const *set);
int		btrim(char const *s1, char const *set);
char	*copy(char *ptr, char const *s1, int bt, int ft);

char	*ft_strtrim(char const *s1, char const *set)
{
	int				bt;
	int				ft;
	char			*ptr;

	ft = ftrim(s1, set);
	if ((size_t)(ft) == ft_strlen(s1))
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	bt = btrim(s1, set);
	ptr = malloc(ft_strlen(s1) - (ft + bt) + 1);
	if (ptr == NULL)
		return (NULL);
	return (copy (ptr, s1, bt, ft));
}

char	*copy(char *ptr, char const *s1, int bt, int ft)
{
	unsigned long	i;

	i = 0;
	while (i < (ft_strlen(s1) - (bt + ft)))
	{
		ptr[i] = s1[ft + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ftrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && (s1[i] != set[j]))
			j++;
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (i);
}

int	btrim(char const *s1, char const *set)
{
	int	oi;
	int	j;

	oi = ft_strlen(s1);
	while (oi > 0)
	{
		j = 0;
		while (set[j] != '\0' && (s1[oi - 1] != set[j]))
			j++;
		if (set[j] == '\0')
			return (ft_strlen(s1) - oi);
		oi--;
	}
	return (ft_strlen(s1) - oi);
}
