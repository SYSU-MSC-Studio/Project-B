#include <string>
#include <sstream>
#define BigInteger long long // need to add BigInteger class

class CalculateExpression{
    public:
        explicit CalculateExpression(std::string exper);
        CalculateExpression(const CalculateExpression &other);
        CalculateExpression operator=(const CalculateExpression&); // unsure if it needs reference
        BigInteger calculate();
        ~CalculateExpression() = default;
        BigInteger _Result;
    private:
        BigInteger CalculateAddSub();
        BigInteger CalculateMulDivMod();
        BigInteger CalculateDigit();
        void clearspace();
        std::string _Expression;
        std::string::iterator _Ptr;
};
