/*
 * FT_DES, made by fventuri.
*/

#include <ft_des.h>

//
// PERMUTATIONS TABLES
//
const uint32_t pc1[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

const uint32_t pc2[48] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

const uint32_t	subkey_rot[16] = {
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1
};

const uint32_t init_perm[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const uint32_t final_perm[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};

const uint32_t expand[48] = {
	32, 1, 2, 3, 4, 5, 4, 5,
	6, 7, 8, 9, 8, 9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32, 1
};

const uint32_t s_box[8][4][16] = {
	{
		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
		{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
		{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
	},

	{
		{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
		{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
		{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
		{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
	},

	{
		{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
		{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
		{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
		{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
	},

	{
		{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
		{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
		{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
		{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
	},

	{
		{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
		{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
		{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
		{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
	},

	{
		{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
		{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
		{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
		{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
	},

	{
		{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
		{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
		{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
		{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
	},

	{
		{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
		{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
		{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
		{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
	},
};

const uint32_t p_box[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25
};

//
// FUNCTIONS
//

// Converts an array of [8] bits values into a [64] bits number
static uint64_t	get_m(uint8_t *msg)
{
	uint64_t	ret = 0;
	uint32_t	i;

	for (i = 0; i < 8; ++i)
	{
		ret <<= 8;
		ret += msg[i];
	}
	return (ret);
}

// Converts a [64] bits message <m> into an array of [8] bits value
// ONLY WORKING ON LITTLE ENDIAN AT THE MOMENT
static void		set_m(uint8_t *msg, uint64_t m)
{
	uint32_t	i;

	for (i = 0; i < 8; ++i)
		msg[i] = m >> (56 - (8 * i));
}

// Permute a [n_len] bits <nbr> to create a [t_len] value with the permutation table <table>
static uint64_t	permute(const uint64_t nbr, const uint32_t *table, size_t t_len, size_t n_len)
{
	uint64_t	ret = 0;
	uint32_t	i;

	for (i = 0; i < t_len; ++i)
	{
		ret <<= 1;
		ret += (nbr << (table[i] - 1 + (64 - n_len))) >> 63;
	}
	return (ret);
}

// Concat two [28] bits subkeys <c> and <d> into a [56] bits key
static uint64_t	subkeycat(uint64_t c, uint64_t d)
{
	uint64_t	ret = c;

	ret <<= 28;
	ret += d;
	return (ret);
}

// Rotate on left <nbr>
static uint32_t	rol_subkey(uint64_t nbr, uint32_t state)
{
	uint32_t	i;

	for (i = 0; i < subkey_rot[state]; ++i)
		nbr = (((nbr << 36) >> 35) + (nbr >> 27)) & 0xfffffff;
	return (nbr);
}

// Get the <i>-th [6] bits block from the [48] bits expanded subkey <blocks>
static uint8_t		get_block(uint64_t blocks, uint32_t i)
{
	return ((blocks << (16 + (i * 6))) >> 58);
}

// Considering a {abcdef} [6] bits number, extracts the bits {af} as <i> and {bcde} as <j>
// and returns the corresponding value from the permutation table <table>
static uint8_t		replace(const uint8_t block, const uint32_t table[4][16])
{
	uint8_t	i = 0;
	uint8_t	j = 0;

	i = ((block >> 5) << 1) + (block & 1);
	j = (block << 3);
	j >>= 4;
	return (table[i][j]);
}

// Used for the computation of <r> (cf. encrypt function)
static uint64_t	ft(uint64_t r, uint64_t k)
{
	uint64_t	exp_r = permute(r, expand, 48, 32);
	uint64_t	blocks = exp_r ^ k;
	uint32_t	i;
	uint64_t	ret = 0;

	for (i = 0; i < 8; ++i)
	{
		ret <<= 4;
		ret += replace(get_block(blocks, i), s_box[i]);
	}
	ret = permute(ret, p_box, 32, 32);
	return (ret);
}

// Generates every k once for the whole encryption process
static void		generate_keys(uint64_t k[16], uint64_t key)
{
	uint32_t	i; // ITERATOR
	uint64_t	c = key >> 28;
	uint64_t	d = (key << 36) >> 36;

	if (k)
	{
		for (i = 0; i < 16; ++i)
		{
			c = rol_subkey(c, i);
			d = rol_subkey(d, i);
			k[i] = permute(subkeycat(c, d), pc2, 48, 56);
		}
	}
}

// Encryption function. This is where the magic happens
uint8_t		*encrypt(uint8_t *msg, uint64_t key, size_t len)
{
	size_t		max_len = (len / 8) * 8;
	uint32_t	i; // ITERATOR
	uint32_t	j; // ITERATOR
	uint64_t	k[16]; // ARRAY OF KEYS
	uint64_t	m; // MSG AS 64bits VALUE
	uint64_t	l; // LEFT PART OF m
	uint64_t	r; // RIGHT PART OF m
	uint64_t	tmp; // USED AS BUFFER FOR l IN FOR LOOP


	// The message can be more than 8 bytes long, we do the same operations every 8 bytes
	generate_keys(k, permute(key, pc1, 56, 64));
	for (i = 0; i < max_len; i += 8)
	{
		m = permute(get_m(&msg[i]), init_perm, 64, 64);
		l = m >> 32;
		r = (m << 32) >> 32;
		for (j = 0; j < 16; ++j)
		{
			tmp = l;
			l = r;
			r = tmp ^ ft(r, k[j]);
		}
		m = permute((r << 32) + l, final_perm, 64, 64);
		set_m(&msg[i], m);
	}

	// Instead of padding the last bytes with zeroes, we XOR them with the original key
	for(i = max_len; i < len; ++i)
		msg[i] ^= key;
	return (msg);
}

// Decryption function. Almost identical to the encrypt() function
uint8_t		*decrypt(uint8_t *msg, uint64_t key, size_t len)
{
	size_t		max_len = (len / 8) * 8;
	uint32_t	i; // ITERATOR
	uint32_t	j; // ITERATOR
	uint64_t	k[16];
	uint64_t	m; // MSG AS 64bits VALUE
	uint64_t	l; // LEFT PART OF m
	uint64_t	r; // RIGHT PART OF m
	uint64_t	tmp; // USED AS BUFFER FOR l IN FOR LOOP


	// The message can be more than 8 bytes long, we do the same operations every 8 bytes
	generate_keys(k, permute(key, pc1, 56, 64));
	for (i = 0; i < max_len; i += 8)
	{
		m = permute(get_m(&msg[i]), init_perm, 64, 64);
		l = m >> 32;
		r = (m << 32) >> 32;
		for (j = 0; j < 16; ++j)
		{
			tmp = l;
			l = r;
			r = tmp ^ ft(r, k[15 - j]);
		}
		m = permute((r << 32) + l, final_perm, 64, 64);
		set_m(&msg[i], m);
	}

	// Instead of padding the last bytes with zeroes, we XOR them with the original key
	for(i = max_len; i < len; ++i)
		msg[i] ^= key;
	return (msg);
}
