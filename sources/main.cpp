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
#include <string>
#include "zutil.h"
#include "zindex.h"
#include "CStringTools.h"
#include "CVCF.h"
#include "CFasta.h"
#include "CTFasta.h"
#include "CFai.h"

void help(std::string name) {
    std::cerr << "VCF2tFasta\n"
            << "Version 0.2\n"
            << "Usage: ./gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -o outputname -n chromosomes.txt\n"
            << "Structural Variants are considered as missing data (N)\n"
            << "Options:\n"
            << "\t-h\t\tHelp and exit\n"
            << "\t-v\t\tInput VCF file\n"
            << "\t-r\t\tReference Fasta file\n"
            << "\t-o\t\tOutput compressed tFasta filename (without extension)\n"
            << "\t-n\t\tFile with chromosome(s) to convert and its length\n"
            << "\t-i\t\tImputation (Only use with VCF files, not gVCF files):\n"
            << "\t\t\t\t0 if missing data in VCF is equal to N in tFasta\n"
            << "\t\t\t\t1 if missing data in VCF is equal to reference fasta in tFasta\n"
            << "\t\t\t\tDefault value is 0\n"
            << std::endl;
}

/*void test(std::string tfasta, std::string refname, std::string chromosome) {
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
}*/

int main(int argc, char** argv) {

    /////////////////////////////
    // Argumentos del programa //
    /////////////////////////////

    std::string vcfname;
    std::string tfastaname;
    std::string tfastaext;
    std::string refname;
    std::string chromname;
    std::string imputation;

    char tmp;
    if (argc == 1) {
        help(argv[0]);
        exit(1);
    }

    while ((tmp = getopt(argc, argv, "hv:r:o:n:i:")) != -1) {
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
            case 'n':
                chromname = std::string(optarg);
                break;
            case 'i':
                imputation = std::string(optarg);
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
    if (chromname == "") {
        // Si no se da ningun cromosoma en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tFile with chromosomes and lengths not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    if (imputation == "") {
        imputation = "0";
    }
    std::cout << std::endl;
    std::cout << "VCF file: " << vcfname << std::endl;
    std::cout << "Reference Fasta file: " << refname << std::endl;
    tfastaext = tfastaname + ".tfa.gz";
    std::cout << "tFasta file: " << tfastaext << std::endl;
    std::cout << "File with chromosomes and length: " << chromname << std::endl;
    if (imputation == "0") {
        //std::cout << "Imputation: True" << std::endl;
    } else if (imputation == "1") {
        std::cout << "Imputation: True" << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tIncorrect imputation value (different to 0 or 1)" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    std::cout << std::endl;

    CVCF vcf(vcfname);
    CTFasta tfasta(tfastaext);
    CFasta fasta(refname);
    CFai fai(chromname);

    std::vector<std::string> chromosomegroup = {};
    std::vector<std::string> chromosomelength = {};
    std::string chromosome = "";
    std::string chromfai = "";
    std::string lengthfai = "";
    char c;
    std::string line = "";
    std::string linefai = "";
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

    if (fai.openReadFile()) {
        linefai = "";
        while (!fai.endFile()) {
            c = fai.getFileChar();
            if (c == '\n') {
                // Dividimos la linea por columnas y obtenemos el cromosoma:
                std::vector<std::string> failine = CStringTools::split(linefai, '\t');
                chromfai = failine[0];
                chromosomegroup.push_back(chromfai);
                lengthfai = failine[1];
                chromosomelength.push_back(lengthfai);

                linefai = "";
            } else {
                linefai += c;
            }
        }
        fai.closeFile();
    } else {
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tIndex file of reference fasta not found '" << refname << ".fai'" << std::endl;
        std::cout << "\tExample: samtools faidx " << refname << std::endl;
        std::cout << std::endl;
        return 1;
    }

    // Create the tFasta file:
    if (tfasta.openWriteFile()) {
        if (vcf.openReadFile()) {
            while (!vcf.endFile()) {
                c = vcf.getFileChar();
                if (c == '\n') {
                    if (line[0] == '#') {
                        if (line[1] == 'C' && line[2] == 'H' && line[3] == 'R' && line[4] == 'O' && line[5] == 'M') {
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
            sizeChrom = CStringTools::stringToInt(chromosomelength[i]);
            // Open the VCF file:
            if (vcf.openReadFile()) {

                line = "";
                current_chromosome = "";
                current_position = 0;

                // Analizamos cada línea del VCF para obtener la secuencia correspondiente del tFasta:
                while (!vcf.endFile()) {
                    c = vcf.getFileChar();
                    if (c == '\n') {
                        if (line[0] != '#') {
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
                                            samplenames_alleles = ">" + samplenames[s] + "_" + CStringTools::intToString(m);
                                        } else {
                                            samplenames_alleles = samplenames_alleles + "\t" + ">" + samplenames[s] + "_" + CStringTools::intToString(m);
                                        }
                                    }
                                }

                                std::string header =
                                        "#vcf2tfasta -v " + vcfname + " -r " + refname + " -o " + tfastaext + " -n " + chromname + "\n" +
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
                                    if (imputation == "0") {
                                        // Si imputation = 0, el missing data se escribe como N
                                        // Si la posicion de la dataline es mayor a la posición siguiente de la anterior dataline, escribimos las posiciones intermedias con Ns (missing data):
                                        for (int n = (current_position + 1); n < CStringTools::stringToInt(pos); n++) {
                                            std::string nucleotides = "";

                                            linetfasta = chromVCF + ":" + CStringTools::intToString(n) + "\t";

                                            for (int s = 0; s < nsamples; s++) {
                                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                    nucleotides = nucleotides + "N";
                                                }
                                            }
                                            linetfasta = linetfasta + nucleotides + "\n";
                                            tfasta.writeFile(linetfasta);
                                        }
                                    } else if (imputation == "1") {
                                        // Si imputation = 1, el missing data del VCF es igual al nucleotido de referencia
                                        if (fasta.openReadFile()) {
                                            subseq = fasta.obtainSubSeq(chromVCF, (current_position + 1), CStringTools::stringToInt(pos));
                                            fasta.closeFile();
                                        }
                                        counter = 0;
                                        for (int n = (current_position + 1); n < CStringTools::stringToInt(pos); n++) {
                                            std::string nucleotides = "";

                                            linetfasta = chromVCF + ":" + CStringTools::intToString(n) + "\t";

                                            for (int s = 0; s < nsamples; s++) {
                                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                    nucleotides = nucleotides + subseq[counter];
                                                }
                                            }
                                            linetfasta = linetfasta + nucleotides + "\n";
                                            tfasta.writeFile(linetfasta);
                                            counter++;
                                        }
                                    }
                                }
                                // Determinamos si la dataline corresponde a un SNP, un bloque homocigoto o un indel (lo comprueba la funcion SetDataline)
                                snppos = lineVCF.find("SNP");
                                block = lineVCF.find("ROH");
                                indelpos = lineVCF.find("INDEL");

                                if (CStringTools::stringToInt(pos) != current_position) {
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
                                }
                            } else {
                                // Si el cromosoma de la dataline no corresponde al cromosoma actual:
                                if (current_chromosome != "") {
                                    if (imputation == "0") {
                                        // Si imputation = 0, el missing data se escribe como N
                                        // Si ya previamente había otro cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del anterior cromosoma
                                        for (int n = (current_position + 1); n <= sizeChrom; n++) {
                                            std::string nucleotides = "";

                                            linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";

                                            for (int s = 0; s < nsamples; s++) {
                                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                    nucleotides = nucleotides + "N";
                                                }
                                            }
                                            linetfasta = linetfasta + nucleotides + "\n";
                                            tfasta.writeFile(linetfasta);
                                        }
                                    } else if (imputation == "1") {
                                        // Si imputation = 1, el missing data del VCF es igual al nucleotido de referencia
                                        if (fasta.openReadFile()) {
                                            subseq = fasta.obtainSubSeq(current_chromosome, (current_position + 1), sizeChrom);
                                            fasta.closeFile();
                                        }
                                        counter = 0;
                                        // Si ya previamente había otro cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del anterior cromosoma
                                        for (int n = (current_position + 1); n <= sizeChrom; n++) {
                                            std::string nucleotides = "";

                                            linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";

                                            for (int s = 0; s < nsamples; s++) {
                                                for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                                    nucleotides = nucleotides + subseq[counter];
                                                }
                                            }
                                            linetfasta = linetfasta + nucleotides + "\n";
                                            tfasta.writeFile(linetfasta);
                                            counter++;
                                        }
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
                    if (imputation == "0") {
                        if (current_chromosome != "") {
                            // Si ya previamente había algun cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del este cromosoma
                            for (int n = (current_position + 1); n <= sizeChrom; n++) {
                                std::string nucleotides = "";

                                linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";

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
                    } else if (imputation == "1") {
                        if (current_chromosome != "") {
                            // Si ya previamente había algun cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del este cromosoma
                            if (fasta.openReadFile()) {
                                subseq = fasta.obtainSubSeq(current_chromosome, (current_position + 1), sizeChrom);
                                fasta.closeFile();
                            }
                            counter = 0;
                            for (int n = (current_position + 1); n <= sizeChrom; n++) {
                                std::string nucleotides = "";

                                linetfasta = current_chromosome + ":" + CStringTools::intToString(n) + "\t";

                                for (int s = 0; s < nsamples; s++) {
                                    for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                        nucleotides = nucleotides + subseq[counter];
                                    }
                                }
                                linetfasta = linetfasta + nucleotides + "\n";
                                tfasta.writeFile(linetfasta);
                                counter++;
                            }
                            current_position = sizeChrom;
                        } else {
                            // Si no había ninguna linea en el VCF correspondiente al cromosoma actual, se escribe el cromosoma entero con Ns.
                            if (fasta.openReadFile()) {
                                subseq = fasta.obtainSubSeq(chromosome, 1, sizeChrom);
                                fasta.closeFile();
                            }
                            counter = 0;
                            for (int n = 1; n <= sizeChrom; n++) {
                                std::string nucleotides = "";

                                linetfasta = chromosome + ":" + CStringTools::intToString(n) + "\t";

                                for (int s = 0; s < nsamples; s++) {
                                    for (int i = s * count_alleles; i < (s * count_alleles) + count_alleles; i++) {
                                        nucleotides = nucleotides + subseq[counter];
                                    }
                                }
                                linetfasta = linetfasta + nucleotides + "\n";
                                tfasta.writeFile(linetfasta);
                                counter++;
                            }
                            current_position = sizeChrom;
                        }
                    }
                }
                vcf.closeFile();
            }
        }
        tfasta.closeFile();
    }

    return 0;
}
