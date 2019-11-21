#ifndef QLED_H
#define QLED_H

#include <QHash>
#include <QWidget>

class QSvgRenderer;

class Led : public QWidget
{
    Q_OBJECT

  public:
    friend class LedRenderer;

    typedef enum LedColor {
        Red,
        Green,
        Yellow,
        Grey,
        Orange,
        Purple,
        Blue,

        MaxLedColor
    } LedColor;

    typedef enum LedShape {
        Circle,
        Square,
        Triangle,
        Rounded,

        MaxLedShape
    } LedShape;

    typedef enum State {
        Off,
        On,

        MaxState
    } State;

    Led(const QString &description = QString(), QWidget *parent = nullptr,
        const QSize &ledSize = QSize(30, 30), const Led::State state = Led::Off,
        const Led::LedColor &onColor  = Led::Green,
        const Led::LedColor &offColor = Led::Grey,
        const Led::LedShape &shape    = Led::Circle,
        const int textAligment        = Qt::AlignCenter);
    Led();
    ~Led();

    Led::State state() const;
    void setState(const Led::State &state);

    LedColor color(const State &state) const;
    void setColor(const State &state, const LedColor &color);

    LedShape shape() const;
    void setShape(const LedShape &shape);

    void setLedSize(QSize size);

    int textAligment() const;
    void setTextAligment(const int &textAligment);

    QString description() const;
    void setDescription(const QString &description);

    void setBlinkEnabled(bool enable, int blinkMsec = 2000);
    bool isBlinking() const;

    void setInteractive(bool value);
    bool isInteractive();

    void setTag(const QString &tag);
    QString tag() const;

  public slots:
    void toggle();

  signals:
    void sizeChanged();
    void clicked();

  protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

  private:
    QSize m_ledSize;
    State m_state;
    LedColor m_onColor;
    LedColor m_offColor;
    LedShape m_shape;
    QString m_description;
    int m_textAligment;
    bool m_blink;
    QTimer *m_blinkTimer;
    bool m_interactive;
    QString m_tag;

    void init();
    void check();
};

class LedRenderer : public QObject
{
    Q_OBJECT

  public:
    static LedRenderer *getIstance();

    QSvgRenderer *getRenderer(const Led::LedShape &shape,
                              const Led::LedColor &color);

  private:
    QHash<QPair<Led::LedShape, Led::LedColor>, QSvgRenderer *> m_renderers;
    static LedRenderer *istance;

    explicit LedRenderer(QObject *parent = nullptr);
    ~LedRenderer();
    void init();
    QString stringifyColor(const Led::LedColor &color) const;
    QString stringifyShape(const Led::LedShape &shape) const;
};
#endif
