#include "Rubik.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Color.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <regex>
#include <algorithm>

Rubik::Rubik(){
    for(int i = 0; i < 6; i++)
        this->faces[i] = Face(COLORS[i]);
}

Rubik::Rubik(const std::string& position){
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
    this->restrictedMoves = {};
}

void Rubik::clearHistoric(){
    std::queue<const Move*> empty;
    this->historic = empty;
}

void Rubik::restrict(const Move* move, const Move* lastMove){
    auto restrictedMoves = this->restrictionFunction(move, lastMove);
    this->restrictedMoves = restrictedMoves;
}

void Rubik::setPosition(const std::string& position){
    // Padrão que a string deve ser enviada
    std::regex pattern("[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}");

    // Verifica se o padrão é válido
    if(!regex_match(position, pattern))
        throw std::runtime_error("O formato da string para inicializar um Rubik deve ser válida");

    // Código para definir a posição
    int count = 0;
    for(uint8_t face = 0; face < 6; face++){
        for(uint8_t i = 0; i < 3; i++){
            for(uint8_t j = 0; j < 3; j++){
                if(i != 1 || j != 1){
                    this->faces[face].stickers[i][j].setColor(Color::getColorByCode(position[count]));
                    count++;
                }
                else this->faces[face].stickers[i][j].setColor(COLORS[face]);
            }
        }
        count++;
    }
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
    auto temp = this->historic;

    while(!temp.empty()){
        std::cout << temp.front()->name << " ";
        temp.pop();
    }

    std::cout << std::endl;
}

std::vector<const Move *> Rubik::getHistoric(){
    auto temp = this->historic;
    std::vector<const Move*> moves;

    while(!temp.empty()){
        moves.push_back(temp.front());
        temp.pop();
    }

    return moves;
}

void Rubik::printRestrictedMoves() const{
    using namespace std;
    for(auto& move : this->restrictedMoves)
        cout << move->name << " ";
    cout << endl;
}

void Rubik::reset(){
    this->setPosition(POS_RESOLVIDO);
    this->clearRestrictedMoves();
}

std::string Rubik::extract() const{
    std::string str;

    for(uint8_t face = 0; face < 6; face++){
        for(uint8_t l = 0; l < 3; l++)
            for(uint8_t c = 0; c < 3; c++)
                if(l != 1 || c != 1) str += this->faces[face].stickers[l][c].getColor()->cod;
        if(face < 5) str += '-';
    }
    
    return str;
}

void Rubik::move(int numArgs, ...){
    va_list args;
    va_start(args, numArgs);

    for(int i = 0; i < numArgs; i++){
        const Move* mov = va_arg(args, const Move*);

        // VERIFICA SE O MOVIMENTO PODE SER EXECUTADO
        if(!this->forceRestrictedMoves){

            auto iterator = std::find(this->restrictedMoves.begin(), this->restrictedMoves.end(), mov);
            if(iterator != this->restrictedMoves.end()) continue;

        }

        for(uint8_t qt = 0; qt < mov->quantity; qt++){

            const Color* aux[3] = {&NONE, &NONE, &NONE};
            for(uint8_t j = 0; j < 4; j++){
                // VARIÁVEIS AUXILIARES
                const uint8_t indexFace = mov->faces[j];
                const Layer* layer = mov->layers[j];
                const Color** colors = this->faces[indexFace].extractLayer(*layer);

                // SETANDO A CAMADA ATUAL
                if(j > 0) this->faces[indexFace].setLayer(*layer, aux);

                // AJUSTANDO O AUXILIAR
                for(int k = 0; k < 3; k++)
                    aux[k] = colors[k];

                delete[] colors;
            }

            // SETANDO A PRIMEIRA FACE DA LISTA
            this->faces[mov->faces[0]].setLayer(*mov->layers[0], aux);

            // GIRANDO A FACE FRACA NO SENTIDO RECEBIDO
            this->faces[mov->weakSide].rotate(mov->turn);
        }

        // ADICIONANDO O MOVIMENTO REALIZADO NA FILA
        if(this->historic.size() >= 20) this->historic.pop();
        this->historic.push(mov);

        // RECALCULANDO OS NOVOS MOVIMENTOS RESTRITOS DO CUBO
        this->restrict(mov, this->lastMove);

        // ATUALIZANDO O ÚTILMO MOVIMENTO REALIZADO
        this->lastMove = mov;
    }

    va_end(args);
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
        int rand = std::rand() % (int)moves.size();

        // MOVIMENTA O CUBO MÁGICO
        this->move(1, moves[rand]);
    }
}

uint8_t Rubik::countEqualStickers(const Rubik& other, const Edge& edge, const uint8_t offset) const{
    uint8_t count = 0;

    auto stickers = edge.getStickers();
    for(uint8_t i = 0; i < 2; i++){
        auto current = stickers[i];
        auto next = stickers[(i + offset) % 2];

        auto mySticker = this->getFaces()[current->getFace()].stickers[current->getLine()][current->getColumn()];
        auto otherSticker = other.getFaces()[next->getFace()].stickers[next->getLine()][next->getColumn()];

        if(mySticker == otherSticker) count++;
    }

    return count;
}

uint8_t Rubik::countEqualStickers(const Rubik& other, const Corner& corner, const uint8_t offset) const{
    uint8_t count = 0;

    auto stickers = corner.getStickers();
    for(uint8_t i = 0; i < 3; i++){
        auto current = stickers[i];
        auto next = stickers[(i + offset) % 3];

        auto mySticker = this->getFaces()[current->getFace()].stickers[current->getLine()][current->getColumn()];
        auto otherSticker = other.getFaces()[next->getFace()].stickers[next->getLine()][next->getColumn()];

        if(mySticker == otherSticker) count++;
    }

    return count;
}

Corners::State Rubik::compareCorner(const Rubik& rubik, const Corner& corner) const{
    // VERIFICANDO A ORIENTAÇÃO DA PEÇA
    uint8_t corrects = this->countEqualStickers(rubik, corner);
    if(corrects == 1) return Corners::State::ORIENTED;
    if(corrects == 3) return Corners::State::CORRECT;

    // VERIFICANDO A PERMUTAÇÃO DA PEÇA NO SENTIDO HORÁRIO
    corrects = this->countEqualStickers(rubik, corner, 1);
    if(corrects == 3) return Corners::State::PERMUTED_CLOCKWISE;

    // VERIFICANDO A PERMUTAÇÃO DA PEÇA NO SENTIDO ANTI-HORÁRIO
    corrects = this->countEqualStickers(rubik, corner, 2);
    if(corrects == 3) return Corners::State::PERMUTED_ANTICLOCKWISE;

    // PEÇA COMPLETAMENTE INCORRETA
    return Corners::State::INCORRECT;
}

Edges::State Rubik::compareEdge(const Rubik& rubik, const Edge& edge) const{
    // VERIFICA QUANTOS ADESIVOS BATEM NA PEÇA ORIGINAL
    uint8_t corrects = countEqualStickers(rubik, edge);
    if(corrects == 1) return Edges::State::ORIENTED;
    if(corrects == 2) return Edges::State::CORRECT;

    // VERIFICAR SE A PEÇA ESTA PERMUTADA
    corrects = countEqualStickers(rubik, edge, 1);
    if(corrects == 2) return Edges::State::PERMUTED;

    // PEÇA INCORRETA
    return Edges::State::INCORRET;
}

std::ostream& operator<<(std::ostream& os, const Rubik* rubik){
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

bool Rubik::operator==(const Rubik& other){
    for(int i = 0; i < 6; ++i)
        if(!(this->faces[i] == other.faces[i]))
            return false;
    return true;
}