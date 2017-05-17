/*
 * FT_DES, made by fventuri.
*/

#include <ft_des.h>

void	print_msg(uint8_t *msg, size_t len)
{
	uint32_t	i;

	for (i = 0; i < len; ++i)
		printf("%s%02hhX", i ? " | " : "", msg[i]);
	printf("\n");
}

void	print_bits(uint64_t nbr)
{
	char	*nb = ft_ulitoa_base(nbr, 2);
	size_t	len = strlen(nb);

	if (len < 64)
		printf("%0*d", (int)(64 - len), 0);
	printf("%s\n", nb);
	free(nb);
}
