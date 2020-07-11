/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:02:58 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/08 15:03:45 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_conf(t_spec *conf, va_list ap)
{
	int		len;
	char	*arg;

	if (conf->type == 'd')
		is_num(conf, ap);
	else if (conf->type == 'u' || conf->type == 'p')
		is_un_num(conf, ap);
	else if (conf->type == 'x' || conf->type == 'X' || conf->type == 'o')
		is_other_num(conf, ap);
	else if (conf->type == 'e' || conf->type == 'E' || conf->type == 'f')
		is_float(conf, ap);
	else if (conf->type == 's' || conf->type == 'c' || conf->size == 'U')
		is_str(conf, ap);
	else
	{
		conf->arg = ft_chrstr(conf->type);
		conf->type = 'c';
	}
	arg = prec_num(conf, conf->arg, ft_strlen(conf->arg));
	if (conf->type == 'C' && ft_strlen(arg) == 0)
		conf->type = 'c';
	len = conf->type == 'c' ? 1 : ft_strlen(arg);
	read_flags(conf, arg, len);
}

char	*prec_num(t_spec *conf, char *arg, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (conf->num == 1)
	{
		if (arg[0] == '0' && len == 1 && conf->prec == 0)
			return (ft_strdup(""));
		if (conf->prec >= len)
		{
			tmp = ft_strnew(conf->prec);
			if (arg[0] == '-')
			{
				arg = ft_strdup(conf->arg + 1);
				tmp[i++] = '-';
				len -= 2;
			}
			else
				arg = ft_strdup(conf->arg);
			while (i < conf->prec - len)
				tmp[i++] = '0';
			return (ft_comb(&tmp, &arg));
		}
	}
	return (ft_strdup(arg));
}

char	*utf_code_str(unsigned int *code, t_spec *conf)
{
	char	*utf;
	char	*tmp;
	char	*str;

	if (code == NULL)
		return (ft_strdup("(null)"));
	if (*code == 0 || conf->prec == 0)
		return (ft_strdup(""));
	str = ft_strnew(0);
	while (*code)
	{
		tmp = utf_code(*code);
		if ((int)ft_strlen(str) + (int)ft_strlen(tmp) <= conf->prec ||
			conf->prec == -1)
			utf = ft_strjoin(str, tmp);
		else
			break ;
		free(str);
		str = ft_strdup(utf);
		free(utf);
		free(tmp);
		code++;
	}
	return (str);
}

char	*utf_code(unsigned int code)
{
	char	*str;

	str = ft_strnew(4);
	if (code <= 0x7F)
		str[0] = code;
	else if (code <= 0x7FF)
	{
		str[0] = 0xC0 | (code >> 6);
		str[1] = 0x80 | (code & 0x3F);
	}
	else if (code <= 0xFFFF)
	{
		str[0] = 0xE0 | (code >> 12);
		str[1] = 0x80 | ((code >> 6) & 0x3F);
		str[2] = 0x80 | (code & 0x3F);
	}
	else
	{
		str[0] = 0xF0 | (code >> 18);
		str[1] = 0x80 | ((code >> 12) & 0x3F);
		str[2] = 0x80 | ((code >> 6) & 0x3F);
		str[3] = 0x80 | (code & 0x3F);
	}
	return (str);
}

void	ft_adress(int *a, t_spec *conf)
{
	int		i;

	i = 0;
	if (conf->prec == 0)
		conf->arg = ft_strdup("");
	else
		conf->arg = ft_hex((unsigned long long int)a, 'x');
	conf->width -= 2;
	while (++i < conf->prec && conf->prec > (int)ft_strlen(conf->arg))
		conf->arg = ft_addchr_s(conf->arg, '0');
	if (conf->flags == NULL)
		conf->flags = ft_addchr_e(conf->flags, '#');
	else if (ft_strchr(conf->flags, '#') == NULL)
		conf->flags = ft_addchr_e(conf->flags, '#');
}
