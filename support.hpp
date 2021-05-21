//
//  support.hpp
//  MinusMinusV3
//
//  Created by Tony Biehl on 2/13/21.
//  Copyright © 2021 Tony Biehl. All rights reserved.
//

#ifndef support_hpp
#define support_hpp

#include <iostream>
#include "Program.h"
#include "Stack.h"

bool load(Program &p);
int calculate(Program &p, Stack<string>& postFix, SymbolTable& local, bool& success);
bool compareBool(Program &p, SymbolTable& local);
int convertOperand(Program &p,string& s, SymbolTable& table, bool& success);
void execute(Program &p, SymbolTable &local, int line, int numParms);
int parseEquation(Program &p,string exp, SymbolTable& local, bool& success);
#endif /* support_hpp */
