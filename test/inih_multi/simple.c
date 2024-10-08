/* Example: parse a simple configuration file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../submodule/inih/ini.h"

typedef struct
{
        int version[4];
        const char* name;
        const char* email;
} configuration;

int ini_read_counter = 0;

static int handler(void* user, const char* section, const char* name,
                        const char* value)
{
        configuration* pconfig = (configuration*)user;

        #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
        if (MATCH("protocol", "version")) {
                    pconfig->version[ini_read_counter] = atoi(value);
                    ini_read_counter++;
        } else if (MATCH("user", "name")) {
                    pconfig->name = strdup(value);
        } else if (MATCH("user", "email")) {
                    pconfig->email = strdup(value);
        } else {
                    return 0;  /* unknown section/name, error */
        }
        return 1;
}

int main(int argc, char* argv[])
{
        configuration config;
        // config.version = 0;  /* set defaults */
        config.name = NULL;
        config.email = NULL;

        if (ini_parse("test.ini", handler, &config) < 0) {
                printf("Can't load 'test.ini'\n");
                return 1;
        }
        printf("Config loaded from 'test.ini': version=%d, name=%s, email=%s\n",
                config.version[1], config.name, config.email);

        if (config.name)
                free((void*)config.name);
        if (config.email)
                free((void*)config.email);

        return 0;
}