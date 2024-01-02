/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-hotkeys.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("myplugin", "en-US")

static obs_source_t* hello_text_source;

static obs_hotkey_id hotkey_id;
static bool is_hello_visible = true;

void toggle_hello_visibility(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    is_hello_visible = !is_hello_visible;
    obs_source_set_enabled(hello_text_source, is_hello_visible);
}

bool obs_module_load(void)
{
    hello_text_source = obs_source_create("text_gdiplus", "HelloWorld", NULL, NULL);
    if (hello_text_source) {
        obs_data_t* settings = obs_data_create();
        obs_data_set_string(settings, "text", "Hello World!");
        obs_source_update(hello_text_source, settings);
        obs_data_release(settings);

        obs_frontend_push_ui_translation("Hello World!");

        blog(LOG_INFO, "Hello World! MyPlugin loaded.");

        hotkey_id = obs_hotkey_register_frontend("ToggleHelloWorld", "Toggle Hello World Visibility",
                                                toggle_hello_visibility, NULL);
        obs_hotkey_load(hotkey_id);

        return true;
    }

    return false;
}

void obs_module_unload(void)
{
    obs_frontend_pop_ui_translation();

    if (hello_text_source) {
        obs_source_release(hello_text_source);
        hello_text_source = NULL;
    }

    obs_hotkey_unregister(hotkey_id);

    blog(LOG_INFO, "Goodbye World! MyPlugin unloaded.");
}
