/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: jjene
 *
 * Created on 23 de junio de 2017, 15:03
 */

#ifndef FILE_H
#define FILE_H

#include <string>
#include "zutil.h"
#include "zindex.h"

class File {
private:
    FILE *file_handle_;
    SGZip gz;
    struct SGZIndex idx;

public:
    std::string file_name_;

public:
    File();
    File(const std::string & file_name);
    File(const File& orig);
    virtual ~File();

public:
    bool openReadFile(void);
    bool openWriteFile(void);
    void closeFile(void);
    char getFileChar(void);
    bool endFile(void);
    void writeFile(std::string s);
    static long int getFileSize(const std::string & file_name);
};

#endif /* FILE_H */

