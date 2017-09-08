/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CStringTools.h
 * Author: jordi
 *
 * Created on June 17, 2016, 12:44 PM
 */

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

#ifndef CSTRINGTOOLS_H
#define CSTRINGTOOLS_H

class CStringTools {
public:
    CStringTools();
    CStringTools(const CStringTools& orig);
    virtual ~CStringTools();
    static std::vector<std::string> split(std::string text, char separator);    // Lo ponemos static para no tener que crear un objeto CStringTool en main.cpp
    static std::string intToString(int number);
    static int stringToInt(std::string s);
private:

};

#endif /* CSTRINGTOOLS_H */

