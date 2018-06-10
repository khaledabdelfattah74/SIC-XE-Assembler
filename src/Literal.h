#ifndef LITERAL_H
#define LITERAL_H
#include <string>

using namespace std;

class Literal
{
    public:
        Literal(string v = "", int l = 0, int a = 0);
        virtual ~Literal();
        string value;
        int length;
        int address;

    protected:

    private:
};

#endif // LITERAL_H
