/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFai.h
 * Author: jordi
 *
 * Created on August 3, 2017, 5:03 PM
 */

#include "File.h"
#include "CStringTools.h"

#ifndef CFAI_H
#define CFAI_H

class CFai : public File {
public:
    CFai(const std::string & file_name);
    //virtual ~CFai();
    int chromosomeSize(std::string chromosome);
private:

};

#endif /* CFAI_H */
