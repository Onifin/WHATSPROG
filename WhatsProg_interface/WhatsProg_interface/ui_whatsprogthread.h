/********************************************************************************
** Form generated from reading UI file 'whatsprogthread.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHATSPROGTHREAD_H
#define UI_WHATSPROGTHREAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_WhatsProgThread
{
public:

    void setupUi(QDialog *WhatsProgThread)
    {
        if (WhatsProgThread->objectName().isEmpty())
            WhatsProgThread->setObjectName("WhatsProgThread");
        WhatsProgThread->resize(400, 300);

        retranslateUi(WhatsProgThread);

        QMetaObject::connectSlotsByName(WhatsProgThread);
    } // setupUi

    void retranslateUi(QDialog *WhatsProgThread)
    {
        WhatsProgThread->setWindowTitle(QCoreApplication::translate("WhatsProgThread", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WhatsProgThread: public Ui_WhatsProgThread {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHATSPROGTHREAD_H
