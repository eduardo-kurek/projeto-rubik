#pragma once

#include "helpers/Color.h"
#include <array>
#include <vector>
#include <string>

// A ordem dos adesivos é da esqueda para a direita, de cima para baixo, ignorando o adesivo central.
struct FacePosition{
    std::array<const Color*, 8> colors;

    std::string toString() const;
    static FacePosition fromString(const std::string& pos);

private:
    static FacePosition doConversion(const std::string& pos);

};


struct RubikPosition{
    FacePosition front;
    FacePosition up;
    FacePosition right;
    FacePosition bottom;
    FacePosition left;
    FacePosition back;

    std::string toString() const;
    static RubikPosition fromString(const std::string& pos);

private:
    static RubikPosition doConversion(const std::string& pos);
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    
};

extern const RubikPosition* POS_RESOLVIDO;