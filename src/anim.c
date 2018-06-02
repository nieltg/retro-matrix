/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "prng.h"

#include "anim.h"

/*
 * https://github.com/cacalabs/libcaca/blob/f32c24a/src/cacademo.c
 */

#define TRAIL_MIN (15)
#define TRAIL_MAX (30)
#define TRAIL_DELTA (TRAIL_MAX - TRAIL_MIN)

#define DROPS_MAX  (SCREEN_COL * SCREEN_ROW / 8)

int anim_is_enabled = 1;

char _anim_buf[SCREEN_ROW][SCREEN_COL];

typedef struct
{
	unsigned r, c, show;
	unsigned speed, len;
}
drop_t;

drop_t _anim_drop[DROPS_MAX];

void anim_init (void)
{
	int i;

	for (i = 0; i < DROPS_MAX; i++)
	{
		_anim_drop[i].show = 0;

		_anim_drop[i].r = prng_gen_range (0, 500);
		_anim_drop[i].c = prng_gen_range (0, 500);

		_anim_drop[i].speed = 5 + prng_gen_range (0, 20);

		_anim_drop[i].len = TRAIL_MIN + prng_gen_range(0, TRAIL_DELTA);
	}
}

void anim_next (void)
{
	int i;

	for (i = 0; i < DROPS_MAX; i++)
	{
		if (_anim_drop[i].r > 500)
		{
			_anim_drop[i].r -= 500;
			_anim_drop[i].c = prng_gen_range (0, 500);

			_anim_drop[i].show = anim_is_enabled;
		}
		else
			_anim_drop[i].r += _anim_drop[i].speed;
	}
}

int anim_is_idle (void)
{
	int i;

	if (anim_is_enabled)
		return 0;

	for (i = 0; i < DROPS_MAX; i++)
	{
		if (_anim_drop[i].show)
			return 0;
	}

	return 1;
}

void anim_render (void)
{
	int i, j;

	for (i = 0; i < SCREEN_ROW; i++)
		for (j = 0; j < SCREEN_COL; j++)
			_anim_buf[i][j] = COLOR_BLACK;

	for (i = 0; i < DROPS_MAX; i++)
	{
		unsigned nr, r, c;

		if (!_anim_drop[i].show)
			continue;

		r = _anim_drop[i].r * (SCREEN_ROW + TRAIL_MAX) / 500;
		c = _anim_drop[i].c * (SCREEN_COL) / 500;

		for (j = 0; j < _anim_drop[i].len; j++)
		{
			if (r >= j)
			{
				nr = r - j;

				if (nr < SCREEN_ROW)
				{
					if (j < 2)
						_anim_buf[nr][c] = COLOR_WHITE;
					else
					if (j < _anim_drop[i].len / 4)
						_anim_buf[nr][c] = COLOR_LIGHT_CYAN;
					else
					if (j < _anim_drop[i].len * 4 / 5)
						_anim_buf[nr][c] = COLOR_CYAN;
					else
						_anim_buf[nr][c] = COLOR_DARK_GREY;
				}
			}
		}
	}

	for (i = 0; i < SCREEN_ROW; i++)
		for (j = 0; j < SCREEN_COL; j++)
			vga_screen_set_color (i, j, _anim_buf[i][j]);
}
