#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_RELATIONAL_OP,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;


typedef struct {
    TokenType type;
    char lexeme[100];
    int line;
    int column;
} Token;


const char* keywords[] = {
    "if", "else", "while", "for", "int", "float", "char", "void",
    "return", "break", "continue", "do", "switch", "case", "default"
};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);


char* input;
int position = 0;
int line = 1;
int column = 1;


bool is_keyword(const char* str);
char peek_char();
char next_char();
void skip_whitespace();
Token get_identifier();
Token get_number();
Token get_relational_operator();
Token get_next_token();
void print_token(Token token);


bool is_keyword(const char* str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}


char peek_char() {
    if (position >= strlen(input)) {
        return '\0';
    }
    return input[position];
}


char next_char() {
    if (position >= strlen(input)) {
        return '\0';
    }
    char ch = input[position++];
    if (ch == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return ch;
}


void skip_whitespace() {
    while (isspace(peek_char())) {
        next_char();
    }
}


Token get_identifier() {
    Token token;
    token.line = line;
    token.column = column;
   
    int i = 0;
    char ch = peek_char();
   
   
    if (isalpha(ch) || ch == '_') {
        token.lexeme[i++] = next_char();
       
       
        while (isalnum(peek_char()) || peek_char() == '_') {
            token.lexeme[i++] = next_char();
        }
    }
   
    token.lexeme[i] = '\0';
   

    if (is_keyword(token.lexeme)) {
        token.type = TOKEN_KEYWORD;
    } else {
        token.type = TOKEN_IDENTIFIER;
    }
   
    return token;
}


Token get_number() {
    Token token;
    token.type = TOKEN_NUMBER;
    token.line = line;
    token.column = column;
   
    int i = 0;
    bool has_dot = false;
   
   
    while (isdigit(peek_char())) {
        token.lexeme[i++] = next_char();
    }
   
   
    if (peek_char() == '.') {
        has_dot = true;
        token.lexeme[i++] = next_char();
       
       
        while (isdigit(peek_char())) {
            token.lexeme[i++] = next_char();
        }
    }
   
    token.lexeme[i] = '\0';
    return token;
}


Token get_relational_operator() {
    Token token;
    token.type = TOKEN_RELATIONAL_OP;
    token.line = line;
    token.column = column;
   
    char ch = next_char();
    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
   

    char next = peek_char();
    if ((ch == '=' && next == '=') ||
        (ch == '!' && next == '=') ||
        (ch == '<' && next == '=') ||
        (ch == '>' && next == '=')) {
        token.lexeme[1] = next_char();
        token.lexeme[2] = '\0';
    }
   
    return token;
}


Token get_next_token() {
    skip_whitespace();
   
    char ch = peek_char();
   
    if (ch == '\0') {
        Token token;
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        token.line = line;
        token.column = column;
        return token;
    }
   
 
    if (isalpha(ch) || ch == '_') {
        return get_identifier();
    }
   
   
    if (isdigit(ch)) {
        return get_number();
    }
   
 
    if (ch == '=' || ch == '!' || ch == '<' || ch == '>') {
        return get_relational_operator();
    }
   
   
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.lexeme[0] = next_char();
    token.lexeme[1] = '\0';
    token.line = line;
    token.column = column - 1;
    return token;
}


void print_token(Token token) {
    const char* type_names[] = {
        "IDENTIFIER", "KEYWORD", "NUMBER", "RELATIONAL_OP", "EOF", "UNKNOWN"
    };
   
    printf("Token: %-15s Lexeme: %-10s Line: %d Column: %d\n",
           type_names[token.type], token.lexeme, token.line, token.column);
}


int main() {
    printf("=== Manual Tokenizer Implementation ===\n\n");
   
   
    char test_input[] = "if (x >= 10) {\n    int count = 25;\n    float rate = 3.14;\n}";
   
    printf("Input:\n%s\n\n", test_input);
    printf("Tokens:\n");
   
   
    input = test_input;
    position = 0;
    line = 1;
    column = 1;
   
 
    Token token;
    do {
        token = get_next_token();
        print_token(token);
    } while (token.type != TOKEN_EOF);
   
    return 0;
}