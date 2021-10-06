#include	"main.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	while (i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		if (s1[i] == '\0')
			return (diff);
		i++;
	}
	return (0);
}

int	is_whitespace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoll(char *s, long long *retnum)
{
	long long	ret;
	int			i;
	int			neg;

	i = 0;
	while (is_whitespace(s[i]))
		i++;
	neg = 1;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		neg = -neg;
		i++;
	}
	ret = 0;
	while (s[i] >= '0' && s[i] <= '9')
		ret = ret * 10 + s[i++] - '0';
	if (i == 0)
		return (-1);
	*retnum = ret * neg;
	return (i);
}
