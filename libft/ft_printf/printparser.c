/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:30:04 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 08:47:42 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"printf.h"

char	*flag_parser(const char *str, int i)
{
	int		j;
	char	*flags;
	char	*retstr;
	int		ind;

	ind = 0;
	flags = "-0# +.";
	retstr = calloc (6, 1);
	if (retstr == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != '%' && (!(ft_isalpha(str[i]))))
	{
		j = 0;
		while (flags[j] != '\0')
		{
			if (flags[j] == str[i] && no_dupl(retstr, str[i], i, str) != 0)
			{
				retstr[ind] = str[i];
				ind++;
			}
			j++;
		}
		i++;
	}
	return (retstr);
}

int	no_dupl(char *retstr, char ch, int e, const char *str)
{
	int	i;

	i = 0;
	while (retstr[i] != '\0')
	{
		if (retstr[i] == ch)
			return (0);
		i++;
	}
	if (ch == '0' && ft_isdigit(str[e - 1]))
		return (0);
	return (1);
}

char	type_reader(const char *str, int i)
{
	int		j;
	char	*types;

	types = "cspdiuxX%";
	j = 0;
	while (!(ft_isalpha(str[i])) && str[i] != '%')
		i++;
	while (types[j] != '\0')
	{
		if (types[j] == str[i])
			return (str[i]);
		j++;
	}
	return ('0');
}

int	width_counter(const char *str, int i)
{
	int	retval;

	while ((!(ft_isalpha(str[i]))) && (str[i] != '%') && str[i] != '.')
	{
		if (str[i] == '-' || (ft_isdigit(str[i]) && str[i] != '0'))
		{
			retval = ft_atoi(&(str[i]));
			if (retval < 0)
				retval *= -1;
			return (retval);
		}	
		i++;
	}
	return (0);
}

int	precision_counter(const char *str, int i)
{
	int	retval;

	while (str[i] != '.' && str[i] != '%' && str[i] != '\0')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	while (str[i] != '%' && str[i] != '\0')
	{
		if (str[i] == '-' || (ft_isdigit(str[i]) && str[i] != '0'))
		{
			retval = ft_atoi(&(str[i]));
			if (retval < 0)
				retval *= -1;
			return (retval);
		}
		i++;
	}
	return (0);
}
