/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CVCF.h
 * Author: jordi
 *
 * Created on July 28, 2017, 2:32 PM
 */

#ifndef CVCF_H
#define CVCF_H

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "zutil.h"
#include "CStringTools.h"
#include "File.h"

#define DOT -2

/*struct SGenotype {
    int ref;
    int alt;

    SGenotype() {
        ref = -1;
        alt = -1;
    }
};*/
struct SGenotype {
    std::vector<int> geno;

    SGenotype() {
        std::vector<int> geno = {};
    }
};

class CVCF : public File {
public:

    //typedef enum tDataline {
    //    COMMENT = 1, HEADER = 2, DATA = 3, UNDEFINED = -1
    //};
    //tDataline type_;

    CVCF(const std::string & file_name);
    //CVCF(const CVCF& orig);
//    virtual ~CVCF();
    std::string SetDataline(std::vector<std::string> vcfline);
    int GetNumberSamples(std::vector<std::string> vcfline);
    std::vector<std::string> GetNameSamples(std::vector<std::string> vcfline);
    std::string chromosome_;
    int position_;
    std::string allele_;
    int position_end_;
    std::list<SGenotype *> genotype_;
    int number_fields_;
    std::vector<std::string> samplenames_;

    inline bool isSNP(void) {
        return (position_end_ == -1);
    }
private:
    void init(void);
};

#endif /* CVCF_H */
