/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_conf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:24:50 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/10 19:25:52 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_spec	*conf_save(t_spec *conf, char const *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (save_size(&str[len]) == 0)
		conf->type = str[len];
	if (conf->type == 'i')
		conf->type = 'd';
	conf->flags = save_flags(str, ft_strnew(6));
	conf->width = save_width(str);
	conf->size = save_size(str);
	conf->num = 0;
	if ((str = ft_strrchr(str, '.')) != NULL)
		conf->prec = ft_atoi(++str);
	reinit_type(conf);
	return (conf);
}

char	*save_flags(char const *str, char *flags)
{
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (str[++j])
	{
		if (str[j] == '-' || str[j] == '+' || str[j] == ' ' || str[j] == '#')
		{
			if (ft_strchr(flags, str[j]) == NULL)
				flags[i++] = str[j];
		}
		if ((str[j] == '0' && (!ft_isdigit(str[j - 1]) && str[j - 1] != '.')) ||
			(str[j] == '0' && j == 0))
		{
			if (ft_strchr(flags, '0') == NULL)
				flags[i++] = str[j];
		}
	}
	if (i == 0)
	{
		ft_strdel(&flags);
		return (NULL);
	}
	return (flags);
}

int		save_width(char const *str)
{
	int		width;
	int		i;

	i = 0;
	width = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.' || str[i - 1] == '.')
		{
			i++;
			while (ft_isdigit(str[i]))
				i++;
		}
		else if (i == 0 && ft_isdigit(str[i]))
			width = ft_atoi(&str[i]);
		else if (ft_isdigit(str[i]) && !ft_isdigit(str[i - 1]))
		{
			if (ft_atoi(&str[i]) != 0)
				width = ft_atoi(&str[i]);
		}
		i++;
	}
	return (width);
}

char	save_size(char const *str)
{
	int		i;
	char	sym;

	sym = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (sym == 'z' || sym == 'j')
			break ;
		if (str[i] == 'l' && str[i - 1] == 'l')
			sym = 'w';
		else if (str[i] == 'h' && str[i - 1] == 'h')
			sym = 'H';
		else if (str[i] == 'l' || str[i] == 'h' || str[i] == 'j' ||
			str[i] == 'z' || str[i] == 't' || str[i] == 'L')
			sym = str[i];
	}
	return (sym);
}

void	reinit_type(t_spec *conf)
{
	if (conf->type == 'U')
	{
		conf->type = 'u';
		conf->size = 'w';
	}
	if (conf->type == 'D')
	{
		conf->type = 'd';
		conf->size = 'w';
	}
	if (conf->type == 'O')
	{
		conf->type = 'o';
		conf->size = 'w';
	}
	if (conf->type == 'F')
	{
		conf->type = 'f';
		conf->size = 'w';
	}
	if ((conf->type == 'c' || conf->type == 's') && conf->size == 'l')
		conf->type = conf->type == 's' ? 'S' : 'C';
	if (conf->type == 'C' || conf->type == 'S')
		conf->size = 'U';
}
