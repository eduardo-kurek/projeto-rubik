#include "Rubik.h"
#include "helpers/constantes.h"
#include "helpers/Color.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <regex>
#include <algorithm>
#include "Random.h"

#ifdef _WIN32
    #include <windows.h>
#endif

Rubik::Rubik(){
    for(int i = 0; i < 6; i++)
        this->faces[i] = Face(COLORS[i]);
}

Rubik::Rubik(const RubikPosition& position){
    for(int i = 0; i < 6; i++)
        this->faces[i] = Face(COLORS[i]);
    this->setPosition(position);
}

const Face* Rubik::getFaces() const{
    return this->faces;
}

void Rubik::setRestrictionFunction(const RestrictionFunction& restrictionFunction){
    this->restrictionFunction = restrictionFunction;
}

void Rubik::clearRestrictedMoves(){
    this->restrictedMoves.clear();
}

void Rubik::restrict(const Move* move, const Move* lastMove){
    auto restrictedMoves = this->restrictionFunction(move, lastMove);
    this->restrictedMoves = restrictedMoves;
}

void Rubik::setPosition(const RubikPosition& position){
    this->faces[FRONT].setPosition(position.front, BLUE);
    this->faces[TOP].setPosition(position.up, YELLOW);
    this->faces[RIGHT].setPosition(position.right, RED);
    this->faces[BOTTOM].setPosition(position.bottom, WHITE);
    this->faces[LEFT].setPosition(position.left, ORANGE);
    this->faces[BACK].setPosition(position.back, GREEN);
}

void Rubik::print(bool clear) const{
    if(clear){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    std::cout << this;
}

void Rubik::printHistoric() const{
    historic.print();
}

std::vector<const Move*> Rubik::getHistoric() const{
    return historic.toVector();
}

std::string Rubik::getHistoricString() const{
    return historic.toString();
}

void Rubik::clearHistoric(){
    historic.clear();
}

void Rubik::printRestrictedMoves() const{
    using namespace std;
    for(auto& move : this->restrictedMoves)
        cout << move->name << " ";
    cout << endl;
}

void Rubik::reset(){
    this->setPosition(*POS_RESOLVIDO);
    this->clearHistoric();
    this->clearRestrictedMoves();
}

RubikPosition Rubik::extractPosition() const{
    RubikPosition position {
        this->faces[FRONT].extract(),
        this->faces[TOP].extract(),
        this->faces[RIGHT].extract(),
        this->faces[BOTTOM].extract(),
        this->faces[LEFT].extract(),
        this->faces[BACK].extract()
    };
    return position;
}

void Rubik::move(std::vector<const Move*> moves){
    for(auto& move : moves)
        this->move(move);
}

void Rubik::move(const Move* mov){
    if(!canExecute(mov)) return;
    if(mov->quantity == 1)
        doSingleMove(mov);
    else
        doDoubleMove(mov);
    setupAfterMove(mov);
}

bool Rubik::canExecute(const Move* mov) const{
    if(mov == nullptr) return false;
    if(canForceMoves()) return true;
    if(!isMoveRestricted(mov)) return true;
    return false;
}

void Rubik::setupAfterMove(const Move* mov){
    historic.add(mov);
    restrict(mov, lastMove);
    lastMove = mov;
}

void Rubik::doSingleMove(const Move* mov){
    swapRightShiftFaceLayers(mov->faces, mov->layers);
    rotateWeakSide(mov);
}

void Rubik::doDoubleMove(const Move* mov){
    swapDoubleShiftFaceLayers(mov->faces, mov->layers);
    rotateWeakSide(mov);
    rotateWeakSide(mov);
}

void Rubik::swapRightShiftFaceLayers(const Faces* faces, const Layer*const layers[4]){
    auto layerColors = getLayerColorsArray(faces, layers);
    std::array<const Color*, 3> aux = layerColors[0];
    setFaceLayer(faces[0], layers[0], layerColors[3]);
    setFaceLayer(faces[3], layers[3], layerColors[2]);
    setFaceLayer(faces[2], layers[2], layerColors[1]);
    setFaceLayer(faces[1], layers[1], aux);
}

void Rubik::swapDoubleShiftFaceLayers(const Faces *faces, const Layer *const layers[4]){
    auto layerColors = getLayerColorsArray(faces, layers);
    std::array<const Color*, 3> aux = layerColors[0];
    setFaceLayer(faces[0], layers[0], layerColors[2]);
    setFaceLayer(faces[2], layers[2], aux);
    aux = layerColors[1];
    setFaceLayer(faces[1], layers[1], layerColors[3]);
    setFaceLayer(faces[3], layers[3], aux);
}

void Rubik::rotateWeakSide(const Move* mov){
    this->faces[mov->weakSide].rotate(mov->turn);
}

std::array<std::array<const Color*, 3>, 4> Rubik::getLayerColorsArray(const Faces* face, const Layer*const layer[4]) const{
    std::array<std::array<const Color*, 3>, 4> layerColors;
    for(int i = 0; i < 4; i++)
        layerColors[i] = this->faces[face[i]].getLayerColors(*layer[i]);
    return layerColors;
}

void Rubik::setFaceLayer(const Faces face, const Layer *layer, std::array<const Color*, 3> colors){
    this->faces[face].setLayer(*layer, colors);
}

bool Rubik::isMoveRestricted(const Move *mov) const{
    auto iterator = std::find(restrictedMoves.begin(), restrictedMoves.end(), mov);
    if(iterator != restrictedMoves.end())
        return true;
    return false;
}

bool Rubik::canForceMoves() const{
    return this->forceRestrictedMoves;
}

std::vector<const Move *> Rubik::getValidMoves(){
    std::vector<const Move*> validMoves;

    for(auto& move : Moves){
        auto iterator = std::find(this->restrictedMoves.begin(), this->restrictedMoves.end(), move);
        if(iterator == this->restrictedMoves.end()) validMoves.push_back(move);
    }

    return validMoves;
}

void Rubik::scramble(int quantity){
    for(int i = 0; i < quantity; i++){
        auto moves = this->getValidMoves();

        // GERANDO O NÚMERO ALEATÓRIO
        int rand =  svc::Random::Int(0, moves.size() - 1);

        // MOVIMENTA O CUBO MÁGICO
        this->move(moves[rand]);
    }
}

std::ostream& operator<<(std::ostream& os, const Rubik* rubik){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    // Imprimindo a primeira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo topo
        os << " " << rubik->faces[TOP].getLine(i) << std::endl;
    }

    // Imprimindo a segunda camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem
        for(uint8_t j = 0; j < MARGEM_ESQUERDA; j++, os << " ");

        // Face esquerda
        os << rubik->faces[LEFT].getLine(i) << " ";

        // Face frontal
        os << rubik->faces[FRONT].getLine(i) << " ";

        // Face direita
        os << rubik->faces[RIGHT].getLine(i) << " ";

        // Face posterior
        os << rubik->faces[BACK].getLine(i) << " " << std::endl;
    }

    // Imprimindo a terceira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo baixo
        os << " " << rubik->faces[BOTTOM].getLine(i) << std::endl;
    }
    return os;
}

bool Rubik::operator==(const Rubik& other) const{
    for(int i = 0; i < 6; ++i)
        if(!(this->faces[i] == other.faces[i]))
            return false;
    return true;
}