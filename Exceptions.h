//
// Created by Bychin on 21.10.2017.
//

#ifndef LABORATORY_WORK_1_2_EXCEPTIONS_H
#define LABORATORY_WORK_1_2_EXCEPTIONS_H


#include <exception>
#include <string>


class BadFileFormatException : public std::exception {
    std::string error;
public:
    BadFileFormatException() {
        error.assign("Unknown or unsupported file format!");
    }
    explicit BadFileFormatException(const std::string& file_format) {
        error.assign("File format \"" + file_format + "\" is not supported!");
    }
    const char* what() const noexcept override {
        return error.c_str();
    }
};

class NoFileFoundException : public std::exception {
    std::string error;
public:
    NoFileFoundException() {
        error.assign("Cannot open file! Probably it does not exist!");
    }
    explicit NoFileFoundException(const std::string& file_) {
        error.assign("Cannot open file: \"" + file_ + "\"! Probably it does not exist!");
    }
    const char* what() const noexcept override {
        return error.c_str();
    }
};

#endif //LABORATORY_WORK_1_2_EXCEPTIONS_H
