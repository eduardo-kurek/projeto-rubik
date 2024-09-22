#include "RubikPosition.h"
#include <cstdint>
#include <regex>
#include <iostream>
#include "helpers/enums/Faces.h"
#include "helpers/Color.h"

std::string RubikPosition::toString() const{
    std::string str;
    str += front.toString() + "-";
    str += up.toString() + "-";
    str += right.toString() + "-";
    str += bottom.toString() + "-";
    str += left.toString() + "-";
    str += back.toString();
    return str;
}

std::string FacePosition::toString() const{
    std::string str;
    for(auto& color : colors){
        if(color == nullptr) std::cerr << "Cor nula na face" << str << std::endl;
        str += color->cod;
    }
    return str;
}

FacePosition FacePosition::fromString(const std::string &pos){
    std::regex pattern("[BYRWOG]{8}");
    if(!regex_match(pos, pattern))
        throw std::runtime_error("O formato da string para inicializar um FacePosition deve ser válida");
    return FacePosition::doConversion(pos);
}

FacePosition FacePosition::doConversion(const std::string &pos){
    FacePosition converted;
    for(int i = 0; i < 8; i++)
        converted.colors[i] = Color::getColorByCode(pos[i]);
    return converted;
}

RubikPosition RubikPosition::fromString(const std::string &pos){
    std::regex pattern("[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}");
    if(!regex_match(pos, pattern))
        throw std::runtime_error("O formato da string para inicializar um RubikPosition deve ser válida");
    return RubikPosition::doConversion(pos);
}

RubikPosition RubikPosition::doConversion(const std::string &pos){
    RubikPosition converted;
    std::vector<std::string> splitedFaces = splitString(pos, '-');
    converted.front = FacePosition::fromString(splitedFaces[FRONT]);
    converted.up = FacePosition::fromString(splitedFaces[TOP]);
    converted.right = FacePosition::fromString(splitedFaces[RIGHT]);
    converted.bottom = FacePosition::fromString(splitedFaces[BOTTOM]);
    converted.left = FacePosition::fromString(splitedFaces[LEFT]);
    converted.back = FacePosition::fromString(splitedFaces[BACK]);
    return converted;
}

std::vector<std::string> RubikPosition::splitString(const std::string &str, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while(std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

const RubikPosition* POS_RESOLVIDO = new RubikPosition{
    FacePosition{&BLUE, &BLUE, &BLUE, &BLUE, &BLUE, &BLUE, &BLUE, &BLUE},
    FacePosition{&YELLOW, &YELLOW, &YELLOW, &YELLOW, &YELLOW, &YELLOW, &YELLOW, &YELLOW},
    FacePosition{&RED, &RED, &RED, &RED, &RED, &RED, &RED, &RED},
    FacePosition{&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE},
    FacePosition{&ORANGE, &ORANGE, &ORANGE, &ORANGE, &ORANGE, &ORANGE, &ORANGE, &ORANGE},
    FacePosition{&GREEN, &GREEN, &GREEN, &GREEN, &GREEN, &GREEN, &GREEN, &GREEN}
};