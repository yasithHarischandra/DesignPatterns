#include <iostream>
#include <map>
#include <stack>
#include <string>

// Abstract Expression class
class Expression {
public:
    virtual int interpret(std::map<char, int>& context) = 0;
};

// Terminal Expression class for variable
class VariableExpression : public Expression {
private:
    char variable;

public:
    VariableExpression(char var) : variable(var) {}

    int interpret(std::map<char, int>& context) override {
        return context[variable];
    }
};

// Terminal Expression class for constant
class ConstantExpression : public Expression {
private:
    int value;

public:
    ConstantExpression(int val) : value(val) {}

    int interpret(std::map<char, int>& context) override {
        return value;
    }
};

// Non-terminal Expression class for addition
class AddExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret(std::map<char, int>& context) override {
        return left->interpret(context) + right->interpret(context);
    }
};

// Client code
int main() {
    // Create a context (variable mappings)
    std::map<char, int> context;
    context['a'] = 5;
    context['b'] = 3;

    // Create expressions
    Expression* expr1 = new VariableExpression('a');
    Expression* expr2 = new ConstantExpression(10);
    Expression* expr3 = new VariableExpression('b');
    Expression* expr4 = new AddExpression(expr1, expr2);
    Expression* expr5 = new AddExpression(expr4, expr3);

    // Interpret and calculate the result
    int result = expr5->interpret(context);

    std::cout << "Result: " << result << std::endl;

    // Clean up memory
    delete expr1;
    delete expr2;
    delete expr3;
    delete expr4;
    delete expr5;

    return 0;
}
