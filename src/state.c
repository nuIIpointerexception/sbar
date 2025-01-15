#include <stdlib.h>
#include "constants.h"
#include "state.h"
#include "wayland.h"

struct state *state_init() {
	struct state *state = calloc(1, sizeof(struct state));
	if (!state) return NULL;
	
	state->font = FONT_SPEC;
	state->normal_bg = COLOR_BACKGROUND;
	state->normal_fg = COLOR_FOREGROUND;
	state->anchor = BAR_ANCHOR;
	state->height = BAR_HEIGHT;
	
	if (wayland_init(state) != 0) {
		free(state);
		return NULL;
	}
	
	return state;
}
