#ifndef MYCOMPILER_UTILITIES_H
#define MYCOMPILER_UTILITIES_H

#include <iostream>
#include <map>
#include <regex>

bool isInteger(const std::string &input) {
    std::regex integerRegex("^[-+]?\\d+$");
    return std::regex_match(input, integerRegex);
}

bool isFloat(const std::string &input) {
    std::regex floatRegex("^[-+]?\\d+\\.\\d+(?:[eE][-+]?\\d+)?$");
    return std::regex_match(input, floatRegex);
}

bool isValidIdentifier(const std::string &input) {
    std::regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    return std::regex_match(input, identifierRegex);
}

bool isStringConstant(const std::string &input) {
    std::regex stringConstantRegex("^\"[^\"]*\"$");
    return std::regex_match(input, stringConstantRegex);
}

bool isCharacterConstant(const std::string &input) {
    std::regex charConstantRegex("^'[^']'$");
    return std::regex_match(input, charConstantRegex);
}

std::string isKeyword(const std::string &input) {
    std::map<std::string, std::string> Keywords = {
            {"int", "DataType"},
            {"float", "DataType"},
            {"char", "DataType"},
            {"bool", "DataType"},
            {"string", "DataType"},
            {"const", "Const"},
            {"for", "For"},
            {"if", "IF"},
            {"else", "Else"},
            {"break", "BreakContinue"},
            {"continue", "BreakContinue"},
            {"class", "Class"},
            {"inherits", "Inheritance"},
            {"this", "This"},
            {"cout", "CharacterOut"},
            {"cin", "CharacterIn"},
            {"interface", "Interface"},
            {"implements", "Implement"},
            {"public", "AccessModifiers"},
            {"protected", "AccessModifiers"},
            {"private", "AccessModifiers"},
            {"array", "Array"},
            {"stack", "Stack"},
            {"enum", "Enum"},
            {"void", "Void"},
            {"return", "Return"},
    };

    auto it = Keywords.find(input);
    if (it != Keywords.end()) {
        return it->second; // Return the corresponding value
    } else {
        return ""; // Return an empty string if no match found
    }
}

std::string isPunctuator(const std::string &input) {
    std::map<std::string, std::string> Punctuator = {
            {";", ";"}, {":", ":"}, {",", ","}, {"(", "("}, {")", ")"},
            {"{", "{"}, {"}", "}"}, {"[", "["}, {"]", "]"}, {".", "."}
    };

    auto it = Punctuator.find(input);
    if (it != Punctuator.end()) {
        return it->second;
    } else {
        return "";
    }
}

std::string isPOperator(const std::string &input) {
    std::map<std::string, std::string> Operator = {
            {"+", "AddSubtract"},
            {"-", "AddSubtract"},
            {"*", "MultiplyDivideModulo"},
            {"/", "MultiplyDivideModulo"},
            {"%", "MultiplyDivideModulo"},
            {"=", "Assignment"},
            {"+=", "CompoundAssignment"},
            {"-=", "CompoundAssignment"},
            {"*=", "CompoundAssignment"},
            {"/=", "CompoundAssignment"},
            {"%=", "CompoundAssignment"},
            {"&&", "LogicalAnd"},
            {"||", "LogicalAnd"},
            {"<", "RelationalOperator"},
            {">", "RelationalOperator"},
            {"<=", "RelationalOperator"},
            {">=", "RelationalOperator"},
            {"!=", "RelationalOperator"},
            {"==", "RelationalOperator"},
            {"<<", "StreamInsertionOperator"},
            {">>", "StreamExtractionOperator"},
            {"->", "MemberAccessOperator"}
    };

    auto it = Operator.find(input);
    if (it != Operator.end()) {
        return it->second;
    } else {
        return "";
    }
}

//// Define token types
enum class TokenType {
    INTEGER,
    FLOAT,
    STRING,
    CHAR,
    KEYWORD,
    PUNCTUATOR,
    OPERATOR,
    UNKNOWN
};

// Define a struct for tokens
struct Token {
    TokenType type;
    std::string ClassPart;
    std::string ValuePart;
    int LineNo;
};

#endif //MYCOMPILER_UTILITIES_H

//bool isOperator(char ch){
//    for (auto & Operators : Operator) {
////        cout << Operators.first << ": " << Operators.second << endl;
//        char op = Operators.first;
//        if (ch == op)
//            return true;
//        return false;
//    }
//}