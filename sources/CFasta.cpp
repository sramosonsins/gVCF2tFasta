/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFasta.cpp
 * Author: jordi
 * 
 * Created on August 3, 2017, 12:11 PM
 */

#include "CFasta.h"

CFasta::CFasta(const std::string & file_name) : File(file_name) {
}

//CFasta::CFasta(const CFasta& orig) {
//}

//CFasta::~CFasta() {
//}

std::string CFasta::obtainSubSeq(std::string chrom, int pos_i, int pos_f) {

    char c;
    std::string line = "";
    int numberLines = 0;
    int numberNucleotides = 0;
    std::string correct_chrom = "";

    std::string subseq = "";

    while (!endFile()) {
        c = getFileChar();
        if (c == '\n') {
            if (line[0] == '>') {
                int n = line.find(chrom);
                if (n != std::string::npos) {
                    correct_chrom = chrom;
                    numberNucleotides = 0;
                } else {
                    correct_chrom = "";
                }
            }
            line = "";
        } else {
            line += c;
            if (correct_chrom != "") {
                numberNucleotides++;
                if (numberNucleotides >= pos_i && numberNucleotides <= pos_f) {
                    subseq += c;
                } else if(numberNucleotides > pos_f && correct_chrom == chrom){
                    break;
                }
            }
        }
    }

    return subseq;
    
}