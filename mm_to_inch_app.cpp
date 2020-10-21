#include "mm_to_inch_app.h"
#include "ui_mm_to_inch_app.h"
#include <QDebug>
#include <QStyle>



mm_to_inch_app::mm_to_inch_app(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mm_to_inch_app)
{
    ui->setupUi(this);
    /* System Tray Icon is necessary to the application window is not in focus
     * */

    QFile StyleFile(":/Combinear/Combinear.qss");
    StyleFile.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(StyleFile.readAll());
    setStyleSheet(StyleSheet);

    trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    QIcon asdf;
    asdf.addFile(":/icons/Roundicons-100-Free-Solid-Science.ico");
    trayIcon->setIcon(asdf);
    trayIcon->setToolTip("MM TO INCH APP");
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    //Control + Space (Control + C + Space is what makes this work), but Control + Space calls the window (the Ctrl + C) just does the copying.
    RegisterHotKey((HWND)mm_to_inch_app::winId(),   // Set the system identifier of the widget window that will handle the HotKey
                   100,                             // Set identifier HotKey
                   //MOD_ALT | MOD_SHIFT,           // Set modifiers
                   //MOD_ALT,
                   MOD_CONTROL,
                   ' ');                            // We define hotkeys for HotKey

    converter = new pop_up_unit_converter();
    converter->hide();
    this->showMinimized();
    this->setEnabled(false);
    this->setVisible(false);
    this->hide();
}

void mm_to_inch_app::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange) {
        if(isMinimized()) {
            this->hide();
            event->ignore();
        }
    }
}

void mm_to_inch_app::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
    this->hide();
    event->ignore();
    }
}

mm_to_inch_app::~mm_to_inch_app()
{
    delete ui;
}

bool mm_to_inch_app::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    // Transform the message pointer to the MSG WinAPI
    MSG* msg = reinterpret_cast<MSG*>(message);

    // If the message is a HotKey, then ...
    if(msg->message == WM_HOTKEY){
        // ... check HotKey
        if(msg->wParam == 100){
                converter->activateWindow();
                converter->setFocus(); converter->show(); converter->raise();
                converter->setGeometry(QCursor::pos().x(),QCursor::pos().y()-20,200,200);
            }
        return true;
    }
    return false;
}

void mm_to_inch_app::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        !isVisible() ? show() : hide();
        break;
    default:
        break;
    }
}
