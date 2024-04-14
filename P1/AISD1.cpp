#include <iostream>
#include "MString.h"
#include "Stack.h"
#include "AISD1.h"
using namespace std;

int applyIf(Stack<int>& numbers) {
    int a = numbers.pop(); //fałsz
    int b = numbers.pop(); //prawda
    int c = numbers.pop(); //warunek
    cout << "IF " << a << " " << b << " " << c << " ";
    numbers.showReverse();
    cout << endl;
    return c > 0 ? b : a;
}

int applyMin(Stack<int>& numbers, MString functionName, int numberAmount) {
    int min = INT_MAX;

    cout << functionName;

    while (numberAmount--) {
        int current = numbers.pop();
        cout << " " << current;

        if (current < min) {
            min = current;
        }
    }
    cout << " ";
    numbers.showReverse();
    cout << endl;
    return min;
}

int applyMax(Stack<int>& numbers, MString functionName, int numberAmount) {
    int max = INT_MIN;
    cout << functionName;
    while (numberAmount--) {
        int current = numbers.pop();
        cout << " " << current;
        if (current > max) {
            max = current;
        }
    }
    cout << " ";
    numbers.showReverse();
    cout << endl;
    return max;
}

void ignoreWhiteSpaces(char& c) { //zmienia orgyinalny c
    while (c == ' ' or c == '\t' or c == '\n') {
        //ignorowanie bialych znakow
        c = getchar();
    }
}

bool isOperator(char c) {
    return c == '+' or c == '-' or c == '*' or c == '/';
}

bool isFunction(char function) {
    return function == 'N' or function == 'M' or function == 'I';
}

int makeOperation(char operation, int b, int a) {
    switch (operation) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0) {
            cout << "ERROR" << endl;
            return INT_MAX;
            //przejdz do nastepnego zadania
        }
        else {
            return a / b;
        }
    default:
        break;
    }
    return 0;
}

