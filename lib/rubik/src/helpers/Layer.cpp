#include "helpers/Layer.h"


const LayerCoord _00 = {ZERO, ZERO};
const LayerCoord _01 = {ZERO, ONE};
const LayerCoord _02 = {ZERO, TWO};
const LayerCoord _10 = {ONE, ZERO};
const LayerCoord _11 = {ONE, ONE};
const LayerCoord _12 = {ONE, TWO};
const LayerCoord _20 = {TWO, ZERO};
const LayerCoord _21 = {TWO, ONE};
const LayerCoord _22 = {TWO, TWO};

const Layer LAYER_U  = Layer{{_00, _01, _02}};
const Layer LAYER_UA = Layer{{_02, _01, _00}};
const Layer LAYER_D  = Layer{{_20, _21, _22}};
const Layer LAYER_DA = Layer{{_22, _21, _20}};
const Layer LAYER_R  = Layer{{_22, _12, _02}};
const Layer LAYER_RA = Layer{{_02, _12, _22}};
const Layer LAYER_L  = Layer{{_00, _10, _20}};
const Layer LAYER_LA = Layer{{_20, _10, _00}};