#include "BtnContainer.hpp"

BtnContainer::BtnContainer()
{
    for (int i = 0; i < 8; ++i) {
        b.emplace_back(std::make_pair(
            std::unique_ptr<QPushButton>(new QPushButton()), [i, this]() {
                val.set(i);
                setClr(i);
            }));
    }
    //    ci vorrebbe un modo per mettere in un Btncontainer i button da 0 a 3 e
    //    nell'altro dal 4 al 7, altrimenti entrambi contengono anche i valori
    //    dell'altro
}

void BtnContainer::setClr(const int i)
{
    if (val[i])
        b[i].first->setStyleSheet("background-color:#ff0000;");
    else
        b[i].first->setStyleSheet("background-color:#0000ff;");
}
