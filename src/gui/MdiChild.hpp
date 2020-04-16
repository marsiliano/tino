#pragma once

#include "GuiElement.hpp"

class MdiChild : public QWidget
{
    Q_OBJECT

public:
    explicit MdiChild(const Block &block, QWidget *parent = nullptr);

    bool hasElementWithAddress(int address) const;
    void resetToDefault();

signals:
    void updateModbus(int address);

public slots:
    void updateGuiElemets();

private:
    std::vector<int> m_addresses;
    std::vector<GuiElement> m_guiElements;
};
