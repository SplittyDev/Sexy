//
// Created by Splitty on 27.08.2015.
//

#ifndef SEXY_TOKENTYPE_H
#define SEXY_TOKENTYPE_H

using namespace std;

enum TokenType {
    Comment,
    Identifier,
    Semicolon,
    Comma,
    Operator,
    StringLiteral,
    Number,
    OpeningParen,
    ClosingParen,
    OpeningCurlyBracket,
    ClosingCurlyBracket,
    OpeningSquareBracket,
    ClosingSquareBracket,
};

static string TokenTypeName[] = {
        [Comment] = "Comment",
        [Identifier] = "Identifier",
        [Semicolon] = "Semicolon",
        [Comma] = "Comma",
        [Operator] = "Operator",
        [StringLiteral] = "StringLiteral",
        [Number] = "Number",
        [OpeningParen] = "OpeningParen",
        [ClosingParen] = "ClosingParen",
        [OpeningCurlyBracket] = "OpeningCurlyBracket",
        [ClosingCurlyBracket] = "ClosingCurlyBracket",
        [OpeningSquareBracket] = "OpeningSquareBracket",
        [ClosingSquareBracket] = "ClosingSquareBracket"
};

#endif