/* 
 * File:   CFasta.cpp
 * Author: jordi
 * 
 * Created on August 3, 2017, 12:11 PM
 * last update on May 23, 2024 
 */

#include "CFasta.h"

// Function to check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
CFasta::CFasta(const std::string & file_name)  {
    fasta_fname = file_name;

}

/**
 * Opens the FASTA file for reading and performs necessary operations.
 * 
 * This function checks if the index file exists for the FASTA file. If the index file does not exist,
 * it creates the index file. Then, it loads the FASTA index and retrieves the number of sequences
 * and their lengths. The sequence names and lengths are stored in the `chromosomegroup` and `chromosomelength`
 * vectors respectively.
 * 
 * @return `true` if the FASTA file is opened and processed successfully, `false` otherwise.
 */
bool CFasta::openReadFile() {
    int build_fai = 0;
    // Construct the name of the index file
    char fai_filename[1024];
    snprintf(fai_filename, sizeof(fai_filename), "%s.fai", fasta_fname.c_str());

    // Check if the index file exists
    if (!file_exists(fai_filename)) {
        // printf("Index file %s does not exist. Creating index...\n", fai_filename);
        log_info("Index file %s does not exist. Creating index...", fasta_fname.c_str());
        
        if (( build_fai = fai_build(fasta_fname.c_str()) ) != 0) {
            //fprintf(stderr, "Failed to create FASTA index for: %s\n", fasta_fname.c_str());
            log_error("Failed to create FASTA index for: %s", fasta_fname.c_str());
            return false;
        }
    }

    // Load the FASTA index
    fai = fai_load(fasta_fname.c_str());
    if (!fai) {
        // fprintf(stderr, "Failed to load FASTA index for: %s\n", fasta_fname.c_str());
        log_error("Failed to load FASTA index for: %s", fasta_fname.c_str());
        return false;
    }
    // return fai;

     // Get the number of sequences
    int nseq = faidx_nseq(fai);
    if (nseq < 0) {
        // fprintf(stderr, "Failed to get the number of sequences from: %s\n", fasta_fname.c_str());
        log_error("Failed to get the number of sequences from: %s", fasta_fname.c_str());
        fai_destroy(fai);
        return false;
    }

    // printf("Number of sequences: %d\n", nseq);
    log_debug("Number of sequences: %d", nseq);

    // Iterate through sequence names and print their lengths
    for (int i = 0; i < nseq; i++) {
        const char *seq_name = faidx_iseq(fai, i);
        std::string seq_name_str = seq_name;
        chromosomegroup.push_back(seq_name_str);
        int seq_len = faidx_seq_len(fai, seq_name);
        if (seq_len < 0) {
            fprintf(stderr, "Failed to get the length of sequence: %s\n", seq_name);
            return false;
        }
        chromosomelength.push_back(seq_len);
        // printf("Sequence name: %s, Length: %d\n", seq_name, seq_len);
        log_debug("Sequence name: %s, Length: %d", seq_name, seq_len);
    }


    return true;
}
void CFasta::closeFile() {
    fai_destroy(fai);
    // clear the vectors
    chromosomegroup.clear();
    chromosomelength.clear();
    fai = NULL;

}
//CFasta::CFasta(const CFasta& orig) {
//}

//CFasta::~CFasta() {
//}

/**
 * Retrieves a subsequence from the FASTA file based on the given chromosome, start position, and end position.
 *
 * @param chrom The chromosome name.
 * @param pos_i The start position of the subsequence.
 * @param pos_f The end position of the subsequence.
 * @return The subsequence as a string.
 */
std::string CFasta::obtainSubSeq(std::string chrom, int pos_i, int pos_f) {

 

    std::string subseq = "";


    int seq_len;
    // const char *seq_name = faidx_iseq(fai, 0);

    // construct the region string
    std::string region = chrom + ":" + std::to_string(pos_i) + "-" + std::to_string(pos_f);

    char *seq = fai_fetch(fai, region.c_str(), &seq_len);
   
    subseq = seq;
    return subseq;
    
}