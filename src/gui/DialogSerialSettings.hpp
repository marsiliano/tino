#pragma once

#include <QDialog>
#include <Settings.hpp>

namespace Ui
{
class DialogSerialSettings;
}

class DialogSerialSettings : public QDialog
{
    Q_OBJECT

  public:
    explicit DialogSerialSettings(Settings *settings,
                                  QWidget *parent = nullptr);
    ~DialogSerialSettings() override;

  private slots:
    void serialPortOverrideBox();
    void accept() override;

  private:
    Ui::DialogSerialSettings *ui;
    Settings *m_settings;
};
