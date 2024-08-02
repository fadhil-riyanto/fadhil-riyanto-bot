#include "../headers/int_helper.h"
#include <string>

bool FadhilRiyanto::int_utils::int_helper::int2bool(int src)
{
        return (src == 1) ? true : false;
}

std::string FadhilRiyanto::int_utils::int_helper::int2bool2str(int src)
{
        return (src == 1) ? "true" : "false";
}