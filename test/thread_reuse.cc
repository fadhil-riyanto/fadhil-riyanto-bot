#include <cstdio>
#include <thread>

void fn(void)
{
        printf("executed");
}
int main()
{
        std::thread fn2;

        fn2 = std::thread(fn);
        fn2.join();

        fn2 = std::thread(fn);
        fn2.join();
}