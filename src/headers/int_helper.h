#ifndef INT_HELPER_H
#define INT_HELPER_H

#include <string>

namespace FadhilRiyanto::int_utils {
        class int_helper {
                public:
                static bool int2bool(int src);
                static std::string int2bool2str(int src);
        };
}

#endif