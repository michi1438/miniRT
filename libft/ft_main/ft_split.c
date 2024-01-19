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

int	count_words(char const *str, char sep)
{
	int	i;
	int	same_word;

	i = 0;
	same_word = 0;
	while (*str)
	{
		if (*str == sep)
			same_word = 0;
		else
		{
			if (!same_word)
			{
				same_word = 1;
				i ++;
			}
		}
		str ++;
	}
	return (i);
}

static size_t	next_wordlen(char const *str, char sep)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == sep)
			return (i);
		else
			i ++;
		str ++;
	}
	return (i);
}

static int	free_split(char ***res, int index)
{
	int	i;

	if ((*res)[index])
		return (0);
	i = 0;
	while (i < index)
	{
		free((*res)[i]);
		i ++;
	}
	free(res);
	return (1);
}

static char	**handle_empty(void)
{
	char	**res;

	res = malloc(sizeof(*res));
	if (!res)
		return (0);
	res[0] = 0;
	return (res);
}

char	**ft_split(char const *str, char sep)
{
	char	**res;
	int		i;

	if (!count_words(str, sep))
		return (handle_empty());
	res = malloc(sizeof(*res) * (count_words(str, sep) + 1));
	if (!res)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str != sep)
		{
			res[i] = malloc(next_wordlen(str, sep) + 1);
			if (free_split(&res, i))
				return (0);
			ft_strlcpy(res[i], str, next_wordlen(str, sep) + 1);
			i ++;
			str += next_wordlen(str, sep);
		}
		else
			str ++;
	}
	res[i] = 0;
	return (res);
}
