#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "state.h"
#include "wayland.h"

int main(void) {
	struct state *state = state_init();
	if (!state) return 1;
	
	while (1) {
		struct wl_buffer *buffer = create_buffer(state);
		if (!buffer) {
			return 1;
		}
		
		wl_surface_attach(state->wl_surface, buffer, 0, 0);
		wl_surface_damage_buffer(state->wl_surface, 0, 0, state->width, state->height);
		wl_surface_commit(state->wl_surface);
		
		while (wl_display_prepare_read(state->wl_display) != 0) {
			wl_display_dispatch_pending(state->wl_display);
		}
		wl_display_flush(state->wl_display);
		
		if (wl_display_read_events(state->wl_display) == -1) {
			break;
		}
		
		wl_display_dispatch_pending(state->wl_display);
		usleep(UPDATE_INTERVAL_US);
	}
	
	return 0;
}
