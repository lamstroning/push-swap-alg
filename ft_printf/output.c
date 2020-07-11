/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:28:34 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/19 15:28:40 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	wrtie_arg(t_spec *conf, char *arg)
{
	if (conf->type == 'c')
	{
		ft_putchar(arg[0]);
		conf->len++;
	}
	else
	{
		if (!ft_strcmp(arg, "(null)") && conf->prec <= 6 && conf->prec != -1)
		{
			free(arg);
			arg = ft_strsub(conf->arg, 0, conf->prec);
			if (conf->prec == 0)
				conf->len++;
		}
		ft_putstr(arg);
		conf->len += ft_strlen(arg);
	}
}

void	wrtie_flag(char *arg, t_spec *conf, int i, int len)
{
	if (ft_strchr(conf->flags, '-'))
	{
		flags_imprt(conf);
		wrtie_arg(conf, arg);
		while (++i < len)
			ft_putchar(' ');
		conf->len += i;
	}
	else if (ft_strchr(conf->flags, '0') && (conf->prec < 0 || conf->num == 0))
	{
		flags_imprt(conf);
		len = check_zero(&arg, len, conf);
		while (++i < len)
			ft_putchar('0');
		wrtie_arg(conf, arg);
		conf->len += i;
	}
	else
	{
		while (++i < len)
			ft_putchar(' ');
		flags_imprt(conf);
		wrtie_arg(conf, arg);
		conf->len += i;
	}
}

int		check_zero(char **arg, int len, t_spec *conf)
{
	if (ft_strcmp(*arg, "(null)"))
		return (len);
	free(*arg);
	*arg = ft_strdup("");
	len = conf->width;
	return (len);
}
