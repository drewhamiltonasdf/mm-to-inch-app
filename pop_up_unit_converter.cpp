#include "pop_up_unit_converter.h"


pop_up_unit_converter::pop_up_unit_converter(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground);

    inactivity_timer = new QTimer(this);


    connect(inactivity_timer, SIGNAL(timeout()), this, SLOT(SLOT_close_pop_up()));

    QFile StyleFile(":/Combinear/Combinear.qss");
    StyleFile.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(StyleFile.readAll());
    setStyleSheet(StyleSheet);

    QClipboard *clipboard = QGuiApplication::clipboard();
    DrillSelector = new drill_size_selector(*clipboard);
    DrillSelector->hide();

    Menu_Options = new QMenuBar(this);
    Menu_Options->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    //base_units->setMinimumWidth(400);
        from_inches = new QMenu("inch →", this);
            inch_to_mm = new QAction("mm", this); from_inches->addAction(inch_to_mm); connect(inch_to_mm, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_mm);
            inch_to_micron = new QAction("micron", this); from_inches->addAction(inch_to_micron); connect(inch_to_micron, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_micron);
            inch_to_drill_size = new QAction("drill size", this); from_inches->addAction(inch_to_drill_size); connect(inch_to_drill_size, &QAction::triggered, this, &pop_up_unit_converter::showDrillSelectorInches);
            inch_to_nm = new QAction("nm", this); from_inches->addAction(inch_to_nm); connect(inch_to_nm, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_nm);
            inch_to_cm = new QAction("cm", this); from_inches->addAction(inch_to_cm); connect(inch_to_cm, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_cm);
            inch_to_meter = new QAction("meter", this); from_inches->addAction(inch_to_meter); connect(inch_to_meter, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_meter);
            inch_to_foot = new QAction("foot", this); from_inches->addAction(inch_to_foot); connect(inch_to_foot, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_foot);
            inch_to_yard = new QAction("yard", this); from_inches->addAction(inch_to_yard); connect(inch_to_yard, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_yard);
            inch_to_mile = new QAction("mile", this); from_inches->addAction(inch_to_mile); connect(inch_to_mile, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_mile);
            inch_to_km = new QAction("km", this); from_inches->addAction(inch_to_km); connect(inch_to_km, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_km);
            inch_to_nautical_mile = new QAction("nautical mile", this); from_inches->addAction(inch_to_nautical_mile); connect(inch_to_nautical_mile, &QAction::triggered, this, &pop_up_unit_converter::SLOT_inch_to_nautical_mile);

        from_mm = new QMenu("mm →", this);
            mm_to_inch = new QAction("inch", this); from_mm->addAction(mm_to_inch); connect(mm_to_inch, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_inch);
            mm_to_micron = new QAction("micron", this); from_mm->addAction(mm_to_micron); connect(mm_to_micron, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_micron);
            mm_to_drill_size = new QAction("drill size", this); from_mm->addAction(mm_to_drill_size); connect(mm_to_drill_size, &QAction::triggered, this, &pop_up_unit_converter::showDrillSelectorMillis);
            mm_to_cm = new QAction("cm", this); from_mm->addAction(mm_to_cm); connect(mm_to_cm, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_cm);
            mm_to_meter = new QAction("meter", this); from_mm->addAction(mm_to_meter); connect(mm_to_meter, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_meter);
            mm_to_nm = new QAction("nm", this); from_mm->addAction(mm_to_nm); connect(mm_to_nm, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_nm);
            mm_to_foot = new QAction("foot", this); from_mm->addAction(mm_to_foot); connect(mm_to_foot, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_foot);
            mm_to_yard = new QAction("yard", this); from_mm->addAction(mm_to_yard); connect(mm_to_yard, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_yard);
            mm_to_mile = new QAction("mile", this); from_mm->addAction(mm_to_mile); connect(mm_to_mile, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_mile);
            mm_to_km = new QAction("km", this); from_mm->addAction(mm_to_km);  connect(mm_to_km, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_km);
            mm_to_nautical_mile = new QAction("nautical mile", this); from_mm->addAction(mm_to_nautical_mile);  connect(mm_to_nautical_mile, &QAction::triggered, this, &pop_up_unit_converter::SLOT_mm_to_nautical_mile);


    MORE = new QMenu("(more)", this);
        LENGTH = new QMenu("LENGTH", this);
        MASS = new QMenu("MASS", this);
        MORE->addMenu(LENGTH);
        MORE->addMenu(MASS);

    close_pop_up = new QAction("X"); connect(close_pop_up, &QAction::triggered, this, &pop_up_unit_converter::SLOT_close_pop_up);

    Menu_Options->addMenu(from_inches);
    Menu_Options->addMenu(from_mm);
    Menu_Options->addMenu(MORE);
    Menu_Options->addAction(close_pop_up);



}

void pop_up_unit_converter::showDrillSelectorInches()
{

    double value = double_from_clipboard_string();
    DrillSelector->setInputValue(value);
    DrillSelector->useInches();
    DrillSelector->reCalc();
    DrillSelector->setLocation(QCursor::pos());
    DrillSelector->show();
    this->hide();
}
void pop_up_unit_converter::showDrillSelectorMillis()
{

    double value = double_from_clipboard_string();
    DrillSelector->setInputValue(value);
    DrillSelector->useMillis();
    DrillSelector->reCalc();
    DrillSelector->setLocation(QCursor::pos());
    DrillSelector->show();
    this->hide();
}

