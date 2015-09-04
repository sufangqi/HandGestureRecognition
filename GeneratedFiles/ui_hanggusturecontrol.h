/********************************************************************************
** Form generated from reading UI file 'hanggusturecontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANGGUSTURECONTROL_H
#define UI_HANGGUSTURECONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HangGustureControl
{
public:
    QLabel *label_binary;
    QLabel *label_RGB;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSlider *Slider;
    QSlider *Slider_2;
    QSlider *Slider_3;
    QSlider *Slider_4;

    void setupUi(QWidget *HangGustureControl)
    {
        if (HangGustureControl->objectName().isEmpty())
            HangGustureControl->setObjectName(QStringLiteral("HangGustureControl"));
        HangGustureControl->resize(1340, 690);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/sdu.ico"), QSize(), QIcon::Normal, QIcon::Off);
        HangGustureControl->setWindowIcon(icon);
        label_binary = new QLabel(HangGustureControl);
        label_binary->setObjectName(QStringLiteral("label_binary"));
        label_binary->setGeometry(QRect(20, 40, 640, 480));
        label_binary->setFrameShape(QFrame::Box);
        label_RGB = new QLabel(HangGustureControl);
        label_RGB->setObjectName(QStringLiteral("label_RGB"));
        label_RGB->setGeometry(QRect(680, 40, 640, 480));
        label_RGB->setFrameShape(QFrame::Box);
        label = new QLabel(HangGustureControl);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 550, 54, 12));
        label_2 = new QLabel(HangGustureControl);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 550, 54, 12));
        label_3 = new QLabel(HangGustureControl);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(660, 550, 54, 12));
        label_4 = new QLabel(HangGustureControl);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(990, 550, 54, 12));
        widget = new QWidget(HangGustureControl);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 560, 1301, 21));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        Slider = new QSlider(widget);
        Slider->setObjectName(QStringLiteral("Slider"));
        Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Slider);

        Slider_2 = new QSlider(widget);
        Slider_2->setObjectName(QStringLiteral("Slider_2"));
        Slider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Slider_2);

        Slider_3 = new QSlider(widget);
        Slider_3->setObjectName(QStringLiteral("Slider_3"));
        Slider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Slider_3);

        Slider_4 = new QSlider(widget);
        Slider_4->setObjectName(QStringLiteral("Slider_4"));
        Slider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Slider_4);


        retranslateUi(HangGustureControl);

        QMetaObject::connectSlotsByName(HangGustureControl);
    } // setupUi

    void retranslateUi(QWidget *HangGustureControl)
    {
        HangGustureControl->setWindowTitle(QApplication::translate("HangGustureControl", "HangGustureControl", 0));
        label_binary->setText(QString());
        label_RGB->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HangGustureControl: public Ui_HangGustureControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANGGUSTURECONTROL_H
