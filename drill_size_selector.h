#ifndef DRILL_SIZE_SELECTOR_H
#define DRILL_SIZE_SELECTOR_H

#include <QWidget>
//#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QHeaderView>
#include <algorithm>
#include <QClipboard>
#include "SendKeys.h"
#include <QKeyEvent>

class drill_size_selector : public QWidget
{
        Q_OBJECT
public:
    explicit drill_size_selector(QClipboard &clipboard, QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent *event) override;

    double INPUT_VALUE = 35.7188;
    bool using_inches = true;
    QBrush *row_highlight = new QBrush( QColor(0x5f4d29) );
    QTableWidget *drill_table;
    int GetBestMatch(std::vector<double> array, double INPUT_VALUE);    //Returns and index
    QClipboard *clipboard = nullptr;
    void setInputValue(double value);

    void useInches();
    void useMillis();
    void reCalc();

    std::vector<double> Diameter_Inches;
    std::vector<double> Diameter_Millis;

    void setLocation(QPoint point);
    void clearRowHighlight();

    QPoint *location;

public slots:
    void print_cell_data(int row, int column);

};

#endif // DRILL_SIZE_SELECTOR_H
