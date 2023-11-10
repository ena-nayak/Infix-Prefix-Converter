#include <iostream>
#include <stack>
#include <string>

using namespace std;

//function signatures
int getPrecedence(char op);
bool isHigherPrecedence(char op1, char op2);
bool isEqualPrecedence(char op1, char op2);
bool isLowerPrecedence(char op1, char op2);
string reverseString(string infix);
string infixToPrefix(string s);
bool charOperator(char op);
string prefixToInfix(string s);

//helper function for infixToPrefix()
int getPrecedence(char op) 
{
  switch (op) 
  {
    case '*':
    case '/':
    case '%':
      return 5;
    case '+':
    case '-':
      return 6;
    case '^':
      return 12;
    case '(':
    case ')':
      return 2;
  }
  return -1;
}

//helper function for infixToPrefix()
bool isHigherPrecedence(char op1, char op2) 
{
  return (getPrecedence(op1) > getPrecedence(op2));
}

//helper function for infixToPrefix()
bool isEqualPrecedence(char op1, char op2) 
{
  return (getPrecedence(op1) == getPrecedence(op2));
}

//helper function for infixToPrefix()
bool isLowerPrecedence(char op1, char op2) 
{
  return (getPrecedence(op1) < getPrecedence(op2));
}

//helper function for infixToPrefix()
string reverseString(string infix) 
{
  string prefix(infix);
  for (int i = infix.size() - 1; i >= 0; i--) 
  {
    if (infix[i] == '(') 
    {
      prefix[infix.size() - i - 1] = ')';
    } 
    else if (infix[i] == ')') 
    {
      prefix[infix.size() - i - 1] = '(';
    } 
    else 
    {
      prefix[infix.size() - i - 1] = infix.at(i);
    }
  }

  return prefix;
}

//helper function for infixToPrefix()
string infixToPrefix(string s) 
{
  string mathOperators("+-*/%()^");
  stack < char > operatorsStack;
  string reverse = reverseString(s);
  string prefix(reverse);
  string pString = "";

  for (int i = 0; i < reverse.size(); i++) 
  {
    if (reverse[i] == ' ') 
    {
      continue;
    }
    if (mathOperators.find(reverse[i]) == string::npos) 
    {
      pString += reverse[i];
    } 
    else 
    {
      if (operatorsStack.empty()) 
      {
        operatorsStack.push(reverse[i]);
      } 
      else 
      {
        if (isHigherPrecedence(reverse[i], operatorsStack.top())) 
        {
          operatorsStack.push(reverse[i]);
        } 
        else if (isEqualPrecedence(operatorsStack.top(), reverse[i]) && reverse[i] == '^') 
        {
          while (!isHigherPrecedence(operatorsStack.top(), reverse[i]) && !isHigherPrecedence(reverse[i], operatorsStack.top())) 
          {
            pString += reverse[i];
            operatorsStack.pop();
          }

        } 
        else if (isEqualPrecedence(operatorsStack.top(), reverse[i])) 
        {
          operatorsStack.push(reverse[i]);
        } 
        else if (reverse[i] == ')') 
        {
          while (!operatorsStack.empty() && operatorsStack.top() != '(') 
          {
            pString += operatorsStack.top();
            operatorsStack.pop();
          }
          operatorsStack.pop();
        } 
        else if (reverse[i] == '(') 
        {
          operatorsStack.push(reverse[i]);
        } 
        else if (isLowerPrecedence(reverse[i], operatorsStack.top())) 
        {
          while (isLowerPrecedence(reverse[i], operatorsStack.top())) 
          {
            pString += operatorsStack.top();
            operatorsStack.pop();
          }
        }
      }

    }
  }
  while (!operatorsStack.empty()) 
  {
    pString += operatorsStack.top();
    operatorsStack.pop();
  }
  return reverseString(pString);
}

//helper function of infixToPrefix()
bool charOperator(char op) 
{
  if (op == '+' || op == '-' || op == '/' || op == '*' || op == '^' || op == '%') return true;

  else return false;
}

string prefixToInfix(string s) 
{
  stack < string > equation;
  string op1, op2, e;

  for (int i = s.size(); i >= 0; i--) 
  {
    if (charOperator(s[i])) 
    {
      op1 = equation.top();
      equation.pop();
      op2 = equation.top();
      equation.pop();

      e = op1 + s[i] + op2;
      equation.push(e);
    } 
    else 
    {
      equation.push(string(1, s[i]));
    }
  }
  return equation.top();
}

int main() 
{
  string infix;
  string prefix;
  char run, choice;

  cout << "Welcome!" << endl << "This program converts your equation from the infix to prefix notation, or vice versa." << endl << endl << "Would you like to try? Enter 'Y' for yes and 'N' for no" << endl;
  cin >> run;

  while (run == 'Y' || run == 'y') 
  {
    cout << endl << "Enter 'P' to convert from prefix to infix notation, or enter 'I' to convert from infix to prefix notation: ";
    cin >> choice;

    if (choice == 'p' || choice == 'P') 
    {
      cout << endl << "Enter an equation in the prefix notation: ";
      cin >> prefix;
      infix = prefixToInfix(prefix);
      cout << endl << "Infix version of prefix equation: " << infix;
    } 
    else 
    {
      cout << endl << "Enter an equation in the infix notation: ";
      cin >> infix;
      infix = infixToPrefix(infix);
      cout << endl << "Prefix version of infix equation: " << infix;
    }

    cout << endl << endl << "Would you like to run again? Enter 'Y' for yes and 'N' for no: ";
    cin >> run;
  }

  cout << endl << endl << "Goodbye...";

  return 0;
}