#include <cairo/cairo.h>
#include <pango/pangocairo.h>
#include <time.h>

#include "state.h"
#include "render.h"


static void
cairo_set_source_u32(cairo_t *cairo, uint32_t color) {
	cairo_set_source_rgba(
		cairo,
		(color >> 16 & 0xff) / 255.,  // Red
		(color >> 8 & 0xff) / 255.,   // Green
		(color & 0xff) / 255.,        // Blue
		(color >> 24 & 0xff) / 255.   // Alpha
	);
}


void
render(void *data, struct state *state)
{
	time_t t = time(NULL);
	char time_str[9];
	strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&t));

	cairo_surface_t *surface = cairo_image_surface_create_for_data(
		data,
		CAIRO_FORMAT_ARGB32,
		state->width,
		state->height,
		state->width * 4
	);
	cairo_t *cairo = cairo_create(surface);
	cairo_set_antialias(cairo, CAIRO_ANTIALIAS_FAST);
	cairo_set_source_u32(cairo, state->normal_bg);
	cairo_paint(cairo);

	PangoLayout *layout = pango_cairo_create_layout(cairo);
	PangoFontDescription *desc = pango_font_description_from_string(state->font);
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);

	pango_layout_set_text(layout, time_str, -1);
	int width, height;
	pango_layout_get_pixel_size(layout, &width, &height);
	
	cairo_set_source_u32(cairo, state->normal_fg);
	cairo_move_to(cairo, (state->width - width) / 2, (state->height - height) / 2);
	pango_cairo_show_layout(cairo, layout);

	g_object_unref(layout);
	cairo_destroy(cairo);
	cairo_surface_destroy(surface);
}

