#ifndef DBG_H
#define DBG_H

#include "../../submodule/log.c-patched/src/log.h"

#define mongoc_dbg_conn(x) {            \
        x == NULL ? log_info("mongoc_dbg_on_null") : log_info("mongoc_dbg_not_null"); \
}                                                                                           \

#endif