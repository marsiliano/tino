#include "Block.hpp"

#include <QDebug>
#include <QtTest>

class tst_Eq : public QObject
{
    Q_OBJECT

  private slots:
    void tst_eq();

  private:
    core::Block get();
};

core::Block tst_Eq::get()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };
    std::vector<std::string> s1 = { "bytename" };

    core::Byte b(v, s, true);
    std::vector<core::Byte> vb = { b, b, b };

    core::Byte b1(v, s1, false);
    std::vector<core::Byte> vb1 = { b1, b1, b1 };

    core::Group g(vb, 'm');
    core::Group g1(vb1, 'v');

    std::vector<core::Group> vg = { g, g1 };
    core::Block bl(vg, "block");

    return bl;
}

void tst_Eq::tst_eq()
{
    core::Block b1 = get();
    core::Block b2 = get();
    QVERIFY(b1 == b2);
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
