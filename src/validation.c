#include "push_swap.h"

int check_validate(char **args, int len, int **a)
{
	int i;
	int size;
	int count_elements;

	i = skip_flags(args);
	count_elements = len + (i + 1) * -1;
	if (count_elements < 1)
		error("please, enter minimum 2 numbers");
	*a = ft_memalloc(sizeof(int) * count_elements);
	size = 0;
	while (++i <= len)
	{
		if ((!ft_strchr(args[i], '-')) ||
			(ft_strchr(args[i], '-') && ft_isdigit(args[i][1])))
			(*a)[size] = ft_atoi(args[i]);
		else
			error("Invalid value");
		size++;
	}
	return (size);
}

char **parse_string(const char **argv, int len, int *stk_size)
{
	char ***tmp;
	int i;
	int j;
	int size;

	j = -1;
	i = -1;
	size = -1;
	tmp = (char ***) ft_memalloc(sizeof(char **) * len);
	while (++i < len)
	{
		tmp[i] = ft_strsplit(argv[i], ' ');
		while (tmp[i][++j] != NULL)
			size++;
		j = -1;
	}
	*stk_size = size;
	return (merge_stack(&tmp, size));
}

int skip_flags(char **args)
{
	int count_flags;

	if (ft_strequ(args[0], "-h") || ft_strequ(args[0], "-help"))
		help_flag();
	count_flags = -1;
	if (ft_strequ(args[0], "-v") || ft_strequ(args[0], "-c"))
		count_flags++;
	if (ft_strequ(args[1], "-v") || ft_strequ(args[1], "-c"))
		count_flags++;
	return (count_flags);
}

void check_repeat(const char **args)
{
	int i;

	i = 0;
	while (args[i + 1])
	{
		check_number(args[i]);
		check_number(args[i + 1]);
		cmp_args(args[i], &args[i + 1]);
		i++;
	}
}

void check_number(const char *str)
{
	char	*tmp;

	tmp = ft_itoa(ft_latoi(str));
	if (!tmp || ft_strcmp(tmp, str))
		error("I'ts not are number!");
	ft_strdel(&tmp);
}

void	cmp_args(const char *cmp, const char **args)
{
	int i;

	i = -1;
	if (!args || !cmp)
		return ;
	while (args[++i])
		if (!ft_strcmp(args[i], cmp))
			error("repeat numbers!");
}

void error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar('\n');
	exit(1);
}
