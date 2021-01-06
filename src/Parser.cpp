/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <string>
#include <sstream>

#include <Parser.hpp>
#include <StringTools.hpp>
#include <Colorized.hpp>

void 
FParser::Parse(std::string fpage, std::string fpage_static_data) {
    keyword     = stringtools::GetBetweenString(fpage, "[", "]");
    
    if(fpage.front() != '}') {
        information = stringtools::Between(fpage_static_data, "[" + keyword + "]" + "{", "}");    
    } else {
        information = stringtools::GetBetweenString(fpage, "[" + keyword + "]" + "{", "}");
    }
    
    if(information != "error") {
        if(keyword == "Title") {
            BOLD_LIGHT_WHITE_COLOR std::cout << " " << information + "\n"; RESETB  
        }
        else if(keyword == "Description") {
            LIGHT_BLUE_COLOR std::cout << " " << information << "\n\n"; RESETB
        }
        else if(keyword == "Author") {
            LIGHT_BLACK_COLOR std::cout << " " << information + "\n"; RESETB
        }
        else if(keyword == "License") {
            LIGHT_MAGENTA_COLOR std::cout << " " << information + "\n"; RESETB
        }
        else if(keyword == "Usage") {
            std::string code_block, description, block;
            
            std::istringstream usage_stream(information);
            
            while(std::getline(usage_stream, block)) {
                block = stringtools::ltrim(block);
                
                if(block[0] == '*') {
                    description = stringtools::GetBetweenString(block, "*", ":");
                    code_block  = stringtools::GetBetweenString(block, "<", ">");
                    

                    LIGHT_GREEN_COLOR std::cout << " *" << description << ":" << "\n";
                    
                    /* TODO: Syntax highlighting */
                    LIGHT_WHITE_COLOR std::cout << "   " << code_block << "\n\n"; RESETB
                }
            }
        }
    } else {
        /* List */
    }     
}
