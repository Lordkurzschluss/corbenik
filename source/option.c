#include <common.h>

FILE *conf_handle;

struct config_file *config;
extern uint8_t *enable_list;
void list_patches_build(char *name, int desc_is_fname);

void
regenerate_config()
{
    for(int i=0; i < 4; i++)
        config->magic[i] = CONFIG_MAGIC[i];

    config->config_ver = config_version;
    config->options[OPTION_ACCENT_COLOR] = 2;
    config->options[OPTION_BRIGHTNESS]   = 3;

    if (!(conf_handle = fopen(PATH_CONFIG, "w")))
        poweroff();

    fwrite(config, 1, sizeof(struct config_file), conf_handle);
    fclose(conf_handle);
}

void
mk_structure()
{
    f_mkdir(ROOT);
    f_mkdir(DATA);
      f_mkdir(LIBEXECDIR);
      f_mkdir(LIBDIR);
        f_mkdir(PATH_EXEFS);
          f_mkdir(PATH_EXEFS_TEXT);
          f_mkdir(PATH_EXEFS_DATA);
          f_mkdir(PATH_EXEFS_RO);
        f_mkdir(PATH_FIRMWARES);
        f_mkdir(PATH_MODULES);
      f_mkdir(BINDIR);
#if defined(CHAINLOADER) && CHAINLOADER == 1
      f_mkdir(PATH_CHAINS);
#endif
      f_mkdir(SBINDIR);
      f_mkdir(SYSCONFDIR);
      f_mkdir(LOCALSTATEDIR);
        f_mkdir(PATH_TEMP);
          f_mkdir(PATH_LOADER_CACHE);
        f_mkdir(PATH_LOG);
      f_mkdir(SHAREDIR);
        f_mkdir(PATH_KEYS);
        f_mkdir(LOCALEDIR);
          f_mkdir(PATH_LOCEMU);
}

void
update_config()
{
    int updated = 0;

    if (config->options[OPTION_ACCENT_COLOR] == 0) {
        config->options[OPTION_ACCENT_COLOR] = 2;
        updated = 1;
    }

    if (updated) {
        save_config(); // Save the configuration.
    }
}

void
load_config()
{
    config = (struct config_file*)malloc(sizeof(struct config_file));
    memset(config, 0, sizeof(struct config_file));

    mk_structure(); // Make directory structure if needed.

    // Zero on success.
    if (!(conf_handle = fopen(PATH_CONFIG, "r"))) {
        regenerate_config();
    } else {
        fread(config, 1, sizeof(struct config_file), conf_handle);
        fclose(conf_handle);

        if (memcmp(&(config->magic), CONFIG_MAGIC, 4)) {
            f_unlink(PATH_CONFIG);
            regenerate_config();
        }

        if (config->config_ver < config_version) {
            f_unlink(PATH_CONFIG);
            regenerate_config();
        }
    }

    list_patches_build(PATH_PATCHES, 0);

    update_config();
}

void
save_config()
{
    write_file(enable_list, PATH_TEMP "/PATCHENABLE", FCRAM_SPACING / 2);

    f_unlink(PATH_CONFIG);

    if (!(conf_handle = fopen(PATH_CONFIG, "w")))
        abort("Failed to open config for write?\n");

    config->options[OPTION_RECONFIGURED] = 0; // This should not persist to disk.

    fwrite(config, 1, sizeof(struct config_file), conf_handle);
    fclose(conf_handle);

    config->options[OPTION_RECONFIGURED] = 1; // Save caches on boot.

    fprintf(stderr, "Saved config successfully.\n");
}
