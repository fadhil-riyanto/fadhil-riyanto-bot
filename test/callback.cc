#include <cstdio>
#include <functional>

void random(int d)
{
        printf("%d\n", d);
}

class othermem 
{
private:
        std::function<void(int)> *myfn;
public:
        void testcall(std::function<void(int)> recv_func)
        {
                this->myfn = &recv_func;
                this->callit();
        }

        void callit()
        {
                (*this->myfn)(2);
        }
};

int main()
{
        std::function<void(int)> randomfunc = random;

        othermem othermem;
        othermem.testcall(randomfunc);
}