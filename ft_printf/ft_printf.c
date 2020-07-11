/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:23:56 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/08 12:33:26 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			end_return(t_spec *conf)
{
	int		len;

	len = conf->len;
	free(conf);
	return (len);
}

t_spec		*conf_create(void)
{
	t_spec *res;

	res = (t_spec*)malloc(sizeof(t_spec));
	res->len = 0;
	res->type = 0;
	res->flags = NULL;
	res->arg = NULL;
	res->width = 0;
	res->size = 0;
	res->prec = -1;
	res->num = 0;
	return (res);
}

int			ft_printf(char const *format, ...)
{
	va_list	ap;
	int		i;
	t_spec	*conf;

	i = 0;
	conf = conf_create();
	va_start(ap, format);
	while (i < (int)ft_strlen(format))
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i += spec_format(&format[i + 1], ap, conf);
			if (i < (int)ft_strlen(format))
				continue ;
		}
		if (format[i] != '\0' && format[i] != '%')
		{
			ft_putchar(format[i]);
			conf->len++;
		}
		i++;
	}
	va_end(ap);
	return (end_return(conf));
}

int			spec_format(char const *check, va_list ap, t_spec *conf)
{
	char	*tmp;
	int		len;

	if (ft_strlen(check) == 0)
		return (1);
	tmp = read_spec(check);
	len = ft_strlen(tmp);
	if (ft_isdigit(tmp[len - 1]) || save_size(&tmp[len - 1]) != 0)
		return (len + 1);
	if (tmp[len - 1] == '-' || tmp[len - 1] == '+' ||
		tmp[len - 1] == ' ' || tmp[len - 1] == '#')
		return (len + 1);
	conf = conf_save(conf, tmp);
	free(tmp);
	read_conf(conf, ap);
	return (len + 1);
}

char		*read_spec(char const *str)
{
	int		i;
	char	tmp[1];

	i = -1;
	while (str[++i])
	{
		if (str[i] != '.' && !ft_isdigit(str[i]))
		{
			tmp[0] = str[i];
			if (save_size(tmp) == 0 && (tmp[0] != '-' && tmp[0] != '+' &&
			tmp[0] != ' ' && tmp[0] != '#'))
				return (ft_strsub(str, 0, i + 1));
		}
	}
	return (ft_strdup(str));
}
