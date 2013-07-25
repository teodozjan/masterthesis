/********************************************************************************
** Form generated from reading ui file 'Queue_gui.ui'
**
** Created: Sat Oct 25 17:30:04 2008
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QUEUE_GUI_H
#define UI_QUEUE_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *startButton;
    QPushButton *ToEnd;
    QLabel *label_3;
    QSpinBox *MaxSimTime;
    QTabWidget *EventTabs;
    QWidget *tab;
    QLabel *label;
    QSpinBox *ServersNum;
    QWidget *tab_2;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_2;
    QSpinBox *QueueSize;
    QLabel *label_18;
    QSpinBox *WaitLen;
    QLabel *label_21;
    QComboBox *Discipline;
    QWidget *tab_3;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QSpinBox *UserNum;
    QComboBox *EventLength;
    QLabel *label_13;
    QSpinBox *TrafficLen;
    QLabel *label_11;
    QLabel *label_10;
    QDoubleSpinBox *TrafficDen;
    QWidget *tab_4;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLCDNumber *LCDServed;
    QLabel *label_8;
    QLCDNumber *LCDRejected;
    QLabel *label_9;
    QLCDNumber *LCDAll;
    QLabel *label_7;
    QLabel *label_14;
    QLCDNumber *LCDGOS;
    QLabel *label_15;
    QLCDNumber *LCDA;
    QLabel *label_16;
    QLCDNumber *LCDErr;
    QLabel *label_19;
    QLCDNumber *LCDQueUsage;
    QLabel *label_12;
    QLCDNumber *LCDReallyQueued;
    QLabel *label_20;
    QLCDNumber *LCDAvgWait;
    QPushButton *QuiT;
    QProgressBar *ProgressSim;
    QProgressBar *ProgressGOS;
    QLabel *label_5;
    QLabel *label_6;
    QLCDNumber *LCDClock;
    QLabel *LCDCLockLabel;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(873, 357);
    startButton = new QPushButton(Form);
    startButton->setObjectName(QString::fromUtf8("startButton"));
    startButton->setGeometry(QRect(250, 10, 113, 29));
    ToEnd = new QPushButton(Form);
    ToEnd->setObjectName(QString::fromUtf8("ToEnd"));
    ToEnd->setEnabled(false);
    ToEnd->setGeometry(QRect(380, 10, 113, 29));
    label_3 = new QLabel(Form);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(40, 20, 92, 18));
    MaxSimTime = new QSpinBox(Form);
    MaxSimTime->setObjectName(QString::fromUtf8("MaxSimTime"));
    MaxSimTime->setGeometry(QRect(140, 10, 106, 29));
    MaxSimTime->setMinimum(1);
    MaxSimTime->setMaximum(999999999);
    MaxSimTime->setSingleStep(60);
    MaxSimTime->setValue(500000);
    EventTabs = new QTabWidget(Form);
    EventTabs->setObjectName(QString::fromUtf8("EventTabs"));
    EventTabs->setGeometry(QRect(10, 60, 551, 281));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    label = new QLabel(tab);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(20, 30, 94, 18));
    ServersNum = new QSpinBox(tab);
    ServersNum->setObjectName(QString::fromUtf8("ServersNum"));
    ServersNum->setGeometry(QRect(120, 20, 106, 29));
    ServersNum->setMinimum(1);
    ServersNum->setMaximum(999999999);
    ServersNum->setValue(50);
    EventTabs->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    formLayoutWidget_3 = new QWidget(tab_2);
    formLayoutWidget_3->setObjectName(QString::fromUtf8("formLayoutWidget_3"));
    formLayoutWidget_3->setGeometry(QRect(10, 10, 401, 158));
    formLayout_3 = new QFormLayout(formLayoutWidget_3);
    formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
    formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout_3->setContentsMargins(0, 0, 0, 0);
    label_2 = new QLabel(formLayoutWidget_3);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    formLayout_3->setWidget(0, QFormLayout::LabelRole, label_2);

    QueueSize = new QSpinBox(formLayoutWidget_3);
    QueueSize->setObjectName(QString::fromUtf8("QueueSize"));
    QueueSize->setMaximum(999999999);
    QueueSize->setSingleStep(10);
    QueueSize->setValue(200);

    formLayout_3->setWidget(0, QFormLayout::FieldRole, QueueSize);

    label_18 = new QLabel(formLayoutWidget_3);
    label_18->setObjectName(QString::fromUtf8("label_18"));

    formLayout_3->setWidget(1, QFormLayout::LabelRole, label_18);

    WaitLen = new QSpinBox(formLayoutWidget_3);
    WaitLen->setObjectName(QString::fromUtf8("WaitLen"));
    WaitLen->setMaximum(999999999);
    WaitLen->setSingleStep(10);
    WaitLen->setValue(90);

    formLayout_3->setWidget(1, QFormLayout::FieldRole, WaitLen);

    label_21 = new QLabel(formLayoutWidget_3);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    formLayout_3->setWidget(2, QFormLayout::LabelRole, label_21);

    Discipline = new QComboBox(formLayoutWidget_3);
    Discipline->setObjectName(QString::fromUtf8("Discipline"));

    formLayout_3->setWidget(2, QFormLayout::FieldRole, Discipline);

    EventTabs->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    formLayoutWidget_2 = new QWidget(tab_3);
    formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
    formLayoutWidget_2->setGeometry(QRect(10, 10, 331, 161));
    formLayout_2 = new QFormLayout(formLayoutWidget_2);
    formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
    formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout_2->setContentsMargins(0, 0, 0, 0);
    label_4 = new QLabel(formLayoutWidget_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

    UserNum = new QSpinBox(formLayoutWidget_2);
    UserNum->setObjectName(QString::fromUtf8("UserNum"));
    UserNum->setMaximum(999999999);
    UserNum->setValue(200);

    formLayout_2->setWidget(0, QFormLayout::FieldRole, UserNum);

    EventLength = new QComboBox(formLayoutWidget_2);
    EventLength->setObjectName(QString::fromUtf8("EventLength"));

    formLayout_2->setWidget(1, QFormLayout::FieldRole, EventLength);

    label_13 = new QLabel(formLayoutWidget_2);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    formLayout_2->setWidget(1, QFormLayout::LabelRole, label_13);

    TrafficLen = new QSpinBox(formLayoutWidget_2);
    TrafficLen->setObjectName(QString::fromUtf8("TrafficLen"));
    TrafficLen->setMaximum(999999999);
    TrafficLen->setSingleStep(10);
    TrafficLen->setValue(90);

    formLayout_2->setWidget(2, QFormLayout::FieldRole, TrafficLen);

    label_11 = new QLabel(formLayoutWidget_2);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    formLayout_2->setWidget(2, QFormLayout::LabelRole, label_11);

    label_10 = new QLabel(formLayoutWidget_2);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    formLayout_2->setWidget(3, QFormLayout::LabelRole, label_10);

    TrafficDen = new QDoubleSpinBox(formLayoutWidget_2);
    TrafficDen->setObjectName(QString::fromUtf8("TrafficDen"));
    TrafficDen->setMaximum(100000);
    TrafficDen->setValue(37.9);

    formLayout_2->setWidget(3, QFormLayout::FieldRole, TrafficDen);

    EventTabs->addTab(tab_3, QString());
    tab_4 = new QWidget();
    tab_4->setObjectName(QString::fromUtf8("tab_4"));
    formLayoutWidget = new QWidget(tab_4);
    formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
    formLayoutWidget->setGeometry(QRect(20, 0, 331, 241));
    formLayout = new QFormLayout(formLayoutWidget);
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->setContentsMargins(0, 0, 0, 0);
    LCDServed = new QLCDNumber(formLayoutWidget);
    LCDServed->setObjectName(QString::fromUtf8("LCDServed"));
    LCDServed->setNumDigits(10);
    LCDServed->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(0, QFormLayout::FieldRole, LCDServed);

    label_8 = new QLabel(formLayoutWidget);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    formLayout->setWidget(1, QFormLayout::LabelRole, label_8);

    LCDRejected = new QLCDNumber(formLayoutWidget);
    LCDRejected->setObjectName(QString::fromUtf8("LCDRejected"));
    LCDRejected->setNumDigits(10);
    LCDRejected->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(1, QFormLayout::FieldRole, LCDRejected);

    label_9 = new QLabel(formLayoutWidget);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

    LCDAll = new QLCDNumber(formLayoutWidget);
    LCDAll->setObjectName(QString::fromUtf8("LCDAll"));
    LCDAll->setNumDigits(10);
    LCDAll->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(2, QFormLayout::FieldRole, LCDAll);

    label_7 = new QLabel(formLayoutWidget);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    formLayout->setWidget(0, QFormLayout::LabelRole, label_7);

    label_14 = new QLabel(formLayoutWidget);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    formLayout->setWidget(3, QFormLayout::LabelRole, label_14);

    LCDGOS = new QLCDNumber(formLayoutWidget);
    LCDGOS->setObjectName(QString::fromUtf8("LCDGOS"));
    LCDGOS->setSmallDecimalPoint(false);
    LCDGOS->setNumDigits(10);
    LCDGOS->setSegmentStyle(QLCDNumber::Flat);
    LCDGOS->setProperty("value", QVariant(0));

    formLayout->setWidget(3, QFormLayout::FieldRole, LCDGOS);

    label_15 = new QLabel(formLayoutWidget);
    label_15->setObjectName(QString::fromUtf8("label_15"));

    formLayout->setWidget(4, QFormLayout::LabelRole, label_15);

    LCDA = new QLCDNumber(formLayoutWidget);
    LCDA->setObjectName(QString::fromUtf8("LCDA"));
    LCDA->setNumDigits(10);
    LCDA->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(4, QFormLayout::FieldRole, LCDA);

    label_16 = new QLabel(formLayoutWidget);
    label_16->setObjectName(QString::fromUtf8("label_16"));

    formLayout->setWidget(5, QFormLayout::LabelRole, label_16);

    LCDErr = new QLCDNumber(formLayoutWidget);
    LCDErr->setObjectName(QString::fromUtf8("LCDErr"));
    LCDErr->setNumDigits(10);
    LCDErr->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(5, QFormLayout::FieldRole, LCDErr);

    label_19 = new QLabel(formLayoutWidget);
    label_19->setObjectName(QString::fromUtf8("label_19"));

    formLayout->setWidget(6, QFormLayout::LabelRole, label_19);

    LCDQueUsage = new QLCDNumber(formLayoutWidget);
    LCDQueUsage->setObjectName(QString::fromUtf8("LCDQueUsage"));
    LCDQueUsage->setNumDigits(10);
    LCDQueUsage->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(6, QFormLayout::FieldRole, LCDQueUsage);

    label_12 = new QLabel(formLayoutWidget);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    formLayout->setWidget(7, QFormLayout::LabelRole, label_12);

    LCDReallyQueued = new QLCDNumber(formLayoutWidget);
    LCDReallyQueued->setObjectName(QString::fromUtf8("LCDReallyQueued"));
    LCDReallyQueued->setNumDigits(10);
    LCDReallyQueued->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(7, QFormLayout::FieldRole, LCDReallyQueued);

    label_20 = new QLabel(formLayoutWidget);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    formLayout->setWidget(8, QFormLayout::LabelRole, label_20);

    LCDAvgWait = new QLCDNumber(formLayoutWidget);
    LCDAvgWait->setObjectName(QString::fromUtf8("LCDAvgWait"));
    LCDAvgWait->setNumDigits(10);
    LCDAvgWait->setSegmentStyle(QLCDNumber::Flat);

    formLayout->setWidget(8, QFormLayout::FieldRole, LCDAvgWait);

    EventTabs->addTab(tab_4, QString());
    QuiT = new QPushButton(Form);
    QuiT->setObjectName(QString::fromUtf8("QuiT"));
    QuiT->setGeometry(QRect(510, 10, 113, 29));
    ProgressSim = new QProgressBar(Form);
    ProgressSim->setObjectName(QString::fromUtf8("ProgressSim"));
    ProgressSim->setGeometry(QRect(580, 70, 271, 23));
    ProgressSim->setValue(0);
    ProgressGOS = new QProgressBar(Form);
    ProgressGOS->setObjectName(QString::fromUtf8("ProgressGOS"));
    ProgressGOS->setGeometry(QRect(580, 130, 271, 23));
    ProgressGOS->setValue(0);
    label_5 = new QLabel(Form);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(580, 50, 104, 18));
    label_6 = new QLabel(Form);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(580, 110, 141, 18));
    LCDClock = new QLCDNumber(Form);
    LCDClock->setObjectName(QString::fromUtf8("LCDClock"));
    LCDClock->setGeometry(QRect(780, 160, 64, 23));
    LCDCLockLabel = new QLabel(Form);
    LCDCLockLabel->setObjectName(QString::fromUtf8("LCDCLockLabel"));
    LCDCLockLabel->setGeometry(QRect(590, 160, 171, 18));

    retranslateUi(Form);

    EventTabs->setCurrentIndex(3);


    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Praca inzynierska -- symulator", 0, QApplication::UnicodeUTF8));
    startButton->setText(QApplication::translate("Form", "Start", 0, QApplication::UnicodeUTF8));
    ToEnd->setText(QApplication::translate("Form", "Do ko\305\204ca", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Form", "Czas symulacji", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Form", "Ilo\305\233\304\207 serwer\303\263w", 0, QApplication::UnicodeUTF8));
    EventTabs->setTabText(EventTabs->indexOf(tab), QApplication::translate("Form", "Serwery", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Form", "Rozmiar kolejki", 0, QApplication::UnicodeUTF8));
    label_18->setText(QApplication::translate("Form", "Maksymalny czas czekania", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("Form", "Dyscyplina kolejki", 0, QApplication::UnicodeUTF8));
    Discipline->clear();
    Discipline->insertItems(0, QStringList()
     << QApplication::translate("Form", "FIFO", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "LIFO", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "RANDOM", 0, QApplication::UnicodeUTF8)
    );
    EventTabs->setTabText(EventTabs->indexOf(tab_2), QApplication::translate("Form", "Kolejka", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Form", "Ilo\305\233\304\207 u\305\274ytkownik\303\263w", 0, QApplication::UnicodeUTF8));
    EventLength->clear();
    EventLength->insertItems(0, QStringList()
     << QApplication::translate("Form", "Const", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "Wyk\305\202adniczy", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "Normalny", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "Poissona", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form", "Erlanga", 0, QApplication::UnicodeUTF8)
    );
    label_13->setText(QApplication::translate("Form", "Czas trwania", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("Form", "\305\232redni czas trwania", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("Form", "Nat\304\231\305\274enie ruchu", 0, QApplication::UnicodeUTF8));
    EventTabs->setTabText(EventTabs->indexOf(tab_3), QApplication::translate("Form", "U\305\274ytkownicy", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("Form", "Zdarzenia odrzucone", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("Form", "Zdarzenia razem", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("Form", "Zdarzenia obs\305\202u\305\274one", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("Form", "Poziom dost\304\231pu", 0, QApplication::UnicodeUTF8));
    label_15->setText(QApplication::translate("Form", "Nat\304\231\305\274enie ruchu", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("Form", "Odchy\305\202ka nat\304\231\305\274enia ruchu", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("Form", "Zaj\304\231to\305\233\304\207 kolejki", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("Form", "Zdarzenia zakolejkowane", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("Form", "\305\232redni czas czekania", 0, QApplication::UnicodeUTF8));
    EventTabs->setTabText(EventTabs->indexOf(tab_4), QApplication::translate("Form", "Statystyki obiekt\303\263w", 0, QApplication::UnicodeUTF8));
    QuiT->setText(QApplication::translate("Form", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Form", "Post\304\231p symulacji", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Form", "Zdarze\305\204 obs\305\202u\305\274onych", 0, QApplication::UnicodeUTF8));
    LCDCLockLabel->setText(QApplication::translate("Form", "Czas symulacji", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUEUE_GUI_H
