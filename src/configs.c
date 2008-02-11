#include <stdlib.h>

#include "utils.h"
#include "configs.h"

extern struct Configs configs;

static gchar *default_encoding = "UTF-8";
static gchar *default_tab_name = "Terminal";
static gchar *default_font = "Monospace 10";
static gint scrollback_lines = 4096;
static gchar *default_word_chars = "-A-Za-z0-9,./?%&#:_~";

/**
 * print error message, free GError
 * */
static void config_error(GError** err)
{
    TRACE_STR((*err)->message);
    g_error_free(*err);
    *err = NULL;
}
static void set_default_value(gchar** var, gchar* value, GError** err)
{
    *var = value;
    config_error(err);
}

static void load_termit_options(GKeyFile *keyfile)
{
    gchar *value = NULL;
    GError * error = NULL;
    value = g_key_file_get_value(keyfile, "termit", "default_tab_name", &error);
    if (!value)
        set_default_value(&configs.default_tab_name, default_tab_name, &error);
    else
        configs.default_tab_name = value;
    TRACE_STR(configs.default_tab_name);

    value = g_key_file_get_value(keyfile, "termit", "default_encoding", &error);
    if (!value)
        set_default_value(&configs.default_encoding, default_encoding, &error);
    else
        configs.default_encoding = value;
    TRACE_STR(configs.default_encoding);
    
    value = g_key_file_get_value(keyfile, "termit", "word_chars", &error);
    if (!value)
        set_default_value(&configs.default_word_chars, default_word_chars, &error);
    else
        configs.default_word_chars = value;
    TRACE_STR(configs.default_word_chars);

    value = g_key_file_get_value(keyfile, "termit", "default_font", &error);
    if (!value)
        set_default_value(&configs.default_font, default_font, &error);
    else
        configs.default_font = value;
    TRACE_STR(configs.default_font);
    
    value = g_key_file_get_value(keyfile, "termit", "scrollback_lines", &error);
    if (!value)
    {
        configs.scrollback_lines = scrollback_lines;
        config_error(&error);
    }
    else
        configs.scrollback_lines = atoi(value);
    if (!configs.scrollback_lines)
        configs.scrollback_lines = scrollback_lines;
    TRACE_NUM(configs.scrollback_lines);

    if (g_key_file_has_key(keyfile, "termit", "encodings", &error) == TRUE)
    {
        TRACE;
        gsize enc_length = 0;
        gchar **encodings = g_key_file_get_string_list(keyfile, "termit", "encodings", &enc_length, &error);
        if (!encodings)
        {
            config_error(&error);
            return;
        }
        configs.encodings = encodings;
        configs.enc_length = enc_length;
    }
    else
    {
        TRACE;
        //config_error(&error); // check carefully - segfault with gtk-2.8.20, glib-2.10.3
    }

    TRACE_NUM(configs.enc_length);
}

static void set_termit_options()
{
    configs.default_tab_name = default_tab_name;
    configs.scrollback_lines = scrollback_lines;
    configs.default_font = default_font;
}

static void load_bookmark_options(GKeyFile *keyfile)
{
    GError * error = NULL;
    gsize len = 0;
    gchar **names = g_key_file_get_keys(keyfile, "bookmarks", &len, &error);
    
    int i=0;
    for (i=0; i<len; i++)
    {
        struct Bookmark b;
        b.name = g_strdup(names[i]);
        b.path = g_key_file_get_value(keyfile, "bookmarks", b.name, &error);
        TRACE_STR(b.name);
        TRACE_STR(b.path);
        g_array_append_val(configs.bookmarks, b);
    }

    g_strfreev(names);
}

void termit_load_config()
{
    configs.bookmarks = g_array_new(FALSE, TRUE, sizeof(struct Bookmark));

    GKeyFile * keyfile = g_key_file_new();
    GError * error = NULL;
    
    const gchar *configFile = "termit.cfg";
    const gchar *configHome = g_getenv("XDG_CONFIG_HOME");
    gchar* fullPath = NULL;
    if (configHome)
        fullPath = g_strdup_printf("%s/termit/%s", configHome, configFile);
    else
    {
        fullPath = g_strdup_printf("%s/.config/termit/%s", g_getenv("HOME"), configFile);
    }
    gboolean configsFound = g_key_file_load_from_file(keyfile, fullPath, G_KEY_FILE_NONE, &error);
    g_free(fullPath);

    if (configsFound)
    {
        TRACE_MSG("config file found");
        if (g_key_file_has_group(keyfile, "termit") == TRUE)
            load_termit_options(keyfile);
        else
            set_termit_options();

        if (g_key_file_has_group(keyfile, "bookmarks") == TRUE)
            load_bookmark_options(keyfile);
        g_key_file_free(keyfile);
    }
    else
    {
        TRACE_MSG("config file not found");
        set_termit_options();
    }

    TRACE_STR(configs.default_tab_name);
    TRACE_STR(configs.default_font);
    TRACE_NUM(configs.scrollback_lines);
}

