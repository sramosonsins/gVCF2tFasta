/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.cpp
 * Author: jleno
 * 
 * Created on 23 de junio de 2017, 15:03
 */

#include "File.h"

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>




File::File() {
    file_name_ = "";
    fp = NULL;
}

File::File(const std::string & file_name) {
    file_name_ = file_name;
    fp = NULL;
}

// File::File(const File& orig) {
//     file_name_ = orig.file_name_;
//     fp = NULL;
// }

File::~File() {
    if (fp != NULL) {
        closeFile();
    }

}
void File::closeFile() {
    // close the file
    bgzf_close(fp);
    fp = NULL;
}

long int File::getFileSize(const std::string & file_name) {
    std::ifstream f(file_name.c_str(), std::ios::binary | std::ios::ate);
    long int ret = f.tellg();
    f.close();

    return ret;
}

bool File::openReadFile(void) {
    bool ret = true;

    
    if ((fp = bgzf_open(file_name_.c_str(), "r" )) == NULL) {
    // if ((fp = hts_open_format(file_name_.c_str(), "rz" , &type )) == NULL) {

        ret = false;
    }

    return ret;
}

bool File::openWriteFile(void) {
    bool ret = true;

    if ((fp = bgzf_open(file_name_.c_str(), "w")) == NULL) {
        ret = false;
    }

    

    return ret;
}


char File::getFileChar(void) {
    char c = 0;
    // Read a character from the str 
    // end of line 
    
    if(str.l == 0){
        // len = hts_getline(fp, KS_SEP_LINE, &str);
        len = bgzf_getline(fp, KS_SEP_LINE, &str);
        curr = 0;
    }
    if(len == -1){
        return 0;
    }
    if(str.l == 0){
        // return new line

        return '\n';
    }
    if(curr == len){
        str.l = 0;
        return '\n';
    }
    c = str.s[curr];
    curr++;
    

    return c;
}

bool File::endFile(void) {

    if(len == -1){
       return true;
    }

    return false;
}