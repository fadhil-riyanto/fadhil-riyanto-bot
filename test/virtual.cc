class randomclass {
public:
        virtual int randommethod() = 0;
};

class ourclass : public randomclass {
public:
        int randommethod() 
        {
                return 2;
        }
        

        int randommethod2() 
        {
                return 2;
        }
};

int main()
{
        randomclass classku = ourclass();

        
}