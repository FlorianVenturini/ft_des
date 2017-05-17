/*
 * FT_DES, made by fventuri.
*/

#include <ft_des.h>

uint8_t		*fill_msg(uint8_t *msg, char *s, size_t len)
{
	uint32_t	i;

	for (i = 0; i < len; ++i)
		msg[i] = (uint8_t)s[i];
	return (msg);
}

uint8_t		*default_msg(void)
{
	uint8_t		*ret;

	ret = malloc(sizeof(uint8_t) * 8);
	ret[0] = 0x01;
	ret[1] = 0x23;
	ret[2] = 0x45;
	ret[3] = 0x67;
	ret[4] = 0x89;
	ret[5] = 0xAB;
	ret[6] = 0xCD;
	ret[7] = 0xEF;
	return (ret);
}

int			main(void)
{
	uint8_t		*msg = default_msg();
	size_t		len = 8;
	uint64_t	key = 0x133457799BBCDFF1;

	printf("Before:\n");
	print_msg(msg, len);
	msg = encrypt(msg, key, len);
	printf("After:\n");
	print_msg(msg, len);
	msg = decrypt(msg, key, len);
	printf("Decrypted:\n");
	print_msg(msg, len);
	return (0);
}
