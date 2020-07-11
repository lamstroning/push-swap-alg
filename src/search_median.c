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

int		search_median(t_stk *stk)
{
	int		median;

	median = stk->min + (stk->max - stk->min) / 2;
	sort_stack(stk, median);
	return (median);
}

//void	sort_median(int *a, int *b, t_stk *stk, int m)
void	sort_median(t_stk *stk, int m)
{
//	int		i;
//	int		j;
	int		index;

//	i = 0;
//	j = 0;
	index = -1;
	while (++index < stk->cnt_a)
//	{
		if (stk->a[index] >= m)
			s_push(stk, 'b');
//			a[i++] = stk->a[index];
//		else

//		{
//			write(1, "pb ", 3);
//			b[j++] = stk->a[index];
//		}
//	}
//	free(stk->a);
//	free(stk->b);
//	stk->a = a;
//	stk->cnt_a = i;
//	stk->b = b;
//	stk->cnt_b = j;
}

int 	check_rotate(t_stk *stk)
{
	char cmd;

	cmd = 0;
	return (cmd != 0);
}

int 	check_swap(t_stk *stk)
{
	char cmd;

	cmd = 0;
	if (stk->cnt_a > 1 && stk->a[0] > stk->b[1])
		cmd = 'a';
	if (stk->cnt_a > 1 && stk->a[0] > stk->b[1])
		cmd = cmd == 'a' ? 's' : 'b';
	s_swap(stk ,cmd);
	return (cmd == 0);
}

void	search_cmd(t_stk *stk)
{
	check_swap(stk);
	check_rotate(stk);
}

int		check_sort(t_stk *stk)
{
	int i;

	i = -1;
//	while (++i < stk->cnt_a)
//	{
//		if (stk->a[i] > stk->a[i + 1])
//			return (0);
	search_cmd(stk);
//	}
//	return (stk->cnt_b == 0);
	return (1);
}
void	sort_stack(t_stk *stk, int median) {
//	int		*a;
//	int		*b;
//	int 	len;

//	len = stk->cnt_a;
//	a = ft_memalloc(sizeof(int) * len);
//	b = ft_memalloc(sizeof(int) * len);
//	sort_median(a, b, stk, median);
	sort_median(stk, median);
//	while (!check_sort(stk))
//		continue;
}
