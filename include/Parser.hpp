/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>

class FParser {
    std::string keyword,
                information;
public:
    void Parse(std::string fpage, std::string fpage_static_data);
};

#endif // PARSER_HPP
