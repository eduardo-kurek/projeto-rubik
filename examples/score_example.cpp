#include "scores/basic-score/BasicScore.h"

int main(){
    Rubik r;
    r.move({R, U2, D2, L2, D, R, BA});

    // Configuração padrão, a melhor encontrada até o momento
    BasicConfig cfg1;
    cfg1.print();

    // Configuração personalizada para teste
    BasicConfig cfg2({3, 2, 1, 0}, {3, 2, 1, 0}, 0);
    cfg2.print();

    /* Score configurado para pontuar em relação ao cubo resolvido (default);
     Cfg1 será a configuração usada, mas por padrão BasicScore já utiliza o 
     construtor padrão de BasicConfig, então não seria necessário passar cfg1;
    */
    BasicScore score(cfg1);

    std::cout << "Max Score com cfg1: " << score.getMaxScore() << std::endl;
    std::cout << "Score com cfg1: " << score.calculate(r) << std::endl;
    std::cout << "Score em porcentagem  com cfg1: " << score.calculateNormalized(r) << std::endl;
    std::cout << std::endl;

    // Configuração personalizada
    score.configurate(cfg2);
    std::cout << "Max Score com cfg2: " << score.getMaxScore() << std::endl;
    std::cout << "Score com cfg2: " << score.calculate(r) << std::endl;
    std::cout << "Score com cfg2: " << score.calculate(Rubik()) << std::endl;
    std::cout << "Score em porcentagem com cfg2: " << score.calculateNormalized(r) << std::endl;

    return 0;
}