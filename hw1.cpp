#include "tokens.hpp"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void checkString(string str) {
    int size = str.size();
    if (str[size - 1] != '\"'){
        printf ("Error unclosed string\n");
        exit(0);
    }
    for (int i = 0; i < size - 1; i++) {
        if (str[i] == '\\') {
            if (i == size - 2 && (i == 0 || str[i - 1] != '\\')) {
                printf("Error unclosed string\n");
                exit(0);
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == 'n') {
                if (i == 0 && size == 3) {
                    printf("Error undefined escape sequence \\n\n");
                    exit(0);
                }
                i += 1;
                continue;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == 't') {
                i += 1;
                continue;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == 'r') {
//                if (i == 0 && size == 3) {
//                    printf("Error undefined escape sequence \\r\n");
//                    exit(0);
//                }
                i += 1;
                continue;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == '\\') {
                i += 1;
                continue;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == '\"') {
                i += 1;
                continue;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == '0') {
                break;
            }
            assert(i + 1 < size - 1);
            if (str[i + 1] == 'x') {
                if (i >= size - 4) {
                    if (i == size - 4) {
                        assert(i + 2 < size - 1);
                        printf("Error undefined escape sequence x%c\n", str[i + 2]);
                    } else {
                        printf("Error undefined escape sequence x\n");
                    }
                    exit(0);
                }
                assert(i + 3 < size - 1);
                string part = str.substr(i + 2, 2);
                if (str[i + 2] == '0' && str[i + 3] == '0')
                    break;
                if (str[i + 2] < '0' || str[i + 2] > '7' ||
                    !((str[i + 3] >= '0' && str[i + 3] <= '9') ||
                      (str[i + 3] >= 'a' && str[i + 3] <= 'f') ||
                      (str[i + 3] >= 'A' && str[i + 3] <= 'F'))) {
                    cout << "Error undefined escape sequence x" << part << endl;
                    exit(0);
                }
                i += 3;
                continue;
            }
            assert(i + 1 < size - 1);
            printf("Error undefined escape sequence %c\n", str[i + 1]);
            exit(0);
        }
    }
}

void printString(string str) {
    int size = str.size();
    for (int i = 0; i < size - 1; i++) {
        if (str[i] == '\\') {
            if (str[i + 1] == 'n') {
                printf("\n");
                i += 1;
                continue;
            }
            if (str[i + 1] == 't') {
                printf("\t");
                i += 1;
                continue;
            }
            if (str[i + 1] == 'r') {
                printf("\r");
                i += 1;
                continue;
            }
            if (str[i + 1] == '\\') {
                printf("\\");
                i += 1;
                continue;
            }
            if (str[i + 1] == '\"') {
                printf("\"");
                i += 1;
                continue;
            }
            if (str[i + 1] == '0') {
                break;
            }
            if (str[i + 1] == 'x') {
                if (str[i + 2] == '0' && str[i + 3] == '0')
                    break;
                string part = str.substr(i + 2, 2);
                char ch = stoul(part, nullptr, 16);
                cout << ch;
                i += 3;
                continue;
            }
        }
        cout << str[i];
    }
    cout << endl;
}

void showToken(const char *name) {
    printf("%d %s %s\n", yylineno, name, yytext);
}


int main() {
    int token;
    while ((token = yylex())) {
        if (token == VOID) {
            showToken("VOID");
        } else if (token == INT) {
            showToken("INT");
        } else if (token == BYTE) {
            showToken("BYTE");
        } else if (token == B) {
            showToken("B");
        } else if (token == BOOL) {
            showToken("BOOL");
        } else if (token == AND) {
            showToken("AND");
        } else if (token == OR) {
            showToken("OR");
        } else if (token == NOT) {
            showToken("NOT");
        } else if (token == TRUE) {
            showToken("TRUE");
        } else if (token == FALSE) {
            showToken("FALSE");
        } else if (token == RETURN) {
            showToken("RETURN");
        } else if (token == IF) {
            showToken("IF");
        } else if (token == ELSE) {
            showToken("ELSE");
        } else if (token == WHILE) {
            showToken("WHILE");
        } else if (token == BREAK) {
            showToken("BREAK");
        } else if (token == CONTINUE) {
            showToken("CONTINUE");
        } else if (token == SC) {
            showToken("SC");
        } else if (token == COMMA) {
            showToken("COMMA");
        } else if (token == LPAREN) {
            showToken("LPAREN");
        } else if (token == RPAREN) {
            showToken("RPAREN");
        } else if (token == LBRACE) {
            showToken("LBRACE");
        } else if (token == RBRACE) {
            showToken("RBRACE");
        } else if (token == ASSIGN) {
            showToken("ASSIGN");
        } else if (token == RELOP) {
            showToken("RELOP");
        } else if (token == BINOP) {
            showToken("BINOP");
        } else if (token == COMMENT) {
            printf("%d COMMENT //\n", yylineno);
        } else if (token == ID) {
            showToken("ID");
        } else if (token == NUM) {
            showToken("NUM");
        } else if (token == STRING) {
            checkString((string) yytext);
            printf("%d STRING ", yylineno);
            printString((string) yytext);
        }
    }
    return 0;
}