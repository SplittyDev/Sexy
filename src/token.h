//
// Created by Splitty on 27.08.2015.
//

#ifndef SEXY_TOKEN_H
#define SEXY_TOKEN_H

#include <iostream>
#include "tokentype.h"
#include "tokenposition.h"

using namespace std;

class Token {
public:
    Token (TokenType _type, string _value, TokenPosition *_position);
    TokenPosition *position;
    TokenType type;
    string value;
};


#endif //SEXY_TOKEN_H
