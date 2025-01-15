#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "wlr-layer-shell-unstable-v1-client-protocol.h"


#define FONT_FACE "IBM Plex Mono"
#define FONT_SIZE "9"
#define FONT_SPEC FONT_FACE " " FONT_SIZE

#define COLOR_BACKGROUND 0xff000000
#define COLOR_FOREGROUND 0xffffffff 

#define BAR_HEIGHT 24
#define BAR_ANCHOR ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP

#define BUFFER_STRIDE 4
#define UPDATE_INTERVAL_US 1000000

#endif 