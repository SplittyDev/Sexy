//
// Created by Splitty on 27.08.2015.
//

#include "token.h"

Token::Token (TokenType _type, string _value, TokenPosition *_position) {
    type = _type;
    value = _value;
    position = _position;
    position->linepos = position->linepos - value.size ();
}