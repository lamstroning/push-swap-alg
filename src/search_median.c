/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_median.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 22:57:16 by tdontos-          #+#    #+#             */
/*   Updated: 2020/06/27 23:00:29 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// мин + (макс - мин) / 2 я такую медиану считал
// потом перекидывал числа которые кажется являются большими чем эта медиана
// и так повторял, пока чисел не станет меньше либо равно 3
// их сортировал
// в итоге у тебя в левом стеке 1-3 числа
// А в правом частично отсортированный массив чисел
// затем отсматриваешь какое из чисел в правом проще перекинуть в левый (наименьшее число ходов) и его перекидываешь
// и повторяешь, пока не закончатся числа в правом стеке
// затем тебе нужно в первом стеке просто его подвигать, пока минимальное число не станет на первом месте в стеке

#include "push_swap.h"

void	sort_median(t_stk *stk)
{
	while (!sort_stack(stk) && stk->cnt_a > 2 && !check_sort(stk))
		s_push(stk, 'b');
	while (!check_sort(stk))
		search_cmd(stk);
}

int		check_rotate_rev(t_stk *stk)
{
	char cmd;

	cmd = 0;
	if (stk->cnt_a > 1 && stk->a[0] < stk->a[1])
		cmd = 'a';
	if (stk->cnt_b > 1 && stk->b[0] > stk->b[1])
		cmd = cmd == 'a' ? 's' : 'b';
	s_rotate_rev(stk, cmd);
	return (cmd != 0);
}

int		check_rotate(t_stk *stk)
{
	char cmd;

	cmd = 0;
	if (stk->cnt_a > 1 && stk->a[0] > stk->a[stk->cnt_a - 1])
		cmd = 'a';
	if (stk->cnt_b > 1 && stk->b[0] < stk->b[stk->cnt_a - 1])
		cmd = cmd == 'a' ? 's' : 'b';
	s_rotate(stk, cmd);
	return (cmd != 0);
}

int		check_swap(t_stk *stk)
{
	char cmd;

	cmd = 0;
	if (stk->cnt_a > 1 && stk->a[0] < stk->a[1])
		cmd = 'a';
	if (stk->cnt_b > 1 && stk->b[0] > stk->b[1])
		cmd = cmd == 'a' ? 's' : 'b';
	s_swap(stk, cmd);
	return (cmd == 0);
}

void	push_all(t_stk *stk, char col)
{
	int		len;

	len = col == 'a' ? stk->cnt_a : stk->cnt_b;
	while (len-- >= 0)
		s_push(stk, col);
}

void	search_cmd(t_stk *stk)
{
	if (!stk->cnt_a)
		return ;
	check_swap(stk);
	push_all(stk, 'a');
	if (check_sort(stk))
		return;
	check_rotate(stk);
}

int		check_array(const int *arr, int len,  int direct)
{
	int		i;

	i = -1;
	while (++i < len - 1)
		if (arr[i] * direct > arr[i + 1] * direct)
			return (0);
	return (1);
}

void	rotate_sort(t_stk *stk)
{
	int		len;

	len = stk->cnt_a;
	while (len--)
		s_push(stk, 'b');
	len = stk->cnt_b;
	while (len-- > 1)
	{
		s_rotate_rev(stk, 'b');
		s_push(stk, 'a');
	}
	s_push(stk, 'a');
}

void		first_sort(t_stk *stk)
{
	while (stk->cnt_a && stk->a[0] > stk->m)
		s_push(stk, 'b');
}

int		check_sort(t_stk *stk)
{
	if (stk->cnt_b != 0)
		return (0);
	if (check_array(stk->a, stk->cnt_a, -1))
		rotate_sort(stk);
	if (check_array(stk->a, stk->cnt_a, 1))
		return (1);
	return (0);
}

int		sort_stack(t_stk *stk)
{
	int		i;
	int		pos;
	int		count[2];

	count[0] = 0;
	count[1] = 0;
	i = -1;
	pos = -1;
	first_sort(stk);
	while (++i < stk->cnt_a)
		if (stk->a[i] > stk->m)
		{
			pos = i;
			count[i > stk->cnt_a / 2 - 1]++;
		}
	search_range(stk, stk->a, stk->cnt_a);
	if (check_array(stk->a, stk->cnt_a, 1))
		return (1);
	i = count[0] > count[1] ? pos : stk->cnt_a - pos;
	while (--i >= 0 && pos != 0)
		if (count[0] > count[1])
			s_rotate(stk, 'a');
		else
			s_rotate_rev(stk, 'a');
	check_swap(stk);
	return (0);
}
