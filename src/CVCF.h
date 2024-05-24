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
#include "CStringTools.h"
#include "File.h"
#include <htslib/vcf.h>
#include <htslib/hts.h>
#include <htslib/kseq.h>
#include "log.h"
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

class CVCF  {
public:

    //typedef enum tDataline {
    //    COMMENT = 1, HEADER = 2, DATA = 3, UNDEFINED = -1
    //};
    //tDataline type_;

    CVCF(const std::string & file_name);
    //CVCF(const CVCF& orig);
    virtual ~CVCF();
    std::string SetDataline(std::vector<std::string> vcfline);
    //int GetNumberSamples(std::vector<std::string> vcfline);
    //std::vector<std::string> GetNameSamples(std::vector<std::string> vcfline);
    std::string chromosome_;
    int position_;
    std::string allele_;
    int position_end_;
    std::list<SGenotype *> genotype_;
    int number_fields_;


    std::vector<std::string> samplenames_;
    int GetNumberSamples(void) {
        return samplenames_.size();
    }

    inline bool isSNP(void) {
        return (position_end_ == -1);
    }


    int is_vcf_sorted();
    bool openFile();
    bool closeFile();
    int getLine(std::string & line);
private:
    void init(void);
    std::string input_vcf_fname;
    htsFile *fp = NULL;
    bcf_hdr_t *hdr = NULL;
    kstring_t str = {0, 0, NULL};
    int len = 0;
};

#endif /* CVCF_H */
