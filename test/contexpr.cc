#include <string>

constexpr unsigned int str2int(const char* str, int h = 0)
{
        return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


int main()
{
        std::string test = "sss";
        switch (str2int(test.c_str())) {
                case str2int("tes"):
                return 8;
                break;

                case str2int("sss"):
                return 3;
                break;
        }

}