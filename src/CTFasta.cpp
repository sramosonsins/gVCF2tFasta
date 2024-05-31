/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CTFasta.cpp
 * Author: jordi
 * 
 * Created on August 2, 2017, 3:05 PM
 */

#include "CTFasta.h"
#include "log.h"
#include <iostream>
#include <htslib/tbx.h>

CTFasta::CTFasta(const std::string & file_name)  {
    tfasta_fname = file_name;
}

bool CTFasta::openWriteFile(void)
{
    // open file
    // tfasta_fname = "test.fasta";
    output_fp = bgzf_open(tfasta_fname.c_str(), "w");
    if (!output_fp)
    {
        log_error("Failed to open output file %s\n", tfasta_fname.c_str());
        return 0;
    }
    // Write the TFAv2.0 header to the output file
    const char *v2_header = "##fileformat=TFAv2.0\n";
    if (bgzf_write(output_fp, v2_header, strlen(v2_header)) < 0)
    {
        log_error("Error writing to the output file\n");
        bgzf_close(output_fp);
        return 0;
    }
    return 1;
}

bool CTFasta::writeFile(std::string s){
    if (bgzf_write(output_fp, s.c_str(), s.size()) < 0)
    {
        log_error("Error writing to the output file\n");
        bgzf_close(output_fp);
        return false;
    }
    return true;
}

void CTFasta::closeFile(){

    // try to create the index
    // if (bgzf_flush(output_fp) < 0)
    // {
    //     log_error("Error flushing the output file\n");
    //     bgzf_close(output_fp);
    // }
    bgzf_close(output_fp);
    // create the index
    // open the file again
    BGZF *output_fp = bgzf_open(tfasta_fname.c_str(), "r");
    tbx_t *tbx;
    const tbx_conf_t tfasta_conf = {TBX_GENERIC, 1, 2, 2, '#', 0};

    tbx = tbx_index(output_fp, 0, &tfasta_conf);
    bgzf_close(output_fp);
    if (!tbx)
        return ;
    int ret = hts_idx_save_as(tbx->idx, tfasta_fname.c_str(), NULL, HTS_FMT_TBI);
    tbx_destroy(tbx);


    
}

//CTFasta::~CTFasta() {
//}
