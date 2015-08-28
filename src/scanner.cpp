//
// Created by Splitty on 27.08.2015.
//

#include <iostream>
#include <list>
#include <sstream>
#include "scanner.h"

using namespace std;

Scanner::Scanner () {
    pos = -1;
    linenum = 1;
    linepos = 0;
}

void Scanner::Feed (string _source) {
    source = _source;
}

list<Token> Scanner::Scan () {
    list<Token> tokens;
    stringstream accum;
    while (CanAdvance ()) {
        SkipWhitespace ();
        if (!CanAdvance ())
            break;
        if (Peek () == '/') {
            if (Peek (2) == '/')
                tokens.push_back (ScanComment ());
            else if (Peek (2) == '*')
                tokens.push_back (ScanMultilineComment ());
            continue;
        } else if (isalpha (Peek ())) {
            tokens.push_back (ScanIdent ());
            continue;
        } else if (isdigit (Peek ())) {
            tokens.push_back (ScanNumber ());
            continue;
        }
        accum.clear ();
        switch (Peek ()) {
            case ';':
                Skip ();
                tokens.push_back (Token (TokenType::Semicolon, ";", GetPosition ()));
                break;
            case ',':
                Skip ();
                tokens.push_back (Token (TokenType::Comma, ",", GetPosition ()));
                break;
            case '=':
                if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "==", GetPosition ()));
                } else {
                    Skip();
                    tokens.push_back (Token(TokenType::Operator, "=", GetPosition ()));
                }
                break;
            case '!':
                if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "!=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "!", GetPosition ()));
                }
                break;
            case '^':
                if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "^=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "^", GetPosition ()));
                }
                break;
            case '<':
                if (Peek (2) == '<') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "<<", GetPosition ()));
                } else if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "<=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "<", GetPosition ()));
                }
                break;
            case '>':
                if (Peek (2) == '>') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, ">>", GetPosition ()));
                } else if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, ">=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, ">", GetPosition ()));
                }
                break;
            case '+':
                if (Peek (2) == '+') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "++", GetPosition ()));
                } else if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "+=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "+", GetPosition ()));
                }
                break;
            case '-':
                if (Peek (2) == '-') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "--", GetPosition ()));
                } else if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "-=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "-", GetPosition ()));
                }
                break;
            case '*':
                if (Peek (2) == '*') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "**", GetPosition ()));
                } else if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "*=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "*", GetPosition ()));
                }
                break;
            case '/':
                if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "/=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "/", GetPosition ()));
                }
                break;
            case '%':
                if (Peek (2) == '=') {
                    Skip (2);
                    tokens.push_back (Token (TokenType::Operator, "%=", GetPosition ()));
                } else {
                    Skip ();
                    tokens.push_back (Token (TokenType::Operator, "%", GetPosition ()));
                }
                break;
            case '\'':
            case '"':
                tokens.push_back (ScanString ());
                break;
            case '(':
                Skip ();
                tokens.push_back (Token (TokenType::OpeningParen, "(", GetPosition ()));
                break;
            case ')':
                Skip ();
                tokens.push_back (Token (TokenType::ClosingParen, "(", GetPosition ()));
                break;
            case '[':
                Skip ();
                tokens.push_back (Token (TokenType::OpeningSquareBracket, "[", GetPosition ()));
                break;
            case ']':
                Skip ();
                tokens.push_back (Token (TokenType::ClosingSquareBracket, "]", GetPosition ()));
                break;
            case '{':
                Skip ();
                tokens.push_back (Token (TokenType::OpeningCurlyBracket, "{", GetPosition ()));
                break;
            case '}':
                Skip ();
                tokens.push_back (Token (TokenType::ClosingCurlyBracket, "}", GetPosition ()));
                break;
            default:
                cout << "Unexpected character: " << Peek () << " at " << linenum << ":" << linepos << endl;
                Skip ();
                break;
        }
    }
    return tokens;
}

Token Scanner::ScanIdent () {
    stringstream accum;
    accum << Read ();
    while (CanAdvance () && isalnum (Peek ())) {
        accum << Read ();
    }
    return Token (TokenType::Identifier, accum.str (), GetPosition ());
}

Token Scanner::ScanString () {
    char start = Read ();
    stringstream accum;
    while (CanAdvance () && Peek () != start) {
        switch (Peek ()) {
            case '\\':
                if (start == '"') {
                    switch (Peek(2)) {
                        case 'n':
                            accum << '\n';
                            break;
                        case 'r':
                            accum << '\r';
                            break;
                        case 't':
                            accum << '\t';
                            break;
                        default:
                            cout << "Unsupported escape sequence: \\" << Peek (2) << endl;
                            Skip (2);
                            break;
                    }
                } else {
                    accum << Read ();
                    accum << Read ();
                }
                break;
            default:
                accum << Read ();
                break;
        }
    }
    Skip ();
    return Token (TokenType::StringLiteral, accum.str (), GetPosition ());
}

Token Scanner::ScanNumber () {
    stringstream accum;
    while (CanAdvance () && isdigit (Peek ())){
        accum << Read ();
    }
    return Token (TokenType::Number, accum.str (), GetPosition ());
}

Token Scanner::ScanComment () {
    Skip (2);
    SkipWhitespace ();
    if (!CanAdvance ())
        return Token (TokenType::Comment, "", GetPosition ());
    stringstream accum;
    while (CanAdvance () && Peek () != '\n') {
        accum << Read ();
    }
    Skip ();
    return Token (TokenType::Comment, accum.str (), GetPosition ());
}

Token Scanner::ScanMultilineComment () {
    Skip (2);
    SkipWhitespace ();
    stringstream accum;
    while (CanAdvance () && !(Peek () == '*' && Peek (2) == '/')) {
        accum << Read ();
    }
    Skip (2);
    return Token (TokenType::Comment, accum.str (), GetPosition ());
}

TokenPosition *Scanner::GetPosition () {
    TokenPosition *pos = new TokenPosition ();
    pos->linenum = linenum;
    pos->linepos = linepos;
    return pos;
}

bool Scanner::CanAdvance (size_t count) {
    return pos + count < source.length ();
}

void Scanner::Skip (size_t count) {
    for (int i = 0; i < count; i++) {
        if (!CanAdvance ())
            return;
        pos++;
        if (Peek (0) == '\n') {
            linenum++;
            linepos = 0;
        } else
            linepos++;
    }
}

void Scanner::SkipWhitespace () {
    while (CanAdvance () && isspace (Peek ()))
        Skip ();
}

char Scanner::Peek (size_t lookahead) {
    return (char) (CanAdvance (lookahead) ? source[pos + lookahead] : '\0');
}

char Scanner::Read () {
    Skip ();
    return source[pos];
}