/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFai.cpp
 * Author: jordi
 * 
 * Created on August 3, 2017, 5:03 PM
 */

#include "CFai.h"

CFai::CFai(const std::string & file_name) : File(file_name) {
}

//CFai::~CFai() {
//}

int CFai::chromosomeSize(std::string chromosome) {

    std::string linefai = "";
    char cf;
    int size;

    while (!endFile()) {
        cf = getFileChar();
        if (cf == '\n') {
            std::vector<std::string> failine = CStringTools::split(linefai, '\t');
            if (failine[0] == chromosome) {
                size = CStringTools::stringToInt(failine[1]);
                break;
            }
            linefai = "";
        } else {
            linefai += cf;
        }
    }
    
    return size;
}