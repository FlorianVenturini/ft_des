/*
 * FT_DES, made by fventuri.
*/

#include <ft_des.h>

static int	ft_mag_base(uint64_t nb, uint32_t base, int mag)
{
	if (!nb && !mag)
		return (1);
	if (!nb)
		return (mag);
	return (ft_mag_base(nb / base, base, mag + 1));
}

static char	ft_getdigit_base(uint64_t n, uint32_t base)
{
	if (n > base || base > 62 || base < 2)
		return (0);
	if (n < 10)
		return (n + '0');
	else if (n < 36)
		return (n - 10 + 'a');
	else
		return (n - 36 + 'A');
}

char		*ft_ulitoa_base(uint64_t n, uint32_t base)
{
	char	*ret;
	int		size;

	size = ft_mag_base(n, base, 0);
	if (!(ret = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	bzero(ret, sizeof(char) * (size + 1));
	if (!n)
		ret[0] = '0';
	while (n)
	{
		ret[--size] = ft_getdigit_base(n % base, base);
		n /= base;
	}
	return (ret);
}
