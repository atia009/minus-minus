# Minus Minus Project

By Aaron Tia and Julia Castro

## Prompt

Complete the parseEquation and execute functions.

The basic layout of the program is a main that loads then executes the program, Program.h and Program.cpp which has the MinusMinus program itself with routines for going through the program (more on that later), SymbolTable.h and SymbolTable.cpp for handling symbol tables for the functions and procedure and local variables (two separate tables), the utility of Stack.h and Stack.cpp, and the support.h and support.cpp. The support.cpp is the only file you need to submit. That’s where you will change the parseEquation and execute functions (they are skeletons for now).

With the execute function, remember it is emulation of one function or procedure at a time and needs to have passed to it a SymbolTable, any parameters and for functions a space on the stack of stk for return value. And if it needs to execute another function, have it create another SymbolTable and save the lineNum as a local variable and put any passed arguments onto the stack before recursively calling itself. Note: there are operations that aid in the handling of parameters. Look at the interpret function for an example

For the parseEquation, you need to convert an infix parseEquation into postfix. The following is pseudocode that works well for converting.

for (each character ch in the infix expression)

{

    switch (ch)

    {

        case operand:  // append operand to end of postfix expression

            postfixExp = postfixExp + ch

        case ‘(‘:          // save ‘(’ on stack

            operatorStack.push(ch)

            break

        case operator: // process stack operators of greater precedence

            while (!operatorStack.isEmpty and operatorStack.peek is not a ‘(’ and

                       precedence(ch <= precedence(operatorStack.peek()))

            {

                 Append operatorStack.peek() to the end of postfixExp

                 operatorStack.pop()

            }

            operatorStack.push(ch)   // save the operator

            break

        case ‘)’:          // pop stack util matching ‘(’

            while (operatorStack.peek() is not a ‘(’)

            {

                 Append operatorStack.peek() to the end of postfixExp

                 operatorStack.pop()

            }

            operatorStack.pop()     // remove open parenthesis

            break

    }

}

// append to postfixExp the operators remaining in the stack

while (!operatorStack.isEmpty())

{

    Append operatorStack.peek() to the end of postfixExp

    operatorStack.pop()

}

Note: for functions as part of an equation, the nextFactor will return the function call (complete with parameters) but put a “~” (tilde) in front for easy recognition. Need to call the parseEquation function for just that function call.

Remember to use the support routines and the variables in the Program class (especially lineNumber and stack).
