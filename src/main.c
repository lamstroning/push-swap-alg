#include "push_swap.h"

t_stk	*create_stack(int stk_size, int *a)
{
	t_stk	*stk;

	stk = (t_stk*)ft_memalloc(sizeof(t_stk));
	stk->a = a;
	stk->b = (int*)ft_memalloc(sizeof(int) * stk_size);
	stk->max = stk->a[0];
	stk->min = stk->a[0];
	stk->cnt_a = stk_size;
	stk->dist = 5;
	stk->cnt_b = 0;
	stk->flags[0] = 0;
	stk->flags[1] = 0;
	return (stk);
}

char	**merge_stack(char ****merge, int size)
{
	char	**res;
	int		i;
	int		j;
	char	**current;

	i = 0;
	j = -1;
	res = (char**)ft_memalloc(sizeof(char *) * (size + 2));
	current = res;
	while (size >= 0)
	{
		while ((*merge)[i][++j] != NULL)
		{
			*res = ft_strdup((*merge)[i][j]);
			res++;
			ft_strdel(&(*merge)[i][j]);
			size--;
		}
		free((*merge)[i]);
		i++;
		j = -1;
	}
	*res = NULL;
	free(*merge);
	return (current);
}

int		main(int argc, const char **argv)
{
	t_stk	*stack;
	int		size;
	char	**args_stk;
	int		*a;

	if (argc <= 1)
		error("empty arguments");
	check_repeat(&argv[1]);
	args_stk = parse_string(&argv[1], argc - 1, &size);
	size = check_validate(args_stk, size, &a);
	stack = create_stack(size, a);
	search_median(stack);
	return (1);
}
