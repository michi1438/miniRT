/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:50:38 by mguerga           #+#    #+#             */
/*   Updated: 2023/04/19 08:53:35 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "../ft_main/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include "../ft_gnl/get_next_line_bonus.h"

typedef struct sct {
	char	type;
	char	*conv_flags;
	int		wid;
	int		precis;
	int		prx_len;
	int		len;
}	t_conv;

typedef struct sctone {
	int	hash;
	int	zero;
	int	neg;
	int	space;
	int	plus;
	int	point;
}	t_toggler;	

char	type_reader(const char *str, int i);
int		width_counter(const char *str, int i);
char	*flag_parser(const char *str, int i);
int		ft_printf(const char *str, ...);
int		no_dupl(char *retstr, char ch, int e, const char *str);
int		testprintargint(int toconv, t_conv *cvut);
void	*create_cvut(const char *str, int i, t_conv *cvut);
int		testprintargstr(const char *toconv, t_conv *cvut);
int		proxylengthcnt(const char *str, int i);
void	*flglying(char *flag, t_toggler *flg);
void	*set_flags(t_toggler *flg);
int		numlen(unsigned long ln, t_conv *cvut);
void	apply_width(int size, int width, t_toggler *flg);
void	appwidspe(int size, int width, t_toggler *flg, t_conv *cvut);
int		printarghex(unsigned int toconv, t_conv *cvut);
void	ft_puthex_fd(unsigned long n, int fd, t_conv *cvut);
void	hexprintshrinker(t_toggler *flg, unsigned int toconv, t_conv *cvut);
int		printargcha(int toconv, t_conv *cvut);
int		printargptr(unsigned long toconv, t_conv *cvut);
int		numbertypes(t_conv *cvut, long long toconv, int i);
int		ptrtypes(t_conv *cvut, void *touconv, int i);
int		testperc(t_conv *cvut);
int		lengthhex(unsigned int toconv, t_conv *cvut, t_toggler *flg);
int		lengthprehex(unsigned int toconv, t_conv *cvut, t_toggler *flg);
int		numlenneg(long long ln, t_conv *cvut);
int		lengthint(int toconv, t_conv *cvut, t_toggler *flg);
int		lengthpreint(int toconv, t_conv *cvut);
int		testprintarguns(unsigned int toconv, t_conv *cvut);
void	ft_putuns_fd(unsigned int ln, int fd, t_conv *cvut);
int		precision_counter(const char *str, int i);
void	dealwithpoints(t_toggler *flg, int toconv, t_conv *cvut);
void	dealwithplneg(t_toggler *flg, t_conv *cvut, int toconv);
void	spcplunopoint(t_toggler *flg, int toconv, t_conv *cvut);
void	simple_cvutlen(t_toggler *flg, t_conv *cvut, int toconv);
void	argintprt(t_toggler *flg, t_conv *cvut, int toconv);
void	cvut_lenpoint(t_toggler *flg, t_conv *cvut, int toconv);
void	strshrinker(t_toggler *flg, t_conv *cvut, const char *toconv);
void	cvutlenstr(t_conv *cvut, const char *toconv);
void	strcvutneg(t_toggler *flg, t_conv *cvut, const char *toconv);
void	hexshrinker(unsigned int toconv, t_conv *cvut, t_toggler *flg);
void	dealwithplneg(t_toggler *flg, t_conv *cvut, int toconv);
void	dealwithpospoints(t_toggler *flg, t_conv *cvut, int toconv);
int		ft_normprintf(const char *str, int i, int *ret);
int		placeva(int *ret, t_conv *cvut, int i, va_list perc);
void	cleaner(t_conv *cvut);

#endif
