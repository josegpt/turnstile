/*
 * Copyright (c) 2024 Jose G Perez Taveras <josegpt27@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum state {
	LOCKED,
	UNLOCKED,
	STATE_COUNT
};

enum event {
	COIN,
	PUSH,
	EVENT_COUNT
};

enum state  nextstate(enum state, enum event);
const char *statestr(enum state);
enum event  strevent(const char *);

/* -----------+----------+---------
 * | state    | coin     | push   |
 * |----------+----------+--------|
 * | locked   | unlocked | locked |
 * | unlocked | unlocked | locked |
 * -----------+----------+---------
 */
enum state FSM[STATE_COUNT][EVENT_COUNT] = {
	{UNLOCKED, LOCKED},
	{UNLOCKED, LOCKED}
};

int
main(void)
{
	enum state currentstate = LOCKED;
	char input[5];
	int quit;

	quit = 1;
	do {
		printf("state: %s\n", statestr(currentstate));
		printf("> ");
		fflush(stdout);
		scanf("%s", input);
		if (strcmp(input, "quit") == 0) {
			quit = 0;
		}
		currentstate = nextstate(currentstate, strevent(input));
	} while (quit);
	return EXIT_SUCCESS;
}

enum state
nextstate(enum state currentstate, enum event currentevent)
{
	return FSM[currentstate][currentevent];
}

const char *
statestr(enum state currentstate)
{
	switch (currentstate) {
	case UNLOCKED: return "unlocked";
	default:       return "locked";
	}
}

enum event
strevent(const char* s)
{
	if (strcmp(s, "coin") == 0) return COIN;

	return PUSH;
}

