/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef FPAGE_HPP
#define FPAGE_HPP

#include <iostream>
#include <string>

#include <Locale.hpp>

#define VERSION "0.1-beta-1"

class FPage {
public:
    FPage() = default;
    ~FPage()= default;

    void Initialize(std::string page, bool local);

    std::string DEFAULT_LOCALE = "en";

    /* TODO: Turkish language support for FPages. */
    std::string DEFAULT_DIRECTORY = "/usr/local/fpages/";
};

#endif // FPAGE_HPP
