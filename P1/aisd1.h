#pragma once

void adjustSpace(char& prevC, MString& postfixStr, int number);

void readDigitAndAddToPostfix(char& c, MString& postfixStr, char& prevC);

void closingBracketPostfix(Stack<char>& operatorsStack, char& prevC, MString& postfixStr);

void dotPostfix(Stack<char>& operatorsStack, char c, MString& postfixStr, char& prevC);
