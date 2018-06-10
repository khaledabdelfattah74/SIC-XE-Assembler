#ifndef LITTAB_H
#define LITTAB_H
#include "Literal.h"
#include <unordered_map>

class LitTab
{
    public:
        LitTab();
        virtual ~LitTab();
        int initialAddress = 0;
        int lastAssignedLiteralID = 0;
        bool insert(string);
        bool found(string);
        int assignCurrentLiterals(int, int, string);
        int size();
        unordered_map<string, Literal> litTable;
        unordered_map<int, string> nonAssignedLiterals;

    protected:

    private:
        string to_upper(string);
        int lengthOfInstruction(string);
};

#endif // LITTAB_H
