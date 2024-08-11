void randfn(int *randptr)
{
        *randptr = 0;
}

int main()
{
        int blah = 9;
        randfn(&blah);
        return 0;
}