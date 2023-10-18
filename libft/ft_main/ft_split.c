/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:43:04 by mguerga           #+#    #+#             */
/*   Updated: 2022/11/03 19:44:11 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		counter(char const *s, char c);
void	*implfing(char const *s, char c, char **ptrptr, int *i);
char	**ft_split(char const *s, char c);
int		clear_fing(char **ptrptr, int j);

char	**ft_split(char const *s, char c)
{
	char	**ptrptr;
	int		j;
	int		i[1];

	i[0] = 0;
	ptrptr = malloc(((counter(s, c) + 1) * sizeof(ptrptr)));
	if (ptrptr == NULL)
		return (NULL);
	j = 0;
	while (j < (counter(s, c)))
	{
		if (implfing(s, c, &(ptrptr[j]), i) == NULL)
			if (clear_fing(ptrptr, j) == 0)
				return (NULL);
		j++;
	}
	ptrptr[j] = NULL;
	return (ptrptr);
}

int	clear_fing(char **ptrptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free (ptrptr[i]);
		i++;
	}
	free(ptrptr);
	return (0);
}

void	*implfing(char const *s, char c, char **ptrptr, int *i)
{
	int	e;
	int	buf;

	buf = 0;
	while (s[i[0]] == c)
		i[0]++;
	while (s[i[0]] != c && s[i[0]] != '\0')
	{
		buf++;
		i[0]++;
	}
	*ptrptr = malloc((buf + 1) * sizeof(char));
	if (*ptrptr == NULL)
		return (NULL);
	i[0] -= buf;
	e = 0;
	while (s[i[0]] != c && s[i[0]] != '\0')
	{
		(*ptrptr)[e++] = s[i[0]++];
	}
	(*ptrptr)[e] = '\0';
	return (*ptrptr);
}

int	counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i - 1] != c)
		{
			count++;
			if (s[i] != '\0')
				i++;
		}
	}
	return (count);
}
