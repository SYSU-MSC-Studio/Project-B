#include <CalculateExpression.h>

CalculateExpression::CalculateExpression(std::string expre) : _Expression(expre), _Ptr(_Expression.begin()) {
    _Result = calculate();
}

CalculateExpression::CalculateExpression(const CalculateExpression &other) : _Expression(other._Expression), _Ptr(_Expression.end()), _Result(other._Result) {} 
        
void CalculateExpression::clearspace() {
    while (*_Ptr == ' ') {
        _Ptr ++;
    }
}

CalculateExpression CalculateExpression::operator=(const CalculateExpression &other) {
    _Expression = other._Expression;
    _Ptr = other._Ptr;
    _Result = other._Result;
    return *this;
}

BigInteger CalculateExpression::calculate() {
    return CalculateAddSub();
}

BigInteger CalculateExpression::CalculateAddSub() {
    BigInteger result = CalculateMulDivMod();
    BigInteger right;
    clearspace();
    while (_Ptr != _Expression.end() && (*_Ptr == '+' || *_Ptr == '-')) {
        char ch = *_Ptr++;
        right = CalculateMulDivMod();
        if (ch == '+') {
            result += right;
        }
        else {
            result -= right;
        }
        clearspace();
    }
    return result;
}

BigInteger CalculateExpression::CalculateMulDivMod() {
    BigInteger result = CalculateDigit();
    BigInteger right;
    clearspace();
    while (_Ptr != _Expression.end() && (*_Ptr == '*' || *_Ptr == '/' || *_Ptr == '%')) {
        char ch = *_Ptr++;
        right = CalculateDigit();
        if (ch == '*') {
            result *= right;
        }
        else if (ch == '/') {
            result /= right;
        }
        else {
            result %= right;
        }
        clearspace();
    }
    return result;
}

BigInteger CalculateExpression::CalculateDigit() {
    BigInteger result = 0;
    clearspace();
    if (*_Ptr == '(') {
        ++ _Ptr; // (
        result = calculate();
        clearspace();
        ++ _Ptr; // )
    }
    else if (_Ptr != _Expression.end()) {
        auto distance = _Ptr - _Expression.begin();
        std::string substr = _Expression.substr(distance);
        std::istringstream record(substr);
        record >> result;
        while ((*_Ptr >= '0' && *_Ptr <= '9') || (*_Ptr == '.')) {
            ++_Ptr;
        }
    }
    return result;
}
