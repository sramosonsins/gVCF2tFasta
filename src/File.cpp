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
    file_handle_ = NULL;
}

File::File(const std::string & file_name) {
    file_name_ = file_name;
    file_handle_ = NULL;
}

File::File(const File& orig) {
    file_name_ = orig.file_name_;
    file_handle_ = NULL;
}

File::~File() {
    if (file_handle_ != NULL) {
        closeFile();
    }

}

long int File::getFileSize(const std::string & file_name) {
    std::ifstream f(file_name.c_str(), std::ios::binary | std::ios::ate);
    long int ret = f.tellg();
    f.close();

    return ret;
}

bool File::openReadFile(void) {
    bool ret = true;

    if ((file_handle_ = fzopen(file_name_.c_str(), "r", &gz)) == NULL) {
        ret = false;
    }

    return ret;
}

bool File::openWriteFile(void) {
    bool ret = true;

    /*init_gzindex_structure(&idx);
    file_handle_ = fzopen(file_name_.c_str(), "wb+", &gz);

    if (file_handle_ != NULL) {
        gz.index = &idx;
    } else {
        ret = false;
    }*/

    if ((file_handle_ = fzopen(file_name_.c_str(), "wb+", &gz)) == NULL) {
        ret = false;
    } else {
        init_gzindex_structure(&idx);
        gz.index = &idx;
    }

    return ret;
}

void File::writeFile(std::string s) {
    fzprintf(file_handle_, &gz, (char*) s.c_str());
}

void File::closeFile(void) {
    fzclose(file_handle_, &gz);
}

char File::getFileChar(void) {
    return fzgetc(file_handle_, &gz);
}

bool File::endFile(void) {
    bool ret = false;

    if (fzeof(file_handle_, &gz) == true) {
        ret = true;
    }

    return ret;
}