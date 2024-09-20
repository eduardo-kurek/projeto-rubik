#include "Historic.h"
#include <iostream>

void Historic::add(const Move* move){
    if(this->moves.size() >= HISTORIC_SIZE) this->moves.pop();
    this->moves.push(move);
}

void Historic::clear(){
    this->moves = std::queue<const Move*>();
}

void Historic::print() const{
    auto temp = this->moves;

    while(!temp.empty()){
        std::cout << temp.front()->name << " ";
        temp.pop();
    }

    std::cout << std::endl;
}

std::vector<const Move*> Historic::toVector() const{
    auto temp = this->moves;
    std::vector<const Move*> moves;

    while(!temp.empty()){
        moves.push_back(temp.front());
        temp.pop();
    }

    return moves;
}

std::string Historic::toString() const{
    std::string s;
    auto historic = this->toVector();
    for(auto& move : historic)
        s += move->name + " ";
    s += "\b";
    return s;
}
