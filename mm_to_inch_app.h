#ifndef MM_TO_INCH_APP_H
#define MM_TO_INCH_APP_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "windows.h" // Connect WinAPI library
#include "pop_up_unit_converter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mm_to_inch_app; }
QT_END_NAMESPACE

class mm_to_inch_app : public QMainWindow
{
    Q_OBJECT

public:
    mm_to_inch_app(QWidget *parent = nullptr);
    ~mm_to_inch_app();
    pop_up_unit_converter *converter;
    virtual void changeEvent(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
protected:
    // The method for processing native events from the OS in Qt
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::mm_to_inch_app *ui;
    QSystemTrayIcon *trayIcon;
    QClipboard *clipboard;

};
#endif // MM_TO_INCH_APP_H
