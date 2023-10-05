#include "Layer.h"

Layer::Layer(uint8_t si, uint8_t ei, uint8_t sj, uint8_t ej){
    this->si = si;
    this->ei = ei;
    this->sj = sj;
    this->ej = ej;
}

const Layer LAYER_U  = Layer(0, 0, 0, 2);
const Layer LAYER_UA = Layer(0, 0, 2, 0);
const Layer LAYER_D  = Layer(2, 2, 0, 2);
const Layer LAYER_DA = Layer(2, 2, 2, 0);
const Layer LAYER_R  = Layer(0, 2, 2, 2);
const Layer LAYER_RA = Layer(2, 0, 2, 2);
const Layer LAYER_L  = Layer(0, 2, 0, 0);
const Layer LAYER_LA = Layer(2, 0, 0, 0);
const Layer LAYER_M  = Layer(0, 2, 1, 1);
const Layer LAYER_MA = Layer(2, 0, 1, 1);
const Layer LAYER_E  = Layer(1, 1, 0, 2);
const Layer LAYER_EA = Layer(1, 1, 2, 0);