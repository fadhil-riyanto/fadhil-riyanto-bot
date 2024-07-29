#include <string>

int main() 
{
        std::string x = "aaaa aaaa";
        std::string::size_type z = x.find(" ");


        printf("%d\n", (z == std::string::npos));
}