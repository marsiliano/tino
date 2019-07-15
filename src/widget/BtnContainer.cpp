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
}

void BtnContainer::setClr(const int i)
{
    if (val[i])
        b[i].first->setStyleSheet("background-color:#ff0000;");
    else
        b[i].first->setStyleSheet("background-color:#0000ff;");
}
