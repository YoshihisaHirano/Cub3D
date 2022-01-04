int	ft_atoi(const char *s)
{
	int			res;
	int			minus;
	char		*str;

	minus = 1;
	res = 0;
	str = (char *) s;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + ((*str) - 48);
		str++;
	}
	return (res * minus);
}
