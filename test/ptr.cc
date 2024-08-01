#include <memory>
#include <stdio.h>

int main()
{
        auto abc = std::shared_ptr<int>(new int(10));

        int *normal_ptr = abc.get();
        *normal_ptr = 18;
        abc.unique();
        printf("%d\n", *abc.get());

}