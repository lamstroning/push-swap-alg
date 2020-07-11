/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:55:53 by tdontos-          #+#    #+#             */
/*   Updated: 2020/06/07 20:55:54 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	s_swap(t_stk *stk, char c)
{
	if (c != 'a' && c != 'b' && c != 's')
		return ;
	if ((c == 'b' && stk->cnt_b <= 1) || (c == 'a' && stk->cnt_a <= 1))
		return ;
	if (c != 's')
		c == 'a' ? ft_swap(&stk->a[0], &stk->a[1]) :
		ft_swap(&stk->b[0], &stk->b[1]);
	else
	{
		if (stk->cnt_b > 1)
			ft_swap(&stk->b[0], &stk->b[1]);
		if (stk->cnt_a > 1)
			ft_swap(&stk->a[0], &stk->a[1]);
	}
	ft_printf("s%c ", c);
}

void	s_push(t_stk *stk, char c)
{
	int		*new;
	int		i;
	int		*count;

	if (c != 'a' && c != 'b')
		return ;
	i = -1;
	if ((c == 'b' && stk->cnt_a <= 0) || (c == 'a' && stk->cnt_b <= 0))
		return ;
	count = c == 'b' ? &stk->cnt_b : &stk->cnt_a;
	new = (int *)ft_memalloc(sizeof(int) * ++(*count));
	new[++i] = c == 'b' ? stk->a[0] : stk->b[0];
	while (++i < *count)
		new[i] = c == 'b' ? stk->b[i - 1] : stk->a[i - 1];
	c == 'b' ? free(stk->b) : free(stk->a);
	c == 'b' ? (stk->b = new) :
	(stk->a = new);
	push_down(c == 'b' ? &stk->a : &stk->b, c == 'b' ? (stk->cnt_a -= 1)
		: (stk->cnt_b -= 1));
	ft_printf("p%c ", c);
}

void	push_down(int **stk, int max)
{
	int		i;
	int		*a;

	a = (int *)ft_memalloc(sizeof(int) * max);
	i = -1;
	while (++i < max)
		a[i] = (*stk)[i + 1];
	free(*stk);
	*stk = a;
}

void	s_rotate(t_stk *stk, char c)
{
	int		*tmp;
	int		buf;
	int		count;
	int		i;

	if (c != 'a' && c != 'b' && c != 'r')
		return ;
	if (c != 'r')
	{
		tmp = c == 'a' ? stk->a : stk->b;
		count = c == 'a' ? stk->cnt_a - 1 : stk->cnt_b - 1;
	}
	else
	{
		tmp = stk->a;
		count = stk->cnt_a - 1;
		s_rotate(stk, 'b');
	}
	buf = tmp[0];
	i = -1;
	while (++i < count)
		tmp[i] = tmp[i + 1];
	tmp[i] = buf;
	ft_printf("r%c ", c);
}

void	s_rotate_rev(t_stk *stk, char c)
{
	int		*tmp;
	int		buf;
	int		count;

	if (c != 'a' && c != 'b' && c != 'r')
		return ;
	if (c != 'r')
	{
		tmp = c == 'a' ? stk->a : stk->b;
		count = c == 'a' ? stk->cnt_a - 1 : stk->cnt_b - 1;
	}
	else
	{
		tmp = stk->a;
		count = stk->cnt_a - 1;
		s_rotate_rev(stk, 'b');
	}
	buf = tmp[count];
	while (--count >= 0)
		tmp[count + 1] = tmp[count];
	tmp[0] = buf;
	ft_printf("rr%c ", c);
}
