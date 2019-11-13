/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFasta.h
 * Author: jordi
 *
 * Created on August 3, 2017, 12:11 PM
 */

#include "File.h"

#ifndef CFASTA_H
#define CFASTA_H

class CFasta : public File {
public:
    CFasta(const std::string & file_name);
    //CFasta(const CFasta& orig);
//    virtual ~CFasta();
    
    std::string obtainSubSeq(std::string chrom, int pos_i, int pos_f);
    
private:

};

#endif /* CFASTA_H */
