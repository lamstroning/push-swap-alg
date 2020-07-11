/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 19:07:25 by tdontos-          #+#    #+#             */
/*   Updated: 2019/02/12 19:07:27 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//remove this lib for prod
#include <inttypes.h>
void	is_num(t_spec *conf, va_list ap)
{
	conf->num = 1;
	if (conf->size == 0)
		conf->arg = ft_itoa(va_arg(ap, int));
	else if (conf->size == 'z')
		conf->arg = ft_itoa(va_arg(ap, size_t));
	else if (conf->size == 'l')
		conf->arg = ft_itoa(va_arg(ap, long int));
	else if (conf->size == 'w')
		conf->arg = ft_itoa(va_arg(ap, long long int));
	else if (conf->size == 'j')
		conf->arg = ft_itoa(va_arg(ap, intmax_t));
	else if (conf->size == 'h')
		conf->arg = ft_itoa((short int)va_arg(ap, int));
	else if (conf->size == 'H')
		conf->arg = ft_itoa((signed char)va_arg(ap, int));
}

void	is_un_num(t_spec *conf, va_list ap)
{
	if (conf->type == 'p')
	{
		ft_adress(va_arg(ap, int*), conf);
		return ;
	}
	conf->num = 1;
	if (conf->size == 0)
		conf->arg = ft_unitoa(va_arg(ap, unsigned int));
	else if (conf->size == 'l')
		conf->arg = ft_unitoa(va_arg(ap, unsigned long int));
	else if (conf->size == 'w')
		conf->arg = ft_unitoa(va_arg(ap, unsigned long long int));
	else if (conf->size == 'z')
		conf->arg = ft_unitoa(va_arg(ap, size_t));
	else if (conf->size == 'h')
		conf->arg = ft_unitoa((short unsigned int)va_arg(ap, int));
	else if (conf->size == 'H')
		conf->arg = ft_unitoa((unsigned char)va_arg(ap, unsigned int));
	else if (conf->size == 'j')
		conf->arg = ft_unitoa(va_arg(ap, intmax_t));
}

void	is_other_num(t_spec *conf, va_list ap)
{
	conf->num = 1;
	if (conf->type == 'o')
	{
		if (conf->size == 0)
			conf->arg = ft_octal(va_arg(ap, unsigned int));
		else if (conf->size == 'z')
			conf->arg = ft_octal(va_arg(ap, size_t));
		else if (conf->size == 'l' || conf->size == 'w' || conf->size == 'j')
			conf->arg = ft_octal(va_arg(ap, unsigned long int));
		else if (conf->size == 'h')
			conf->arg = ft_octal((unsigned short int)va_arg(ap, unsigned int));
		else if (conf->size == 'H')
			conf->arg = ft_octal((unsigned char)va_arg(ap, unsigned long int));
		return ;
	}
	if (conf->size == 0)
		conf->arg = ft_hex(va_arg(ap, unsigned int), conf->type);
	else if (conf->size == 'l' || conf->size == 'w' || conf->size == 'j')
		conf->arg = ft_hex(va_arg(ap, unsigned long int), conf->type);
	else if (conf->size == 'z')
		conf->arg = ft_hex(va_arg(ap, size_t), conf->type);
	else if (conf->size == 'h')
		conf->arg = ft_hex((unsigned short int)va_arg(ap, int), conf->type);
	else if (conf->size == 'H')
		conf->arg = ft_hex((unsigned char)va_arg(ap, int), conf->type);
}

void	is_str(t_spec *conf, va_list ap)
{
	char *tmp;

	tmp = NULL;
	if (conf->type == 'C')
		conf->arg = utf_code(va_arg(ap, unsigned int));
	else if (conf->type == 'S')
		conf->arg = utf_code_str(va_arg(ap, unsigned int*), conf);
	else if (conf->type == 'c')
		conf->arg = ft_chrstr((char)va_arg(ap, int));
	else
		tmp = va_arg(ap, char *);
	if (tmp == NULL && conf->arg == NULL)
		conf->arg = ft_strdup("(null)");
	else if (conf->type == 's' && conf->size != 'U')
	{
		if (conf->prec == -1)
			conf->arg = ft_strdup(tmp);
		else
			conf->arg = ft_strsub(tmp, 0, conf->prec);
	}
}

void	is_float(t_spec *conf, va_list ap)
{
	if (conf->prec == -1)
		conf->prec = 6;
	if (conf->type == 'e' || conf->type == 'E')
	{
		if (conf->size == 'l' || conf->size == 0)
			conf->arg = ft_expn(va_arg(ap, double), conf->type - 'E');
		if (conf->size == 'w')
			conf->arg = ft_expn(va_arg(ap, long double), conf->type - 'E');
	}
	else if (conf->type == 'f')
	{
		if (conf->size == 0 || conf->size == 'l')
			conf->arg = ft_float_itoa(conf->prec, va_arg(ap, double));
		if (conf->size == 'L' || conf->size == 'w')
			conf->arg = ft_float_itoa(conf->prec, va_arg(ap, long double));
	}
}
