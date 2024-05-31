/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CTFasta.h
 * Author: jordi
 *
 * Created on August 2, 2017, 3:05 PM
 */

#include <string>
#include "File.h"
#include <htslib/bgzf.h>

#ifndef CTFASTA_H
#define CTFASTA_H

class CTFasta  {
public:
    CTFasta(const std::string & file_name);
    bool openWriteFile(void);
    void closeFile(void);
    //virtual ~CTFasta();
    bool writeFile(std::string s);
    int count_alleles;
private:
    BGZF *output_fp;
    std::string tfasta_fname;
    
};

#endif /* CTFASTA_H */
