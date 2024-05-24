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
#include <vector>
#include <string>
#include <htslib/faidx.h>
#include <htslib/hts.h>
#include "log.h"

#ifndef CFASTA_H
#define CFASTA_H

class CFasta   {
public:
    CFasta(const std::string & file_name);
    //CFasta(const CFasta& orig);
//    virtual ~CFasta();
    
    std::string obtainSubSeq(std::string chrom, int pos_i, int pos_f);
    bool openReadFile();
    void closeFile();
    std::vector<std::string> chromosomegroup = {};
    std::vector<int> chromosomelength = {};
private:
    std::string fasta_fname;
    faidx_t *fai;
};

#endif /* CFASTA_H */
