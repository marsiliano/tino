#pragma once

#include <Block.hpp>
#include <QGroupBox>

struct GuiElement {
    Element *el;
    std::vector<QWidget *> w;
};

class MdiChild : public QGroupBox
{
    Q_OBJECT

  public:
    explicit MdiChild(const Block &block, QWidget *parent = nullptr);

    bool hasElementWithAddress(int address) const;

  public slots:
    void updateGuiElemets();

  private:
    std::vector<int> m_addresses;
    std::vector<GuiElement> m_guiElements;
};
