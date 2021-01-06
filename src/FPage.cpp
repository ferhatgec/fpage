/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <fstream>

#include <FPage.hpp>
#include <Parser.hpp>

#include <FileSystemPlusPlus.hpp>

void
FPage::Initialize(std::string page, bool local) {
    std::string page_directory, page_data, page_static_data;

    if(local == false) {
        page_directory   = DEFAULT_DIRECTORY + page + ".fpage";
        page_static_data = fsplusplus::ReadFileWithReturn(page_directory); 
    }
    
    FParser parser;
    
    std::ifstream readfile(page_directory.c_str());
    
    if(readfile.is_open()) {
        while (std::getline(readfile, page_data)) { 
        	parser.Parse(page_data, page_static_data);
        }
        
        readfile.close();
    } 
}

int main(int argc, char** argv) {
    if(argc < 2) {
        /* TODO: Read 'fpage' fpage. */        
        return 0; 
    }
    
    std::string file(argv[1]);
    
    /* TODO: Check is fpage file exist */
    FPage main;
    
    main.Initialize(file, false);   
    
    return 0;
}
