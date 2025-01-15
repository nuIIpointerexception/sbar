#ifndef _WAYLAND_H
#define _WAYLAND_H

#include "state.h"

int wayland_init(struct state *state);
struct wl_buffer *create_buffer(struct state *state);

#endif
