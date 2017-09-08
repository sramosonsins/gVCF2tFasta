/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on July 27, 2017, 10:59 AM
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
//#include <fstream>
#include <string>
//#include <vector>
//#include <map>
#include "zutil.h"
#include "zindex.h"
#include "CStringTools.h"
#include "CVCF.h"
#include "CFasta.h"
#include "CTFasta.h"
#include "CFai.h"
//#include "CDataline.h"
//#include "CFastaIndex.h"
//#include <sstream>

void help(std::string name) {
    std::cerr << "VCF2tFasta\n"
            << "Version 0.2\n"
            << "Usage: ./vcf2tfasta -v input.vcf -r reference.fa -o outputname -c chromosome(s)\n"
            << "Options:\n"
            << "\t-h\t\tHelp and exit\n"
            << "\t-v\t\tInput VCF file\n"
            << "\t-r\t\tReference Fasta file (it must be indexed with samtools faidx)\n"
            << "\t-o\t\tOutput compressed tFasta filename (without extension), it will be added the chromosome(s) of '-c' option in the final filename\n"
            << "\t-c\t\tChromosome(s) to convert (if there are more than one chromosome, they have to be separated by comma)\n"
            << std::endl;
}

void test(std::string tfasta, std::string refname, std::string chromosome) {
    FILE *h = 0;
    SGZip gz;

    h = fzopen(tfasta.c_str(), "r", &gz);

    CFai fai(refname + ".fai");

    int sizeChrom;

    // Obtenemos el tamaño del último cromosoma
    if (fai.openReadFile()) {
        sizeChrom = fai.chromosomeSize(chromosome);
        fai.closeFile();
    }

    std::string last_position_tfa = chromosome + ":" + CStringTools::intToString(sizeChrom);
    
    if (h != NULL) {

        struct SGZIndex idx;
        load_index_from_file(gz.index_file_name, &idx);

        long int row_num = -1; // Set to -1 if you want to search by ID.
        if (fzseek(h, &gz, &idx, last_position_tfa.c_str(), &row_num, false) == GZ_OK) { // Or set NULL to the ID if you want to seach by position.
            // After the call to fzseek, the row_num variable has the reached sequence number (0-based).
            // Set the last parameter to true (1) if you want to search from the last position found. It is faster.
            char ch = ' ';
            while ((!fzeof(h, &gz)) && (ch != '\n') && (ch != '\x0')) {
                ch = fzgetc(h, &gz);
                printf("%c", ch);
            }
        }

        unload_all_index_positions(&idx);

        fzclose(h, &gz);
    }
}

