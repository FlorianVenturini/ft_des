/*
 * FT_DES, made by fventuri.
 */

// Made thanks to http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

#ifndef FT_DES_H
# define FT_DES_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>

// CRYPT.C
uint8_t		*encrypt(uint8_t *msg, uint64_t key, size_t len);
uint8_t		*decrypt(uint8_t *msg, uint64_t key, size_t len);

// FT_ULITOA_BASE.C
char		*ft_ulitoa_base(uint64_t n, uint32_t base);

// MAIN.C
uint8_t		*fill_msg(uint8_t *msg, char *s, size_t len);

// PRINT.C
void		print_msg(uint8_t *msg, size_t len);
void		print_bits(uint64_t nbr);

#endif
