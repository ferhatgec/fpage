/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <fstream>
#include <sstream>

#include <FPage.hpp>
#include <Parser.hpp>
#include <Locale.hpp>
#include <Script.hpp>

#include <FileSystemPlusPlus.hpp>
#include <Colorized.hpp>

void
FPage::Initialize(std::string page, bool local) {
    FLocale locale;
    FScript script;

    std::string page_directory, page_data, page_static_data;

    this->DEFAULT_LOCALE = locale.InitLocale(this->DEFAULT_LOCALE);

    if(local == false) {
        page_directory   = this->DEFAULT_DIRECTORY + this->DEFAULT_LOCALE + "/" + page + ".fpage";
    } else {
        page_directory   = fsplusplus::GetCurrentWorkingDir() + "/" + page + ".fpage";
    }
    
    page_static_data = fsplusplus::ReadFileWithReturn(page_directory);

    FParser parser;
    
    std::ifstream readfile(page_directory.c_str());
    
    if(readfile.is_open()) {
        while (std::getline(readfile, page_data)) {
            script.Generate(page_data);
        }
        
        readfile.close();
    }

    if(!script.generated.empty()) {
        std::istringstream stream(script.generated);

        for(std::string temp_line; std::getline(stream, temp_line); ) {
            parser.Parse(temp_line, script.generated);
        }
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
