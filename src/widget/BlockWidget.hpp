#include "GroupWidget.hpp"

class BlockWidget : public QWidget
{
    Q_OBJECT

  public:
    BlockWidget(core::Block val, QWidget *parent = nullptr);
    ~BlockWidget() override = default;
};