void pop_up_unit_converter::paintEvent(QPaintEvent *event)
{
    mm_to_inch->setText("inch: \t" + double_to_string(double_from_clipboard_string() / 25.4));
    mm_to_micron->setText("micron: \t" + double_to_string(double_from_clipboard_string() * 1000));
    mm_to_cm->setText("cm: \t" + double_to_string(double_from_clipboard_string() / 10));
    mm_to_meter->setText("meter: \t" + double_to_string(double_from_clipboard_string() / 1000));
    mm_to_nm->setText("nm: \t" + double_to_string(double_from_clipboard_string() * 1000000));
    mm_to_foot->setText("foot: \t" + double_to_string(double_from_clipboard_string() / 304.8));
    mm_to_yard->setText("yard: \t" + double_to_string(double_from_clipboard_string() / 914));
    mm_to_mile->setText("mile: \t" + double_to_string(double_from_clipboard_string() / 1609000));
    mm_to_km->setText("km: \t" + double_to_string(double_from_clipboard_string() / 1000000));
    mm_to_nautical_mile->setText("nautical mile: \t" + double_to_string(double_from_clipboard_string() / 1852000));

    inch_to_mm->setText("mm: \t" + double_to_string(double_from_clipboard_string() * 25.4));
    inch_to_micron->setText("micron: \t" + double_to_string(double_from_clipboard_string() * 25400));
    inch_to_nm->setText("nm: \t" + double_to_string(double_from_clipboard_string() * 25400000));
    inch_to_cm->setText("cm: \t" + double_to_string(double_from_clipboard_string() * 2.54));
    inch_to_meter->setText("meter: \t" + double_to_string(double_from_clipboard_string() / 39.37));
    inch_to_foot->setText("foot: \t" + double_to_string(double_from_clipboard_string() / 12));
    inch_to_yard->setText("yard: \t" + double_to_string(double_from_clipboard_string() / 36));
    inch_to_mile->setText("mile: \t" + double_to_string(double_from_clipboard_string() / 63360));
    inch_to_km->setText("km: \t" + double_to_string(double_from_clipboard_string() / 39370));
    inch_to_nautical_mile->setText("nautical mile: \t" + double_to_string(double_from_clipboard_string() / 72913));
}

void pop_up_unit_converter::paste_conversion(double &num)
{
    clipboard->setText(double_to_string(num));
    hide();
    ::Sleep(100);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(0x56, 0, 0, 0);
    ::Sleep(10);
    keybd_event(0x56,0,KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP, 0);
    //qDebug() << QString::number(num * 25.4, 'G', 100) << " CHACHACHA.";
}

QString pop_up_unit_converter::double_to_string(double value)
{
    QString returnString = QString::number(value, 'G', 5);
    //returnString.remove( QRegExp("0+$") ); // Remove any number of trailing 0's
    //returnString.remove( QRegExp("\\.$") ); // If the last character is just a '.' then remove it
    return returnString;
}

void pop_up_unit_converter::SLOT_inch_to_mm()
{
    double converted_value = double_from_clipboard_string() * 25.4;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_foot()
{
    double converted_value = double_from_clipboard_string() / 12;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_yard()
{
    double converted_value = double_from_clipboard_string() / 36;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_mile()
{
    double converted_value = double_from_clipboard_string() / 63360;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_micron()
{
    double converted_value = double_from_clipboard_string() * 25400;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_meter()
{
    double converted_value = double_from_clipboard_string() / 39.37;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_cm()
{
    double converted_value = double_from_clipboard_string() * 2.54;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_km()
{
     double converted_value = double_from_clipboard_string() / 39370;
     paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_nm()
{
    double converted_value = double_from_clipboard_string() * 25400000;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_inch_to_nautical_mile()
{
    double converted_value = double_from_clipboard_string() / 72913;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_inch()
{
    double converted_value = double_from_clipboard_string() / 25.4;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_foot()
{
    double converted_value = double_from_clipboard_string() / 304.8;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_yard()
{
    double converted_value = double_from_clipboard_string() / 914;  //approximate
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_mile()
{
    double converted_value = double_from_clipboard_string() / (1690000); //approximate
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_micron()
{
    double converted_value = double_from_clipboard_string() * 1000;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_meter()
{
    double converted_value = double_from_clipboard_string() / 1000;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_km()
{
    double converted_value = double_from_clipboard_string() / 1000000;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_nm()
{
    double converted_value = double_from_clipboard_string() * 1000000;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_cm()
{
    double converted_value = double_from_clipboard_string() / 10;
    paste_conversion(converted_value);
}

void pop_up_unit_converter::SLOT_mm_to_nautical_mile()
{
    double converted_value = double_from_clipboard_string() / 1852000; //approx.
    paste_conversion(converted_value);
}

double pop_up_unit_converter::double_from_clipboard_string()
{
    QString text = clipboard->text();
    text.remove(",");
    QTextStream floatTextStream(&text);
    double converted_value;
    floatTextStream << qSetRealNumberPrecision(100);
    floatTextStream >> converted_value;
    return converted_value;
}

void pop_up_unit_converter::SLOT_close_pop_up()
{
    hide();
}

void pop_up_unit_converter::mouseMoveEvent(QMouseEvent *event)
{
    //QPoint local_mouse_pos(event->x(), event->y());
    //QPoint mouse_pos = mapToGlobal(local_mouse_pos);
    //setGeometry(mouse_pos.x() - 150, mouse_pos.y() - 220, 300, 200);
    //update();
    //Q_ASSERT(event);

    //Restart timer if we're moving around
    inactivity_timer->stop();
}

void pop_up_unit_converter::leaveEvent(QEvent *event)
{
   inactivity_timer->start(15000);
}

void pop_up_unit_converter::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        hide();
    }
}