int getPriority(char c) {
    if (c == 'N')
        return 4;
    else if (c == 'M' || c == 'I')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void adjustSpace(char& prevC, MString& postfixStr, int numberWidth = 1)
{
    if (postfixStr.getSize() - numberWidth < 0)
    {
        return;
    }
    prevC = postfixStr[postfixStr.getSize() - numberWidth];
    if (prevC != ' ')
    {
        postfixStr += ' ';
    }
}

void readDigitAndAddToPostfix(char& c, MString& postfixStr, char& prevC)
{
    MString number;
    while (c != '.' && isdigit(c))
    {
        number += c;
        cin.get(c);
    }
    postfixStr += number;
    adjustSpace(prevC, postfixStr, number.getSize());
}

bool checkIfFunction(Stack<MString>& operatorsStack) {
    while (operatorsStack.top() == ' ') {
        operatorsStack.pop(); //usuwanie spacji
    }
    return isFunction(operatorsStack.top()[0]);
}

int lengthOfFunction(MString function) {
    switch (function[0]) {
    case 'N':
        return 1;
    case 'I':
        return 2;
    case 'M':
        return 3;
    }
    return -1;
}

void closingBracketPostfix(Stack<MString>& operatorsStack, char& prevC, MString& postfixStr)
{
    while (operatorsStack.top() != "(")
    {
        if (prevC != ' ')
        {
            postfixStr += ' ';
        }
        postfixStr += operatorsStack.pop();
        prevC = postfixStr[postfixStr.getSize() - 1];
    }
    if (operatorsStack.top() == "(")
    {
        adjustSpace(prevC, postfixStr, 1);
        operatorsStack.pop();
        //check if there is a Function
        if (!operatorsStack.isEmpty() && checkIfFunction(operatorsStack)) {
            int sizeOfFunction = lengthOfFunction(operatorsStack.top());
            postfixStr += operatorsStack.pop();
            postfixStr += ' ';
            prevC = postfixStr[postfixStr.getSize() - sizeOfFunction];
        }

    }
}

void dotPostfix(Stack<MString>& operatorsStack, char c, MString& postfixStr, char& prevC)
{
    while (!operatorsStack.isEmpty() && operatorsStack.top() != "(" && getPriority(c) <= getPriority(operatorsStack.top()[0]))
    {
        if (c == operatorsStack.top()[0] && c == 'N')
        {
            break;
        }
        postfixStr += operatorsStack.pop();
        adjustSpace(prevC, postfixStr);
    }
    adjustSpace(prevC, postfixStr);
    MString tempOperand = "";
    tempOperand += c;
    operatorsStack.push(tempOperand);
}

void changeMaxMinParametersCount(Stack<MString>& operatorsStack)
{
    int elementNumber = 1;

    if (isOperator(operatorsStack.top()[0]) && operatorsStack.size() > 2) {
        elementNumber = 2;
    }

    MString maxOrMinString = operatorsStack.getElement(elementNumber);

    if (maxOrMinString[0] == 'M')
    {
        MString prefix = maxOrMinString.substr(0, 3);
        MString num = maxOrMinString.substr(3, maxOrMinString.getSize() - 3);
        int number = num.toNumber() + 1;
        MString result = prefix;
        result += MString::toString(number);
        operatorsStack.getElement(elementNumber) = result;
    }
}

MString infixToPostfix() {
    Stack<MString> operatorsStack;
    MString postfixStr;
    char prevC = '#';
    char c;
    // 1 IF ( 1 , 2 + 3 , 4 ) .
    while (cin.get(c) && c != '.' && c != '\n')
    {
        ignoreWhiteSpaces(c);
        if (c == '.')
        {
            break;
        }
        if (c == '(')
        {
            operatorsStack.push("(");
        }
        else if (isdigit(c))
        {
            readDigitAndAddToPostfix(c, postfixStr, prevC);
        }
        else if (c == 'I')
        {
            cin.get(c);
            operatorsStack.push("IF");
        }
        else if (c == 'M') {
            cin.get(c); //I or A
            cin.get(c); //N or X
            if (c == 'N') { //MIN
                operatorsStack.push("MIN0");
            }
            else if(c=='X') { //MAX
                operatorsStack.push("MAX0");
            }
        }
        else if (c == ')')
        {
            changeMaxMinParametersCount(operatorsStack);
            closingBracketPostfix(operatorsStack, prevC, postfixStr);
        }
        else if (c == ',') {

            changeMaxMinParametersCount(operatorsStack);
            //jezeli na wierzcholku stosu sa operatory i w postfixie sa minimum 2 liczby
            while (isOperator(operatorsStack.top()[0]) && postfixStr.getSize() > 1) {
                postfixStr += operatorsStack.pop();
                adjustSpace(prevC, postfixStr, 1);
            }
            //np. N IF ( 1, 2, 3)
            while (!isOperator(c) && operatorsStack.top() == "N") { // && isFunction(postfixStr[postfixStr.getSize() - 1])
                postfixStr += operatorsStack.pop();
                adjustSpace(prevC, postfixStr, 1);
            }
            // MIN MAX
            while (operatorsStack.top()[0] == 'M') {
                int sizeOfFunction = lengthOfFunction(operatorsStack.top());
                postfixStr += operatorsStack.pop();
                adjustSpace(prevC, postfixStr, sizeOfFunction);
            }
        }
        else if (c != '.') //c != ','?
        {
            dotPostfix(operatorsStack, c, postfixStr, prevC);
        }

        if (postfixStr.getSize() > 0)
        {
            prevC = postfixStr[postfixStr.getSize() - 1];
        }
        //cout << "current: " << c << endl <<"stack: ";
        //operatorsStack.show();
        //cout << endl << postfixStr << endl;
    }

    while (!operatorsStack.isEmpty())
    {
        if (operatorsStack.top() != "(")
        {
            adjustSpace(prevC, postfixStr);
            postfixStr += operatorsStack.pop();
        }
        else
        {
            operatorsStack.pop();
        }
    }

    return postfixStr;
}

int calculatePostfix(MString postfixStr) {
    Stack<int> operands;

    for (int i = 0; i < postfixStr.getSize(); i++) {
        if (isdigit(postfixStr[i])) {
            MString num = "";
            while (i < postfixStr.getSize() && isdigit(postfixStr[i])) {
                num += postfixStr[i];
                if (i + 1 < postfixStr.getSize() && (!isdigit(postfixStr[i + 1]))) {
                    break;
                }
                i++;
            }
            operands.push(num.toNumber());
        }
        else if (isOperator(postfixStr[i])) {
            if (operands.size() > 1) {

                int a = operands.pop();
                int b = operands.pop();
                cout << postfixStr[i] << " " << a << " " << b << " ";
                operands.showReverse();
                cout << endl;
                int result = makeOperation(postfixStr[i], a, b);
                if (result == INT_MAX) {
                    return INT_MAX;
                }
                else {
                    operands.push(result);
                }
            }
        }
        else {
            if (!isFunction(postfixStr[i]))
            {
                continue;
            }
            if (postfixStr[i] == 'N') {
                int a = operands.pop();
                cout << postfixStr[i] << " " << a << " ";
                operands.showReverse();
                cout << endl;
                a *= -1;
                operands.push(a);
            }
            else if (postfixStr[i] == 'I') {
                i++;
                operands.push(applyIf(operands));
            }
            else if (postfixStr[i] == 'M') {
                //MIN MAX
                i += 3;

                MString numbers = "";
                while (isdigit(postfixStr[i])) {
                    numbers += postfixStr[i];
                    i++;
                }

                //czy muszę cofnąć i? czyli i--?

                int numberAmount = numbers.toNumber();
                MString fullFunctionName = postfixStr.substr(i - numbers.getSize() - 3, numbers.getSize() + 3);

                int lastCharInFunctionName = i - numbers.getSize() - 1;

                if (postfixStr[lastCharInFunctionName] == 'N') {
                    operands.push(applyMin(operands, fullFunctionName, numberAmount));
                }
                else if (postfixStr[lastCharInFunctionName] == 'X') {
                    operands.push(applyMax(operands, fullFunctionName, numberAmount));
                }
            }
        }
    }

    return operands.pop();

}

int main()
{
    int n;
    cin >> n;
    cin.ignore(1);

    while (n--) {

        MString postfix = infixToPostfix();
        cout << postfix << endl;

        int result = calculatePostfix(postfix);

        if (result == INT_MAX) {
            cout << endl;
            continue;
        }
        else {
            cout << result << endl;
        }

        cout << endl;
    }
    return 0;
}
