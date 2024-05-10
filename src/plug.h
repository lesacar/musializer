#ifndef PLUG_H_
#define PLUG_H_

#include <raylib.h>

#ifndef THEME
#define THEME

#define THEME_FILE_NAME "theme.nelf"

typedef struct {
    int lastEditTime;
    char binpath[256];
    char cfgpath[513];
    char shader_path[128];
    Color color;
    struct colorfftB {
    int hue;
    float saturation;
    float value;
    } colorfftB;
    struct colorfftS {
    int hue;
    float saturation;
    float value;
    } colorfftS;
    Color color_accent;
    Color color_background;
    Color color_track_panel_background;
    Color color_track_button_background;
    Color color_track_button_hoverover;
    Color color_timeline_background;
    Color color_popup_background;
    Color color_tooltip_foreground;
} Theme;
#endif

void parse_config_buffer(const char *buffer, Theme *theme);

#define LIST_OF_PLUGS \
    PLUG(plug_init, void, Theme *theme) \
    PLUG(plug_pre_reload, void*, void) \
    PLUG(plug_post_reload, void, void*) \
    PLUG(plug_load_resource, void*, const char*, size_t*) \
    PLUG(plug_free_resource, void, void*) \
    PLUG(plug_update, void, Theme *theme)

#define PLUG(name, ret, ...) typedef ret (name##_t)(__VA_ARGS__);
LIST_OF_PLUGS
#undef PLUG

#endif // PLUG_H_
