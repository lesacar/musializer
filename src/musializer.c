#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <libgen.h>
#include <ctype.h>
#include <raylib.h>

#ifndef _WIN32
#include <signal.h> // needed for sigaction()
#endif // _WIN32

#include "./hotreload.h"


void parse_config_buffer(const char *buffer, Theme *theme) {
    theme->lastEditTime = GetFileModTime(theme->binpath);
	const char *line_start = buffer;
	const char *line_end = strchr(buffer, '\n');

	while (line_end != NULL) {
		char line[256];
		int len = line_end - line_start;
		strncpy(line, line_start, len);
		line[len] = '\0';

		char key[128], value[128];
		const char *equal_sign = strchr(line, '=');
		if (equal_sign != NULL) {
			int key_len = equal_sign - line;
			strncpy(key, line, key_len);
			key[key_len] = '\0';

			strcpy(value, equal_sign + 1);
			printf("%s --> ", key);
			if (strcmp(key, "shaderPath") == 0)
			{
				for (size_t i = 0; i < strlen(value); i++)
				{
					if (isalnum(value[i]) == 0 && value[i] != '.'  && value[i] != '-' && value[i] != '_')
					{
						value[i] = '\0';
						break;
					}
				}
				strcpy(theme->shader_path, value);
				printf("SHADER: %s\n", theme->shader_path);
			}
			if (strcmp(key, "color_track_button_hoverover") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_track_button_hoverover = tmpCol;
			}
            if (strcmp(key, "color_track_button_background") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_track_button_background = tmpCol;
			}
            if (strcmp(key, "color_accent") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_accent = tmpCol;
			}
            if (strcmp(key, "color_background") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_background = tmpCol;
			}
            if (strcmp(key, "color_track_panel_background") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_track_panel_background = tmpCol;
			}
            if (strcmp(key, "color_timeline_background") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_timeline_background = tmpCol;
			}
            if (strcmp(key, "color_tooltip_foreground") == 0) {
				Color tmpCol = {0};
				int r, g, b, a;
				if (sscanf(value, "%x %x %x %x", &r, &g, &b, &a) == 4) {
					tmpCol.r = r;
					tmpCol.g = g;
					tmpCol.b = b;
					tmpCol.a = a;
					printf("Color: R%d G%d B%d A%d\n", tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
				} else {
					printf("Invalid color format\n");
				}
				theme->color_tooltip_foreground = tmpCol;
			}

            if (strcmp(key, "colorfftB") == 0) {
                float s,v;
                int h;
				if (sscanf(value, "%d %f %f", &h, &s, &v) == 3) {
					printf("Color: H:%d S:%.3f V:%.3f\n", h,s,v);
				} else {
					printf("Invalid color format\n");
				}
				theme->colorfftB.hue = h;
                theme->colorfftB.saturation = s;
                theme->colorfftB.value = v;
			}
            if (strcmp(key, "colorfftS") == 0) {
                float s,v;
                int h;
				if (sscanf(value, "%d %f %f", &h, &s, &v) == 3) {
					printf("Color: H:%d S:%.3f V:%.3f\n", h,s,v);
				} else {
					printf("Invalid color format\n");
				}
				theme->colorfftS.hue = h;
                theme->colorfftS.saturation = s;
                theme->colorfftS.value = v;
			}
		}

		line_start = line_end + 1;
		line_end = strchr(line_start, '\n');
	}

	// Process the last line if it doesn't end with a newline
	if (line_start != NULL) {
		char line[256];
		strcpy(line, line_start);

		char key[128], value[128];
		const char *equal_sign = strchr(line, '=');
		if (equal_sign != NULL) {
			int key_len = equal_sign - line;
			strncpy(key, line, key_len);
			key[key_len] = '\0';

			strcpy(value, equal_sign + 1);
			printf("%s --> ", key);
		}
	}
}

int main(int argc, char **argv)
{
#ifndef _WIN32
	// NOTE: This is needed because if the pipe between Musializer and FFmpeg breaks
	// Musializer will receive SIGPIPE on trying to write into it. While such behavior
	// makes sense for command line utilities, Musializer is a relatively friendly GUI
	// application that is trying to recover from such situations.
	struct sigaction act = {0};
	act.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &act, NULL);
#endif // _WIN32

	if (!reload_libplug()) return 1;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
	size_t factor = 80;
	InitWindow(factor*16, factor*9, "Musializer");
	SetWindowMonitor(0);
	{
		const char *file_path = "./resources/logo/logo-256.png";
		size_t data_size;
		void *data = plug_load_resource(file_path, &data_size);
		Image logo = LoadImageFromMemory(GetFileExtension(file_path), data, data_size);
		SetWindowIcon(logo);
		plug_free_resource(data);
	}
	Theme theme = {
        .shader_path = "circle.fs",
        .color_accent = GetColor(0x3359CCFF),
        .color_background = GetColor(0x151515FF),
        .color_popup_background = GetColor(0x140505FF),
        .color_timeline_background = GetColor(0xEEEFF),
        .color_tooltip_foreground = WHITE,
        .color_track_button_background = GetColor(0x383838FF),
        .color_track_button_hoverover = GetColor(0x555555FF),
        .color_track_panel_background = GetColor(0x121212FF)
        // original tsoding colors
    };
	sprintf(theme.binpath, "%s/%s", dirname(argv[0]), THEME_FILE_NAME);
	printf("Loading file: %s\n", theme.binpath);
	FILE *fp_theme = fopen(theme.binpath, "r");
	if (fp_theme != NULL)
	{
		size_t bytes_read = fread(theme.cfgpath, 1, sizeof(theme.cfgpath) - 1, fp_theme);
		theme.cfgpath[bytes_read] = '\0'; // Null-terminate the buffer
		fclose(fp_theme);
		//printf("%s\n", b_theme);
		parse_config_buffer(theme.cfgpath, &theme);
	} else { printf("No theme file\n"); fclose(fp_theme); }

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);
	InitAudioDevice();

	plug_init(&theme);
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_H)) {
			void *state = plug_pre_reload();
			if (!reload_libplug()) return 1;
			plug_post_reload(state);
		}
		plug_update(&theme);
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}
