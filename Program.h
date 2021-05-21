//
//  Program.h
//  MinusMinusV3
//
//  Created by Tony Biehl on 2/10/21.
//  Copyright © 2021 Tony Biehl. All rights reserved.
//
/*
--------------------------------------------------
                      Program
--------------------------------------------------
 -progLine[SIZE]:string
 -functions:SymbolTable
 -lastToken:string
 -command:Command
 -size:integer
 -lineNumber:integer
 -line:string
 -errorCount:integer
--------------------------------------------------
 +loadProg(filename:string):bool // load the program using filename given. Return true if successful else false
 +operator=(lineNum:integer):void // goto lineNum
 +operator++():string // next line and return the command
 +operator-=(e:Extract):string // get next token
 +operator*=(c:Commands, p:Program):Commands // friend operator to get the command
 +operator*=(s:string, p:Program):string // friend operator to get the last token
 +operator*=(line:integer, p:Program):integer // friend operator to get the last item on stack
 +peek():integer // get a copy of top of stack
 +peek(v:string, localVars:SymbolTable):integer // get a copy of the value of local variable (localVars points to correct place)
 +pop():integer // pop last line from stack
 +push(line:integer):void // push current line onto stack
 +push(v:string, localVars:SymbolTable):void // push local variable space onto stack and add variable to localVars
 +setVar(v:string, val:integer, localVars:SymbolTable):void // set variable to value and use localVars to find place on stack
--------------------------------------------------
 */
#ifndef Program_h
#define Program_h

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "SymbolTable.h"
#include "Stack.h"

using namespace std;

enum Commands{ASSIGN, CALL, COMMENT, BLANK, DECLARE, ENDIF, ENDWHILE, ENDPROGRAM, FUNCTION, IF, INPUT,
    PRINT, PRINTLN, PROCEDURE, RETURN, UNKNOWN, WHILE
};
enum Extract{BOOLEAN, CMD, COMMA, COMPARE, EQUATION, LINE, PARMS, OPEN_PARM, STRING, TOKEN};
enum Trim{SPACES, QUOTE, PARENTHESIS, NO_TRIM};
const int SIZE = 500;

const char FUNCTION_ARG = '~';
// nextToken end characters
const char END_COMMA = ',';
const char END_LINE = '~';
const char END_COMPARE = '=';
const char END_PAREN = '(';
const char END_SPACE = ' ';
const char END_CMD = '^';

bool checkFirstChar(string s, char ch);
void chop(string& str, int x);

class Program
{
private:
    string progLine[SIZE];
    SymbolTable methods; // for the functions and procedures
    Stack<int> stack;
    string lastToken;
    Commands command;
    int size;
    int lineNumber;
    string line;
    int errorCount;
    
public:
    Program();
    bool addParmOffset(string parm, int offset, SymbolTable &localVars); // add the parameter to the local vars and attach the offset to the stack to it
    
    Commands convertLine(string &c); // convert the c string into Commands and chop off the command from c
    
    int countArguments(SymbolTable& localVars, string& s);
    bool errorMsg(string msg);
    int getLineNumber();
    int getErrorCount();
    bool getMethod(Symbol &);
    bool isOperator(string s);
    bool isValidID(string id);
    bool loadProg(ifstream& inFilr, bool list); // load the program using inFile given. Return true if successful else false
    void operator=(int lineNum); // goto lineNum
    Commands operator++(); // next line and return the command
    string operator-=(Extract e); // get next token
    bool operator==(string method); // see if valid function or procedure
    friend Commands& operator*=(Commands &c, Program &p); // friend operator to get the command
    friend string& operator*=(string &s, Program &p); // friend operator to get the last token
    friend int& operator*=(int &offset, Program &p); // friend operator to get the item on stack via offset
    string nextFactor(string& s);
    string nextToken(string &s, char endCH);

    int peek(); // get a copy of top of stack
    int peek(string v, SymbolTable &localVars); // get a copy of the value of local variable (localVars points to correct place on stack)
    int peek(int i); // know which offset on stack you want
    void poke(string v, int val, SymbolTable &localVars); // set variable to value and use localVars to find place on stack
    void pop(int x); // pop last x items from stack
    int precedence(string s);
    void push(int line); // push current line onto stack
    void push(string v, SymbolTable &localVars); // push local variable space onto stack and add variable to localVars

    void setLineNumber(int lineNum); // set the program line
    void trim(Trim t, string& s);
    void trimIt(string& s);
};

#endif /* Program_h */
