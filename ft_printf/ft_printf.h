/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:05:00 by tdontos-          #+#    #+#             */
/*   Updated: 2019/01/08 15:07:07 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

typedef struct	s_spec
{
	char		*flags;
	int			width;
	int			prec;
	char		size;
	char		type;
	char		*arg;
	int			num;
	int			len;
}				t_spec;

int				ft_printf(char const *format, ...);
t_spec			*conf_create(void);
char			*read_spec(char const *str);
void			reinit_type(t_spec *conf);
void			ft_adress(int *a, t_spec *conf);

int				spec_format(char const *check, va_list ap, t_spec *conf);
char			*prec_num(t_spec *conf, char *arg, int len);
int				check_len(char **arg, t_spec *conf, int len);

char			*save_flags(char const *str, char *flags);
char			save_size(char const *str);
int				save_width(char const *str);
t_spec			*conf_save(t_spec *conf, char const *str);
void			read_conf(t_spec *conf, va_list ap);

void			is_num(t_spec *conf, va_list ap);
void			is_str(t_spec *conf, va_list ap);
void			is_other_num(t_spec *conf, va_list ap);
void			is_float(t_spec *conf, va_list ap);
void			is_un_num(t_spec *conf, va_list ap);

void			read_flags(t_spec *conf, char *arg, int len);
void			flags_imprt(t_spec *conf);
void			octop(t_spec *conf);
void			conf_del(t_spec *conf, char *arg);
char			*utf_code(unsigned int code);
char			*utf_code_str(unsigned int *code, t_spec *conf);

void			wrtie_flag(char *arg, t_spec *conf, int i, int len);
void			wrtie_arg(t_spec *conf, char *arg);
int				check_zero(char **arg, int len, t_spec *conf);

#endif
