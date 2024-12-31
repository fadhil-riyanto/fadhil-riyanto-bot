#include "../../../headers/modules.h"
#include <vector>

#ifndef INTRIN_H 
#define INTRIN_H

class intrin_command : public register_new_msg_mod {
public:
        std::string command; /* maybe unused */
        struct ctx *ctx;
        TgBot::Bot *bot;
        TgBot::Message::Ptr *msg;
        TgBot::Api *api;
        struct ini_config *config;

        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
};

struct _intel_intrin_return {
        char* etype;
        char* type;
        char* varname;
};

struct _intel_intrin_parameter {
        char* etype;
        char* type;
        char* varname;
};

struct _intel_instruction {
        char* form;
        char* name;
        char* xed;
};

struct intel_intrinsics_data {
        /* unofficial */
        char*                           name;
        
        struct _intel_intrin_return* return_data;
        struct _intel_intrin_parameter* parameter;
        int                             parameter_len;
        char*                           description;
        char*                           operation;
        struct _intel_instruction*      instruction;
        std::vector<std::string>              *cpuid;
        char*                           header;
        char*                           category;
};

#endif