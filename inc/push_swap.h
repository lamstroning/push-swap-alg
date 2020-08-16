/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 19:37:49 by tdontos-          #+#    #+#             */
/*   Updated: 2020/06/27 22:47:22 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_stk
{
	int *a;
	int *b;
	int cnt_a;
	int cnt_b;
	int min;
	int max;
	int dist;
	int flags[3];
}					t_stk;

void				error(char *msg);
int					check_validate(char **args, int len, int **a);
void				check_repeat(const char **args);
void				cmp_args(const char *cmp, const char **args);
void				check_number(const char *str);
char				**parse_string(const char **argv, int len, int *stk_size);
int					skip_flags(char **args);
int					help_flag(void);
int					search_median(t_stk *stk);
t_stk				*create_stack(int stk_size, int *a);
char				**merge_stack(char ****merge, int size);
void				sort_median(t_stk *stk, int m);
int					sort_stack(t_stk *stk, int median);
void				s_swap(t_stk *stk, char c);
void				s_push(t_stk *stk, char c);
int					check_rotate(t_stk *stk);
int					check_swap(t_stk *stk);
void				search_cmd(t_stk *stk);
void				first_sort(t_stk *stk, int m);
int					check_sort(t_stk *stk);
int					check_array(const int *a, int len, int direct);
void				s_rotate(t_stk *stk, char c);
void				s_rotate_rev(t_stk *stk, char c);
void				push_down(int **stk, int max);

void				push_all(t_stk *stk, char col);

void 	print_stack(t_stk *stk);

#endif
