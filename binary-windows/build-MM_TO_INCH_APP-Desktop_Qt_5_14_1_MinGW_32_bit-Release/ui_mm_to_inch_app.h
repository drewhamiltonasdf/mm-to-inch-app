/********************************************************************************
** Form generated from reading UI file 'mm_to_inch_app.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MM_TO_INCH_APP_H
#define UI_MM_TO_INCH_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mm_to_inch_app
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mm_to_inch_app)
    {
        if (mm_to_inch_app->objectName().isEmpty())
            mm_to_inch_app->setObjectName(QString::fromUtf8("mm_to_inch_app"));
        mm_to_inch_app->resize(800, 600);
        centralwidget = new QWidget(mm_to_inch_app);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        mm_to_inch_app->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mm_to_inch_app);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        mm_to_inch_app->setMenuBar(menubar);
        statusbar = new QStatusBar(mm_to_inch_app);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mm_to_inch_app->setStatusBar(statusbar);

        retranslateUi(mm_to_inch_app);

        QMetaObject::connectSlotsByName(mm_to_inch_app);
    } // setupUi

    void retranslateUi(QMainWindow *mm_to_inch_app)
    {
        mm_to_inch_app->setWindowTitle(QCoreApplication::translate("mm_to_inch_app", "mm_to_inch_app", nullptr));
        label->setText(QCoreApplication::translate("mm_to_inch_app", "MM_TO_INCH CONVERSION APP (Minimizes to tray)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mm_to_inch_app: public Ui_mm_to_inch_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MM_TO_INCH_APP_H
