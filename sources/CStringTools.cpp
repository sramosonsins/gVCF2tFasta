/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CStringTools.cpp
 * Author: jordi
 * 
 * Created on June 17, 2016, 12:44 PM
 */

#include "CStringTools.h"

CStringTools::CStringTools() {
}

CStringTools::CStringTools(const CStringTools& orig) {
}

CStringTools::~CStringTools() {
}

std::vector<std::string> CStringTools::split(std::string text, char separator) {
    std::vector<std::string> elems;
    std::string param;
    if ((text != "") && (text[0] == separator)) {
        elems.push_back("");
    }
    // Mira la línea entera y a medida que encuentra el separador guarda lo de delante
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c == separator) {
            if (param != "") {
                elems.push_back(param); // Cuando encuentra el separador guarda la palabra previa
                param = "";
            }
        } else {
            param += c; // Guarda cada caracter diferente al separador
        }
    }
    if (param != "") {
        elems.push_back(param); // Guarda cada palabra entre los separadores como elementos del vector
        param = "";
    }
    return elems;
}

namespace patch {

    template < typename T > std::string to_string(const T& n) {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

std::string CStringTools::intToString(int number) {
    std::string s;
    s = patch::to_string(number);
    return s;
}

int CStringTools::stringToInt(std::string s) {
    int n;
    n = atoi(s.c_str());
    return n;
}
