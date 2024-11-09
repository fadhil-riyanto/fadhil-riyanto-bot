#include <cstdio>
#include <string>
#include <sstream>

std::string split_n_index(std::string src, int index)
{
        std::istringstream iss(src);
        std::string s;

        int initial = 0;

        while(getline(iss, s, ' ' )) {
                
                if (initial == index) {
                        return s;
                }

                initial++;
        }

        return 0;

}

int main()
{
        std::string data = "abc def ghi";
        std::string res = split_n_index(data, 2);

        printf("\"%s\"\n", res.c_str());
}