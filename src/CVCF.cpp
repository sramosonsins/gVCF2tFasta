/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CVCF.cpp
 * Author: jordi
 * 
 * Created on July 28, 2017, 2:32 PM
 */

#include "CVCF.h"

CVCF::CVCF(const std::string & file_name) : File(file_name) {
    init();
}

void CVCF::init(void) {
    chromosome_ = "";
    position_ = -1; // The first possible position is equal to 1
    allele_ = "";
    position_end_ = -1;
    //type_ = tDataline::UNDEFINED;
    number_fields_ = 0;
    samplenames_ = {};
    for (std::list<SGenotype *>::iterator i = genotype_.begin(); i != genotype_.end(); i++) {
        delete *i;
    }
    genotype_.clear();

}

//CVCF::CVCF(const CVCF& orig) {
//}

//CVCF::~CVCF() {
//    init();
//}

std::string CVCF::SetDataline(std::vector<std::string> vcfline) {

    init();

    std::string dataline;
    std::string type_data = "";
    std::string nucleotides;

    chromosome_ = vcfline[0];
    position_ = CStringTools::stringToInt(vcfline[1]);
    allele_ = vcfline[3];
    std::vector<std::string> tmp = CStringTools::split(vcfline[4], ',');
    for (int i = 0; i < tmp.size(); i++) {
        allele_ += tmp[i];
    }

    int pos = vcfline[7].find("END=");
    int indel = vcfline[7].find("INDEL");
    int sv = vcfline[7].find("SV");

    if (indel != std::string::npos) {
        type_data = "INDEL";
        position_end_ = 0;
    } else if (sv != std::string::npos) {
        type_data = "INDEL";
        position_end_ = 0;
    } else if (pos != std::string::npos) {
        type_data = "BLOCK";
        position_end_ = CStringTools::stringToInt(vcfline[7].substr(pos + 4, vcfline[7].find(";", pos))); // 4 is the size of "END=", until it finds ";"
    } else {
        type_data = "SNP";
    }

    // Creamos una estructura SGenotype para cada línea con el genotipo sin separador (00,01,11...)
    SGenotype *new_genotype = NULL;
    char separator = '/';
    for (int i = 9; i < vcfline.size(); i++) {
        new_genotype = new SGenotype();

        std::vector<std::string> gt0 = CStringTools::split(vcfline[i], ':');

        separator = '/';
        std::string::size_type loc = gt0[0].find(separator, 0);
        if (loc == std::string::npos) {
            separator = '|';
            loc = gt0[0].find(separator, 0);
        }
        std::vector<std::string> gt = CStringTools::split(gt0[0], separator);

        for (int i = 0; i < gt.size(); i++) {
            if ((gt[i] == ".") || (gt[i] == ".\r")) {
                new_genotype->geno.push_back(DOT);
            } else {
                new_genotype->geno.push_back(CStringTools::stringToInt(gt[i])); // convert number(string) to number(int)
            }
        }
        /*if (gt.size() == 2) {
            if (gt[0] == ".") {
                new_genotype->ref = DOT;
            } else {
                new_genotype->ref = CStringTools::stringToInt(gt[0]); // convert number(string) to number(int)
            }
            if (gt[1] == ".") {
                new_genotype->alt = DOT;
            } else {
                new_genotype->alt = CStringTools::stringToInt(gt[1]); // convert number(string) to number(int)
            }
        } else {
            std::cout << std::endl;
            std::cout << "Error:" << std::endl;
            std::cout << "\tFormat error in VCF file (genotype fields):" << std::endl;
            std::cout << "\t\tChromosome: " << chromosome_ << std::endl;
            std::cout << "\t\tPosition: " << position_ << std::endl;
            std::cout << std::endl;
            //return 1;
        }*/

        genotype_.push_back(new_genotype);
    }
    if (type_data == "SNP") {
        // Si es un SNP, se escribe el nucleotido que toque segun el genotipo
        nucleotides = "";
        for (std::list<SGenotype *>::iterator i = genotype_.begin(); i != genotype_.end(); i++) {
            /*if ((*i)->ref == DOT && (*i)->alt == DOT) {
                nucleotides = nucleotides + "NN";
            } else {
                nucleotides = nucleotides + allele_[(*i)->ref] + allele_[(*i)->alt];
            }*/
            for (int j = 0; j < ((*i)->geno).size(); j++) {
                if ((*i)->geno[j] == DOT) {
                    nucleotides = nucleotides + "N";
                } else {
                    nucleotides = nucleotides + allele_[(*i)->geno[j]];
                }
            }
        }
        dataline = chromosome_ + "\t" + CStringTools::intToString(position_) + "\t" + nucleotides + "\t" + "SNP";
    } else if (type_data == "BLOCK") {
        // Si es un BLOQUE HOMOCIGOTO, se escribe los mismo nucleotidos que en el genoma de referencia hasta la posicion END
        for (std::list<SGenotype *>::iterator i = genotype_.begin(); i != genotype_.end(); i++) {
            /*if ((*i)->ref == DOT && (*i)->alt == DOT) {
                nucleotides = nucleotides + "M";
            } else {
                nucleotides = nucleotides + "R";
            }*/
            for (int j = 0; j < ((*i)->geno).size(); j++) {
                if ((*i)->geno[j] == DOT) {
                    nucleotides = nucleotides + "M";
                } else {
                    nucleotides = nucleotides + "R";
                }
            }
        }
        dataline = chromosome_ + "\t" + CStringTools::intToString(position_) + "\t" + nucleotides + "\t" + "ROH" + "\t" + CStringTools::intToString(position_end_);
    } else if (type_data == "INDEL") {
        // Si es un INDEL, se escribe Ns (como si fuera missing data)
        nucleotides = "";
        for (std::list<SGenotype *>::iterator i = genotype_.begin(); i != genotype_.end(); i++) {
            //nucleotides = nucleotides + "NN";
            for (int j = 0; j < ((*i)->geno).size(); j++) {
                nucleotides = nucleotides + "N";
            }
        }
        dataline = chromosome_ + "\t" + CStringTools::intToString(position_) + "\t" + nucleotides + "\t" + "INDEL";
    }

    return dataline;
}

int CVCF::GetNumberSamples(std::vector<std::string> vcfline) {

    number_fields_ = vcfline.size();
    return (number_fields_ - 9);

}

std::vector<std::string> CVCF::GetNameSamples(std::vector<std::string> vcfline) {

    number_fields_ = vcfline.size();
    for (int i = 9; i < number_fields_; i++) {
        samplenames_.push_back(vcfline[i]);
        /*if (samplenames_ == "") {
            samplenames_ = vcfline[i];
        } else {
            samplenames_ = samplenames_ + "\t" + vcfline[i];
        }*/
    }
    return (samplenames_);
}