/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <iostream>
#include <string>
#include <vector>

enum class FTokens : const uint8_t {
    Eq = 0,
    Uneq,
    Global,
    Script
};

class FScript {
    const std::vector<std::string> supported_tokens = {
        "eq",
        "uneq",
        "global",
        "script"
    };

    std::vector<std::string> envs;
public:
    FScript() = default;
    ~FScript()= default;

    std::string generated;

    bool noscript = true;
    bool is_glob = false;
    bool is_glob_data = false;

    bool is_script_statement = false;
    bool is_script_data = false;

    void Generate(const std::string& static_data) noexcept;

    const std::vector<std::string> Tokenize(const std::string& static_line) noexcept;

    bool is_keyword(std::string data) noexcept;

    bool is_global(std::string data) noexcept;
    bool is_script(std::string data) noexcept;
    bool is_script_flag(std::string data) noexcept;

    bool is_equal (const std::string& data) noexcept;

    bool is_eq    (const std::string& data) noexcept;
    bool is_uneq  (const std::string& data) noexcept;

    void Interpret(const std::vector<std::string> data) noexcept;
};

#endif // SCRIPT_HPP
