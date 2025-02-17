#ifndef ARGS_H
# define ARGS_H

struct s_args
{
	int res_x;
	int res_y;
};

int	parse_args(int ac, char **av, struct s_args *args);

#endif // ARGS_H
