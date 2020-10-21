#include "drill_size_selector.h"

//Diameter IN ---  Diameter MM --- Drill Size
//  0.0019           0.0483         #107
// 	0.0156           0.3969         1/64 in


drill_size_selector::drill_size_selector(QClipboard &clipboard, QWidget *parent) : QWidget(parent)
{
    this->clipboard = &clipboard;

    location = new QPoint();

    QFile StyleFile(":/Combinear/Combinear.qss");
    StyleFile.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(StyleFile.readAll());
    setStyleSheet(StyleSheet);

    //Menu_Options = new QMenuBar(this);
      //0.04831.22681.2205  close_pop_up = new QAction("X"); connect(close_pop_up, &QAction::triggered, this, &pop_up_unit_converter::SLOT_close_pop_up);

    drill_table = new QTableWidget(this);

    drill_table->setMaximumSize(188, 1000);
    drill_table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    drill_table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setMaximumSize(188, 1000);
    setMinimumSize(188, 140);
    //    setGeometry(QCursor::pos().x(),QCursor::pos().y(),320,188);
    setWindowFlag(Qt::FramelessWindowHint);

    if (INPUT_VALUE <= 0) {INPUT_VALUE = 0.001;}

    if (INPUT_VALUE >= 1.5 && using_inches) {INPUT_VALUE = 1.5;}
    if (INPUT_VALUE >= 38.1 && !using_inches) {INPUT_VALUE = 38.1;}


    QFile file(":/drill_sizes.csv");
    if (!file.open(QIODevice::ReadOnly)) {
           qDebug() << file.errorString();
           qDebug() << "ERROR READING FILE!";
       }


       QStringList Drill_size;

       while (!file.atEnd()) {
               QString line = file.readLine();
               QStringList split_line = line.split(',');
               Diameter_Inches.push_back(split_line[0].toDouble());
               Diameter_Millis.push_back(split_line[1].toDouble());
               Drill_size.append(split_line[2].trimmed());
       }

       drill_table->setRowCount(Diameter_Inches.size());
       drill_table->setColumnCount(3);
       QStringList header; header.append("Inch:"); header.append("mm:"); header.append("Drill Size");
       drill_table->setHorizontalHeaderLabels(header);
       drill_table->verticalHeader()->setVisible(false);

       Diameter_Inches.erase(Diameter_Inches.begin());
       Diameter_Millis.erase(Diameter_Millis.begin());
       Drill_size.removeAt(0);
       for (uint i = 0; i < Diameter_Inches.size(); i++)
       {
            QTableWidgetItem *a = new QTableWidgetItem(QString::number(Diameter_Inches[i])); a->setFlags(a->flags()^Qt::ItemIsEditable);
            QTableWidgetItem *b = new QTableWidgetItem(QString::number(Diameter_Millis[i])); b->setFlags(b->flags()^Qt::ItemIsEditable);
            QTableWidgetItem *c = new QTableWidgetItem(Drill_size[i]); c->setFlags(c->flags()^Qt::ItemIsEditable);
            drill_table->setItem(i, 0, a);
            drill_table->setItem(i, 1, b);
            drill_table->setItem(i, 2, c);
            //append(QString::number(Diameter_Inches[i]) + "\t" + QString::number(Diameter_Millis[i]) + "\t" + Drill_size[i]);
       }

       drill_table->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
       //drill_table->resizeColumnToContents(0);
       //drill_table->resizeColumnToContents(1);
       //drill_table->resizeColumnToContents(2);
       //drill_table->setContentsMargins(100,0,100,0);
       drill_table->setColumnWidth(0,50);
       drill_table->setColumnWidth(1,50);
       drill_table->setColumnWidth(2,70);

       connect(drill_table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(print_cell_data(int, int)));

       this->hide();
}

void drill_size_selector::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        clearRowHighlight();
        this->hide();
    }
}

int drill_size_selector::GetBestMatch(std::vector<double> array, double INPUT_VALUE)
{
    auto lower = std::lower_bound(array.begin(), array.end(), INPUT_VALUE);
    auto upper = std::upper_bound(array.begin(), array.end(), INPUT_VALUE);

    auto low_index = std::distance(array.begin(), lower);
    auto high_index = std::distance(array.begin(), upper);

    uint min_index = low_index;
    if (low_index > 0)
    {
        auto lower_index = low_index - 1;
        if (abs(array[lower_index] - INPUT_VALUE) < abs(array[low_index] - INPUT_VALUE)) {min_index = lower_index;}
    }
    else
    {
        if (abs(array[high_index] - INPUT_VALUE) < array[min_index]) {min_index = high_index;}
    }

    return min_index;
}

void drill_size_selector::setInputValue(double value)
{
    INPUT_VALUE = value;

}

void drill_size_selector::useInches()
{
    using_inches = true;
}

void drill_size_selector::useMillis()
{
    using_inches = false;
}



void drill_size_selector::reCalc()
{
    if (using_inches)
    {
         int index = GetBestMatch(Diameter_Inches, INPUT_VALUE);
         drill_table->setCurrentCell(index, 0);
         drill_table->item(index,0)->setBackground(*row_highlight);
         drill_table->item(index,1)->setBackground(*row_highlight);
         drill_table->item(index,2)->setBackground(*row_highlight);
    }
    else
    {
        int index = GetBestMatch(Diameter_Millis, INPUT_VALUE);
        drill_table->setCurrentCell(index, 1);
        drill_table->item(index,0)->setBackground(*row_highlight);
        drill_table->item(index,1)->setBackground(*row_highlight);
        drill_table->item(index,2)->setBackground(*row_highlight);
    }
}



void drill_size_selector::setLocation(QPoint point)
{
    location = new QPoint(point);
    setGeometry(location->x(), location->y(), 320, 188);
}

void drill_size_selector::clearRowHighlight()
{
    QColor backgroundcolor(0x131313);

    if (using_inches)
    {
         int index = GetBestMatch(Diameter_Inches, INPUT_VALUE);
         drill_table->setCurrentCell(index, 0);
         drill_table->item(index,0)->setBackground(backgroundcolor);
         drill_table->item(index,1)->setBackground(backgroundcolor);
         drill_table->item(index,2)->setBackground(backgroundcolor);
    }
    else
    {
        int index = GetBestMatch(Diameter_Millis, INPUT_VALUE);
        drill_table->setCurrentCell(index, 1);
        drill_table->item(index,0)->setBackground(backgroundcolor);
        drill_table->item(index,1)->setBackground(backgroundcolor);
        drill_table->item(index,2)->setBackground(backgroundcolor);
    }
}



void drill_size_selector::print_cell_data(int row, int column)
{
    qDebug() << row << " : " << column;
    qDebug() << drill_table->item(row, column)->text();

    clipboard->setText(drill_table->item(row, column)->text());

    hide();
    ::Sleep(100);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(0x56, 0, 0, 0);
    ::Sleep(10);
    keybd_event(0x56,0,KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP, 0);

    clearRowHighlight();
    close();
}

