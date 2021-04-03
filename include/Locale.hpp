/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef LOCALE_HPP
#define LOCALE_HPP

#include <iostream>
#include <string>
#include <vector>

// enum class LanguageLocales : const int8_t {
//     English = 0,
//     Turkish // 1
// };

class FLocale {
    const std::vector<std::string> supported_locales = {
        // "en_US",
        // "en_GB",
        "tr_TR"
    };
public:
    FLocale() = default;
    ~FLocale()= default;

    std::string InitLocale(const std::string& data) noexcept;
};

#endif // LOCALE_HPP
