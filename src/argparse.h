#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

class Argument_parser {
private:
    std::unordered_map<std::string, std::string> argument_descriptions;
    std::unordered_map<std::string, std::string> arguments;
    std::unordered_map<std::string, bool>        optional_arguments;
    std::string                                  program_name;

    bool validate_arguments() const {
        for (const auto& desc : argument_descriptions) {
            if (!optional_arguments.at(desc.first) && arguments.count(desc.first) == 0) {
                std::cerr << "error: argument " << desc.first << " is missing.\n";
                return false;
            }
        }
        return true;
    }

public:
    Argument_parser() {
    }

    void add_argument(const std::string& name, const std::string& description, bool is_optional = false) {
        argument_descriptions[name] = description;
        optional_arguments[name]    = is_optional;
    }

    bool parse(int argc, char* argv[]) {
        for (int i = 1; i < argc; i += 2) {
            std::string arg = argv[i];
            if (i + 1 < argc) {
                arguments[arg] = argv[i + 1];
            }
        }

        return validate_arguments();
    }

    std::string get_argument_value(const std::string& name) const {
        if (arguments.count(name) > 0) {
            return arguments.at(name);
        }
        return "";
    }

    bool argument_exists(const std::string& name) const {
        return arguments.count(name) > 0;
    }

    void print_help() const {
        std::cout << "usage: " << program_name << " [options]\n";
        size_t max_name_length = 0;
        for (const auto& desc : argument_descriptions) {
            max_name_length = std::max(max_name_length, desc.first.length());
        }
        for (const auto& desc : argument_descriptions) {
            if (!optional_arguments.at(desc.first)) {
                std::cout << "  " << std::left << std::setw(max_name_length + 5) << desc.first << desc.second << std::endl;
            }
        }
        for (const auto& desc : argument_descriptions) {
            if (optional_arguments.at(desc.first)) {
                std::cout << "  " << std::left << std::setw(max_name_length + 5) << desc.first << desc.second << " (optional)" << std::endl;
            }
        }
    }

    void set_program_name(const std::string& name) {
        program_name = name;
    }
};