int main(int argc, char** argv) {

    /////////////////////////////
    // Argumentos del programa //
    /////////////////////////////

    std::string vcfname;
    std::string tfastaname;
    std::string tfastaext;
    std::string refname;
    std::string chromgroup;

    char tmp;
    if (argc == 1) {
        help(argv[0]);
        exit(1);
    }

    while ((tmp = getopt(argc, argv, "hv:r:o:c:")) != -1) {
        switch (tmp) {
            case 'h':
                help(argv[0]);
		return 0;
                break;
            case 'v':
                vcfname = std::string(optarg);
                break;
            case 'r':
                refname = std::string(optarg);
                break;
            case 'o':
                tfastaname = std::string(optarg);
                break;
            case 'c':
                chromgroup = std::string(optarg);
                break;
        }
    }
    if (vcfname == "") {
        // Si no se da ningun VCF en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tVCF file not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    if (refname == "") {
        // Si no se da ningun fasta de referencia en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tReference fasta file not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    if (tfastaname == "") {
        // Si no se da ningun nombre para el output en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tOutput tFasta file name not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    if (chromgroup == "") {
        // Si no se da ningun cromosoma en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tChromosome(s) name not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    std::cout << std::endl;
    std::cout << "VCF file: " << vcfname << std::endl;
    std::cout << "Reference Fasta file: " << refname << std::endl;
    tfastaext = tfastaname + "_" + chromgroup + ".tfa.gz";
    std::cout << "tFasta file: " << tfastaext << std::endl;
    std::cout << "Chromosome(s): " << chromgroup << std::endl;
    std::cout << std::endl;

    std::vector<std::string> chromosomegroup = CStringTools::split(chromgroup, ',');

    CVCF vcf(vcfname);
    CTFasta tfasta(tfastaext);
    CFasta fasta(refname);
    CFai fai(refname + ".fai");

    // Clasificamos las lineas del VCF:

    /*typedef enum tDataline {
        COMMENT = 1, HEADER = 2, DATA = 3, UNDEFINED = -1
    };
    tDataline type_line;*/

    std::string chromosome = "";
    char c;
    std::string line = "";
    std::vector<std::string> samplenames = {};
    int nsamples = 0;
    int sizeChrom;
    std::string lineVCF = "";
    int block;
    int snppos;
    int indelpos;
    std::string chromVCF = "";
    std::string pos;
    int pos_f = 0;
    std::string nts;
    std::string subseq = "";
    std::string linetfasta = "";
    int counter;
    std::string current_chromosome;
    int current_position;
    bool start_vcf = true;
    int count_alleles;

    // Create the tFasta file:
    if (tfasta.openWriteFile()) {
        if (vcf.openReadFile()) {
            while (!vcf.endFile()) {
                c = vcf.getFileChar();
                if (c == '\n') {
                    if (line[0] == '#') {
                        if (line[1] == 'C' && line[2] == 'H' && line[3] == 'R' && line[4] == 'O' && line[5] == 'M') {
                            // If the line is the Header:
                            //type_line = tDataline::HEADER;

                            // Dividimos la linea por columnas:
                            std::vector<std::string> vcfline = CStringTools::split(line, '\t');

                            // Obtenemos el nombre de los individuos:
                            samplenames = vcf.GetNameSamples(vcfline);

                            // Obtenemos el numero total de individuos:
                            nsamples = vcf.GetNumberSamples(vcfline);
                            std::cout << "Number of samples: " << nsamples << std::endl;

                            break;
                        }
                    }
                    line = "";
                } else {
                    line += c;
                }
            }
            vcf.closeFile();
        }

        //Por cada cromosoma indicado como argumento del programa:
        for (std::vector<int>::size_type i = 0; i < chromosomegroup.size(); i++) {
            chromosome = chromosomegroup[i];
            // Open the VCF file:
            if (vcf.openReadFile()) {

                line = "";
                current_chromosome = "";
                current_position = 0;

                // Obtenemos el tamaño del cromosoma en el que estamos:
                if (fai.openReadFile()) {
                    sizeChrom = fai.chromosomeSize(chromosome);
                    fai.closeFile();
                } else {
                    std::cout << std::endl;
                    std::cout << "Error:" << std::endl;
                    std::cout << "\tIndex file of reference fasta not found '" << refname << ".fai'" << std::endl;
                    std::cout << "\tExample: samtools faidx " << refname << std::endl;
                    std::cout << std::endl;
                    return 1;
                }

                // Analizamos cada línea del VCF para obtener la secuencia correspondiente del tFasta:
                while (!vcf.endFile()) {
                    c = vcf.getFileChar();
                    if (c == '\n') {
                        if (line[0] != '#') {
                            // If the line is a dataline (SNP, INDEL or Homozygous block):
                            //type_line = tDataline::DATA;

                            // Dividimos la linea por columnas:
                            std::vector<std::string> vcfline = CStringTools::split(line, '\t');

                            // Si estamos en la primera linea, escribimos primero el header (hasta aqui no lo hace para saber cuantos alelos hay por muestra):
                            if ((start_vcf == true) && (current_position == 0)) {
                                count_alleles = 0;
                                for (int n = 0; n < vcfline[9].size(); n++) {
                                    if ((vcfline[9][n] == '/') || (vcfline[9][n] == '|')) {
                                        count_alleles++;
                                    }
                                }
                                count_alleles++;

                                std::string samplenames_alleles;
                                for (int s = 0; s < samplenames.size(); s++) {
                                    for (int m = 0; m < count_alleles; m++) {
                                        if (samplenames_alleles == "") {
                                            samplenames_alleles = samplenames[s] + "_" + CStringTools::intToString(m);
                                        } else {
                                            samplenames_alleles = samplenames_alleles + "\t" + samplenames[s] + "_" + CStringTools::intToString(m);
                                        }
                                    }
                                }

                                std::string header =
                                        "#vcf2tfasta -v " + vcfname + " -r " + refname + " -o " + tfastaext + " -c " + chromgroup + "\n" +
                                        "#NAMES: " + samplenames_alleles + "\n" +
                                        "#CHROMOSOME:POSITION" + "\t" + "GENOTYPES" + "\n";
                                tfasta.writeFile(header);
                            }
                            start_vcf = false;

                            if (vcfline[0] == chromosome) {
                                // Si el cromosoma de la dataline corresponde al cromosoma actual:

                                current_chromosome = chromosome;

                                // Obtenemos los campos deseados de la dataline:
                                lineVCF = vcf.SetDataline(vcfline);
                                std::vector<std::string> dline = CStringTools::split(lineVCF, '\t');
                                chromVCF = dline[0];
                                pos = dline[1];
                                nts = dline[2];

                                // Si el cromosoma de la dataline corresponde al cromosoma actual:
                                if (CStringTools::stringToInt(pos) > (current_position + 1)) {
                                    // Si la posicion de la dataline es mayor a la posición siguiente de la anterior dataline, escribimos las posiciones intermedias con Ns (missing data):
                                    for (int n = (current_position + 1); n < CStringTools::stringToInt(pos); n++) {
                                        std::string nucleotides = "";

                                        linetfasta = chromVCF + ":" + CStringTools::intToString(n) + "\t";
                                        /*for (int s = 0; s < nsamples; s++) {
                                            nucleotides = nucleotides + "NN";
                                        }*/
                                        for (int s = 0; s < nsamples; s++) {
                                            for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                nucleotides = nucleotides + "N";
                                            }
                                        }
                                        linetfasta = linetfasta + nucleotides + "\n";
                                        tfasta.writeFile(linetfasta);
                                    }
                                }
                                // Determinamos si la dataline corresponde a un SNP, un bloque homocigoto o un indel (lo comprueba la funcion SetDataline)
                                snppos = lineVCF.find("SNP");
                                block = lineVCF.find("ROH");
                                indelpos = lineVCF.find("INDEL");

                                if (snppos != std::string::npos) {
                                    // Si la linea del VCF corresponde a un SNP:

                                    linetfasta = chromVCF + ":" + pos + "\t" + nts + "\n";
                                    tfasta.writeFile(linetfasta);

                                    current_position = CStringTools::stringToInt(pos);

                                } else if (block != std::string::npos) {
                                    // Si la linea del VCF corresponde a un Bloque Homocigoto:
                                    pos_f = CStringTools::stringToInt(dline[4]);

                                    // Obtenemos la secuencia correspondiente al bloque a partir del Fasta de referencia:
                                    if (fasta.openReadFile()) {
                                        subseq = fasta.obtainSubSeq(chromVCF, CStringTools::stringToInt(pos), pos_f);
                                        fasta.closeFile();
                                    }

                                    counter = 0;
                                    // Imprimimos la secuencia en formato tFasta:
                                    for (int n = CStringTools::stringToInt(pos); n <= pos_f; n++) {
                                        std::string nucleotides = "";

                                        linetfasta = chromVCF + ":" + CStringTools::intToString(n) + "\t";

                                        /*for (int s = 0; s < nsamples; s++) {
                                            if (nts[s] == 'R') {
                                                nucleotides = nucleotides + subseq[counter] + subseq[counter];
                                            } else if (nts[s] == 'M') {
                                                nucleotides = nucleotides + "NN";
                                            }
                                        }*/
                                        for (int s = 0; s < nsamples; s++) {
                                            for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                if (nts[i] == 'R') {
                                                    nucleotides = nucleotides + subseq[counter];
                                                } else if (nts[i] == 'M') {
                                                    nucleotides = nucleotides + "N";
                                                }
                                            }
                                        }

                                        linetfasta = linetfasta + nucleotides + "\n";
                                        tfasta.writeFile(linetfasta);
                                        counter++;
                                    }

                                    current_position = pos_f;

                                } else if (indelpos != std::string::npos) {
                                    // Si la linea del VCF corresponde a un INDEL, ponemos Ns como si fuera missing data:

                                    linetfasta = chromVCF + ":" + pos + "\t" + nts + "\n";
                                    tfasta.writeFile(linetfasta);

                                    current_position = CStringTools::stringToInt(pos);
                                }
                            } else {
                                // Si el cromosoma de la dataline no corresponde al cromosoma actual:
                                if (current_chromosome != "") {
                                    // Si ya previamente había otro cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del anterior cromosoma
                                    for (int n = (current_position + 1); n <= sizeChrom; n++) {
                                        std::string nucleotides = "";

                                        linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";
                                        /*for (int s = 0; s < nsamples; s++) {
                                            nucleotides = nucleotides + "NN";
                                        }*/
                                        for (int s = 0; s < nsamples; s++) {
                                            for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                nucleotides = nucleotides + "N";
                                            }
                                        }
                                        linetfasta = linetfasta + nucleotides + "\n";
                                        tfasta.writeFile(linetfasta);
                                    }
                                    current_position = sizeChrom;
                                }
                            }
                        }
                        line = "";
                    } else {
                        line += c;
                    }
                }
                if (vcf.endFile()) {
                    //Si llegamos al final del VCF:
                    if (current_chromosome != "") {
                        // Si ya previamente había algun cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del este cromosoma
                        for (int n = (current_position + 1); n <= sizeChrom; n++) {
                            std::string nucleotides = "";

                            linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";
                            /*for (int s = 0; s < nsamples; s++) {
                                nucleotides = nucleotides + "NN";
                            }*/
                            for (int s = 0; s < nsamples; s++) {
                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                    nucleotides = nucleotides + "N";
                                }
                            }
                            linetfasta = linetfasta + nucleotides + "\n";
                            tfasta.writeFile(linetfasta);
                        }
                        current_position = sizeChrom;
                    } else {
                        // Si no había ninguna linea en el VCF correspondiente al cromosoma actual, se escribe el cromosoma entero con Ns.
                        for (int n = 1; n <= sizeChrom; n++) {
                            std::string nucleotides = "";

                            linetfasta = chromosome + ":" + CStringTools::intToString(n) + "\t";
                            /*for (int s = 0; s < nsamples; s++) {
                                nucleotides = nucleotides + "NN";
                            }*/
                            for (int s = 0; s < nsamples; s++) {
                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                    nucleotides = nucleotides + "N";
                                }
                            }
                            linetfasta = linetfasta + nucleotides + "\n";
                            tfasta.writeFile(linetfasta);
                        }
                        current_position = sizeChrom;
                    }
                }
                vcf.closeFile();
            }
        }
        tfasta.closeFile();
    }

    //test(tfastaext,refname,chromosome);

    return 0;
}

