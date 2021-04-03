/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <Script.hpp>
#include <sstream>

#include <StringTools.hpp>

void FScript::Generate(const std::string& static_data) noexcept {
    std::string temporary_static_data = static_data;

    std::vector<std::string> tokens;

    std::istringstream stream(temporary_static_data);

    for(std::string temp_line; std::getline(stream, temp_line);) {
        temp_line = stringtools::ltrim(temp_line);

        tokens = Tokenize(temp_line);

        for(unsigned i = 0; i < tokens.size(); i++) {
            if(is_script_flag(tokens[i])) {
                this->noscript = false;
                break;
            }

            if(this->noscript) {
                this->generated.append(temp_line);

                break;
            }

            if(this->is_script_statement && this->is_script_data) {
                if(tokens[i] != "@" || tokens[i][0] == '[' || tokens[i][0] == '*') {
                    this->generated.append(temp_line);
                }
                else {
                    this->is_script_statement = false;
                    this->is_script_data = false;
                }

                break;
            }
            else if(this->is_script_statement && !this->is_script_data) {
                this->is_script_statement = false;

                break;
            }

            if(this->is_glob_data) {
                if(tokens[i][0] != '@') {
                    this->envs.push_back(tokens[i]);
                }
                else {
                    this->is_glob = false;
                    this->is_glob_data = false;
                }

                break;
            }

            if(is_global(tokens[i]) && !this->is_glob_data) {
                this->is_glob_data = true;
                this->is_glob = true;

                break;
            }
            else if(is_script(tokens[i])) {
                Interpret(tokens);

                break;
            }
            else if(tokens[i][0] == '[' || tokens[i][0] == '*') {
                this->generated.append(temp_line + "\n");
                break;
            }
        }

        this->generated.append("\n");
    }

}

const std::vector<std::string> FScript::Tokenize(const std::string& line_data) noexcept {
    std::istringstream temp(line_data);
    std::vector<std::string> temp_tokens;

    for(std::string temp_token; temp >> temp_token;
        temp_tokens.push_back(temp_token));

    return temp_tokens;
}

bool FScript::is_keyword(std::string data) noexcept {
    for(auto& keyword : this->supported_tokens) {
        if(data == keyword) {
            return true;
        }
    }

    if(is_global(data)
        || is_script(data)
        || is_script_flag(data)) {
        return true;
    }

    return false;
}

bool FScript::is_global(std::string data) noexcept {
    return (data.erase(0, 1) == this->supported_tokens[static_cast<uint8_t>(FTokens::Global)]) ? true : false;
}

bool FScript::is_script(std::string data) noexcept {
    return (data.erase(0, 1) == this->supported_tokens[static_cast<uint8_t>(FTokens::Script)]) ? true : false;
}

bool FScript::is_equal (const std::string& data) noexcept {
    return ((data == "eq") || (data == "uneq")) ? true : false;
}

bool FScript::is_script_flag(std::string data) noexcept {
    return (data.erase(0, 2) == "script") ? true : false;
}

bool FScript::is_eq    (const std::string& data) noexcept {
    return (data == "eq") ? true : false;
}

bool FScript::is_uneq  (const std::string& data) noexcept {
    return (data == "uneq") ? true : false;
}

void FScript::Interpret(const std::vector<std::string> data) noexcept {
    for(unsigned i = 0; i < data.size(); i++) {
        if(data[i][0] == '^') {
            std::string environment = data[i];

            for(auto& envs : this->envs) {
                if(envs == environment.erase(0, 1)) {
                    if(i + 2 > data.size()) return;

                    std::string environment_data = std::basic_string(std::getenv(environment.c_str()));

                    if(is_equal(data[i + 1])) {
                        bool __is_eq = is_eq(data[i + 1]);

                        std::string result_data = data[i + 2];

                        this->is_script_statement = true;

                        if(__is_eq) {
                            if(environment_data == result_data) {
                                this->is_script_data = true;
                            }
                            else {
                                this->is_script_data = false;
                            }
                        }
                        else {
                            if(environment_data != result_data) {
                                this->is_script_data = true;
                            }
                            else {
                                this->is_script_data = false;
                            }
                        }
                    }

                    break;
                }
                else {
                    this->generated.append(data[i]);
                    this->generated.append(" ");
                }
            }
        }
    }

    this->generated.append("\n");
}