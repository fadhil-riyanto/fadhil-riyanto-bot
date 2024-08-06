#include <cstdio>
#include <functional>
void randomfunc(int *b)
{
        printf("%d\n", *b);
}

int main()
{
        int a = 10;

        std::function<void(int*)> myfn = randomfunc;

        myfn(&a);
}