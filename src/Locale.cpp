/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <Locale.hpp>
#include <cstdlib>

std::string FLocale::InitLocale(const std::string& data) noexcept {
    std::string temporary_locale = std::basic_string(std::getenv("LANG"));

    for(auto& locale : this->supported_locales) {
        if(locale.substr(0, 5) == temporary_locale) {
            return locale.substr(0, 2);
        }
    }

    return "en";
}