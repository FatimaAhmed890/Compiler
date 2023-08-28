#include <bits/stdc++.h>
using namespace std;
#include "Utilities.h"

bool isValidDelimiter(char ch) {
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

vector<std::string> wordBreaker(std::string &line) {
    std::vector<std::string> result;
    std::string currentWord;
    int quotes = 0;
    bool isMultiLineComment = false;


    // loop the line character by character
    for (size_t i = 0; i < line.size(); ++i) {
        char character = line[i];

        //check for multi line comments
        if (character == '~' && line[i+1] == '*'){
            isMultiLineComment = true;
            while(isMultiLineComment) {
                for (i; i < line.size(); ++i) {
                    if (line[i] == '*' && line[i + 1] == '~') {
                        isMultiLineComment = false;
                        break;
                    } else
                        continue;
                }
            }
        }
        if (character == '~') {
            continue;
        } else if (character == ' ') {
            if (!currentWord.empty()) {
                result.push_back(currentWord);
                currentWord.clear();
            }
        }else if (character == '"') {
            quotes++;
            currentWord.push_back(character);
            bool isStringLiteral = true;
            while (isStringLiteral) {
                ++i;
                if (i >= line.size()) {
                    break;
                }
                character = line[i];
                currentWord.push_back(character);
                if (line[i] == '"' && line[i - 1] != '\\') {
                    quotes++;
                    if (quotes % 2 == 0) {
                        isStringLiteral = false;
                    }
                }
            }
        } else if (isValidDelimiter(character)) {
            if (!currentWord.empty()) {
                result.push_back(currentWord);
                currentWord.clear();
            }
            result.push_back(std::string(1, character));
        } else {
            currentWord.push_back(character);
        }
    }

    if (!currentWord.empty()) {
        result.push_back(currentWord);
    }

    return result;
}

Token createToken(const std::string &value, int lineNo) {
    Token token;
    
    token.ClassPart = "None"; // Fill this based on your logic
    token.ValuePart = value;
    token.LineNo = lineNo;
    return token;
}

std::vector<Token> Lexer(const std::vector<std::string> &inputLines) {
    std::vector<Token> tokens;
    int lineNo = 1;

    for (const std::string &line : inputLines) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            TokenType tokenType = TokenType::UNKNOWN;
            if (isInteger(word)) {
                tokenType = TokenType::INTEGER;
            } else if (isFloat(word)) {
                tokenType = TokenType::FLOAT;
            } else if (isStringConstant(word)) {
                tokenType = TokenType::STRING;
            } else if (isCharacterConstant(word)) {
                tokenType = TokenType::CHAR;
            } else if (isKeyword(word)) {
                tokenType = TokenType::KEYWORD;
            } else if (isPunctuator(word)) {
                tokenType = TokenType::PUNCTUATOR;
            } else if (isPOperator(word)) {
                tokenType = TokenType::OPERATOR;
            }

            tokens.push_back(createToken(tokenType, word, lineNo));
        }

        lineNo++;
    }

    return tokens;
}


int main()
{
    fstream file;
    string line;

    file.open("/home/fatima/CLionProjects/MyCompiler/basicSyntax.txt",  ios_base::in);

    if (!file.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    int lineNo = 0;

    while(getline(file, line))
    {
        lineNo++;
        vector<string> words = wordBreaker(line);
        cout << "Words on the line " << lineNo << " are: { ";
        for (const string &word: words)
        {
            cout << word << " , ";
        }
        cout << "}" << endl;
    }


    file.close();
    return 0;
}
