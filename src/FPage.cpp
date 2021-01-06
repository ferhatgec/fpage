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
#include <Colorized.hpp>

void
FPage::Initialize(std::string page, bool local) {
    std::string page_directory, page_data, page_static_data;

    if(local == false) {
        page_directory   = DEFAULT_DIRECTORY + page + ".fpage";
    } else {
        page_directory   = fsplusplus::GetCurrentWorkingDir() + "/" + page + ".fpage";
    }
    
    page_static_data = fsplusplus::ReadFileWithReturn(page_directory); 
        
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
    FPage main;
    
    if(argc < 2) {
        main.Initialize("fpage", false);
        return 0; 
    }
    
    std::string file = "";    
    
    if(argv[1][0] == '-' && argv[1][1] == '-') { 
        switch(argv[1][2]) {
            case 'l':
            {
                if(argc > 2) {
                    file.append(argv[2]);
                    
                    main.Initialize(file, true);
                } else {
                    main.Initialize("fpage", false);
                }
                
                break;
            }
            
            case 'v':
            {
                BOLD_LIGHT_RED_COLOR
                std::cout << "Fegeya ";
                
                BOLD_LIGHT_YELLOW_COLOR
                std::cout << "FPage ";
                
                BOLD_LIGHT_BLUE_COLOR
                std::cout << "version: ";
                
                BOLD_LIGHT_MAGENTA_COLOR
                std::cout << VERSION << "\n";
            
                break;
            }
            
            default:
            {
                main.Initialize("fpage", false);
                break;
            }
        }
    } else {
        file.append(argv[1]);
    
        /* TODO: Check is fpage file exist */
        main.Initialize(file, false);   
    }
       
    
    return 0;
}
