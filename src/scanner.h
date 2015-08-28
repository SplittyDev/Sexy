//
// Created by Splitty on 27.08.2015.
//

#ifndef SEXY_SCANNER_H
#define SEXY_SCANNER_H

#include <iostream>
#include <list>
#include "token.h"

using namespace std;

class Scanner {
public:
    Scanner ();
    void Feed (string _source);
    list<Token> Scan ();
private:
    int pos;
    size_t linenum;
    size_t linepos;
    string source;
    bool CanAdvance (size_t count = 1);
    void Skip (size_t count = 1);
    void SkipWhitespace ();
    Token ScanIdent ();
    Token ScanString ();
    Token ScanNumber ();
    Token ScanComment ();
    Token ScanMultilineComment ();
    TokenPosition *GetPosition ();
    char Peek (size_t lookahead = 1);
    char Read ();
};

#endif //SEXY_SCANNER_H_H
