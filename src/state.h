#ifndef _STATE_H
#define _STATE_H

#include <stdint.h>
#include <wayland-client.h>

struct state {
	struct wl_display *wl_display;
	struct wl_registry *wl_registry;
	struct wl_shm *wl_shm;
	struct wl_compositor *wl_compositor;
	struct wl_output *wl_output;
	struct wl_surface *wl_surface;
	struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1;
	struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1;
	int width;
	int height;
	const char *font;
	uint32_t normal_bg;
	uint32_t normal_fg;
	uint32_t anchor;
};

struct state *state_init(void);

#endif
