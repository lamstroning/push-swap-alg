/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:29:50 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/14 16:29:57 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_flags(t_spec *conf, char *arg, int len)
{
	int		i;

	i = -1;
	if (conf->flags == NULL)
	{
		while (++i < conf->width - len)
			ft_putchar(' ');
		wrtie_arg(conf, arg);
		conf->len += i;
		conf_del(conf, arg);
		return ;
	}
	len = check_len(&arg, conf, len);
	wrtie_flag(arg, conf, i, conf->width - len);
	conf_del(conf, arg);
}

void	flags_imprt(t_spec *conf)
{
	if (conf->type != 'd')
	{
		octop(conf);
		return ;
	}
	conf->len++;
	if (ft_strchr(conf->flags, '+'))
	{
		if (conf->arg[0] == '-')
			ft_putchar('-');
		else
			ft_putchar('+');
	}
	else if (ft_strchr(conf->flags, ' ') && conf->arg[0] != '-')
		ft_putchar(' ');
	else if (ft_strchr(conf->flags, '+') == NULL && conf->arg[0] == '-')
		ft_putchar('-');
	else
		conf->len--;
	octop(conf);
}

void	octop(t_spec *conf)
{
	if (ft_strchr(conf->flags, '#') || conf->type == 'p')
	{
		if (conf->type == 'p')
		{
			ft_putstr("0x");
			conf->len += 2;
		}
		if ((conf->type == 'X' || conf->type == 'x') && conf->arg[0] != '0')
		{
			ft_putchar('0');
			ft_putchar(conf->type);
			conf->len += 2;
		}
		else if (conf->type == 'o' && (conf->arg[0] != '0' || conf->prec == 0))
		{
			if (conf->prec <= (int)ft_strlen(conf->arg))
			{
				ft_putchar('0');
				conf->len += 1;
			}
		}
	}
}

void	conf_del(t_spec *conf, char *arg)
{
	conf->type = 0;
	conf->width = 0;
	conf->size = 0;
	conf->prec = -1;
	conf->num = 0;
	free(conf->flags);
	conf->flags = NULL;
	free(arg);
	free(conf->arg);
	conf->arg = NULL;
}

int		check_len(char **arg, t_spec *conf, int len)
{
	if (*arg[0] == '-' && conf->num == 1)
		ft_rewrite(arg, &arg[0][1]);
	if (conf->arg[0] == '-' && *arg[0] != '-')
		len--;
	if ((ft_strchr(conf->flags, '+') || ft_strchr(conf->flags, ' ')
		|| conf->arg[0] == '-') && conf->type == 'd')
		conf->width--;
	if (ft_strchr(conf->flags, '#'))
	{
		if ((conf->type == 'X' || conf->type == 'x') && conf->arg[0] != '0')
			conf->width -= 2;
		if (conf->type == 'o' && (conf->arg[0] != '0' || conf->prec == 0))
			conf->width--;
	}
	return (len);
}
