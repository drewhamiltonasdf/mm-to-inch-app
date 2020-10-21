#ifndef POP_UP_UNIT_CONVERTER_H
#define POP_UP_UNIT_CONVERTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QClipboard>
#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include "windows.h" // Connect WinAPI library
#include <QApplication>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "SendKeys.h"
#include <QTimer>

#include "drill_size_selector.h"

class pop_up_unit_converter : public QWidget
{
    Q_OBJECT
public:
    explicit pop_up_unit_converter(QWidget *parent = nullptr);
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    void paste_conversion(double &num);
    QString double_to_string(double value);

    QTimer *inactivity_timer;

    drill_size_selector *DrillSelector = nullptr;

    QClipboard *clipboard;
    QGridLayout *gridlayout;
    QPushButton *test_button;
    QMenuBar *Menu_Options;
        QMenu *MORE;
            QMenu *LENGTH;
            QMenu *AREA;
            QMenu *DATA_SPEED;
            QMenu *BYTES;
            QMenu *ENERGY;
            QMenu *FREQUENCY;
            QMenu *MASS;
            QMenu *ANGLE;
            QMenu *PRESSURE;
            QMenu *SPEED;
            QMenu *TEMPERATURE;
            QMenu *TIME;
            QMenu *Volume;

        QMenu *from_inches;
        QMenu *from_mm;
        QAction *close_pop_up;

        QAction *mm_to_inch;
        QAction *mm_to_foot;
        QAction *mm_to_yard;
        QAction *mm_to_mile;
        QAction *mm_to_micron;
        QAction *mm_to_meter;
        QAction *mm_to_km;
        QAction *mm_to_nm;
        QAction *mm_to_cm;
        QAction *mm_to_nautical_mile;
        QAction *mm_to_drill_size;

        QAction *inch_to_mm;
        QAction *inch_to_foot;
        QAction *inch_to_yard;
        QAction *inch_to_mile;
        QAction *inch_to_micron;
        QAction *inch_to_meter;
        QAction *inch_to_km;
        QAction *inch_to_nm;
        QAction *inch_to_cm;
        QAction *inch_to_nautical_mile;
        QAction *inch_to_drill_size;

private:
        double double_from_clipboard_string();

signals:

public slots:
      void showDrillSelectorInches();
      void showDrillSelectorMillis();


      void SLOT_close_pop_up();

      void SLOT_inch_to_mm();
      void SLOT_inch_to_foot();
      void SLOT_inch_to_yard();
      void SLOT_inch_to_mile();
      void SLOT_inch_to_micron();
      void SLOT_inch_to_meter();
      void SLOT_inch_to_cm();
      void SLOT_inch_to_km();
      void SLOT_inch_to_nm();
      void SLOT_inch_to_nautical_mile();

      void SLOT_mm_to_inch();
      void SLOT_mm_to_foot();
      void SLOT_mm_to_yard();
      void SLOT_mm_to_mile();
      void SLOT_mm_to_micron();
      void SLOT_mm_to_meter();
      void SLOT_mm_to_km();
      void SLOT_mm_to_nm();
      void SLOT_mm_to_cm();
      void SLOT_mm_to_nautical_mile();

};

#endif // POP_UP_UNIT_CONVERTER_H
