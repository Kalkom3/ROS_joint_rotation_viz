#ifndef UI_MYPLUGIN_H
#define UI_MYPLUGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QWidget>
#include <QGraphicsItem>
#include <QComboBox>


QT_BEGIN_NAMESPACE

class Ui_MyPlugin
{
public:
    
    QWidget *centralwidget;
    QComboBox *topics_names;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QLabel *pos_text[4];
    QLabel *topic_label;
    QStatusBar *statusbar;
    QPushButton *okButton;
    QPushButton *refreshButton;
    void setupUi(QMainWindow *MyPlugin)
    {
        if (MyPlugin->objectName().isEmpty())
            MyPlugin->setObjectName(QStringLiteral("MyPlugin"));
        MyPlugin->resize(800, 600);
        centralwidget = new QWidget(MyPlugin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(80, 80, 320, 320));

        okButton = new QPushButton(centralwidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(0, 0, 50, 40));

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        refreshButton->setGeometry(QRect(50, 0, 100, 40));

        topics_names = new QComboBox(centralwidget);
        topics_names->setObjectName(QStringLiteral("topics_names"));
        topics_names->setGeometry(QRect(150,0,250,30));

        topic_label = new QLabel(centralwidget);
        topic_label->setObjectName(QStringLiteral("topic_label"));
        topic_label->setGeometry(QRect(120,30,250,40));

        pos_text[0] = new QLabel(centralwidget);
        pos_text[0]->setObjectName(QStringLiteral("Pos1_text"));
        pos_text[0]->setGeometry(QRect(20, 130, 100, 40));

        pos_text[1] = new QLabel(centralwidget);
        pos_text[1]->setObjectName(QStringLiteral("Pos2_text"));
        pos_text[1]->setGeometry(QRect(20, 300, 100, 40));

        pos_text[2] = new QLabel(centralwidget);
        pos_text[2]->setObjectName(QStringLiteral("Pos3_text"));
        pos_text[2]->setGeometry(QRect(400, 130, 100, 40));

        pos_text[3] = new QLabel(centralwidget);
        pos_text[3]->setObjectName(QStringLiteral("Pos4_text"));
        pos_text[3]->setGeometry(QRect(400, 300, 100, 40));

        MyPlugin->setCentralWidget(centralwidget);
        

        menubar = new QMenuBar(MyPlugin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MyPlugin->setMenuBar(menubar);

        statusbar = new QStatusBar(MyPlugin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MyPlugin->setStatusBar(statusbar);

        retranslateUi(MyPlugin);

        QMetaObject::connectSlotsByName(MyPlugin);
    } // setupUi

    void retranslateUi(QMainWindow *MyPlugin)
    {
        MyPlugin->setWindowTitle(QApplication::translate("MyPlugin", "MyPlugin", Q_NULLPTR));
        okButton->setText(QApplication::translate("MyPlugin","OK",Q_NULLPTR));
        refreshButton->setText(QApplication::translate("MyPlugin","Refresh",Q_NULLPTR));
        topic_label->setText(QApplication::translate("MyPlugin","Saved Topic:",Q_NULLPTR));
        pos_text[0]->setText(QApplication::translate("MyPlugin","Rot=0",Q_NULLPTR));
        pos_text[1]->setText(QApplication::translate("MyPlugin","Rot=0",Q_NULLPTR));
        pos_text[2]->setText(QApplication::translate("MyPlugin","Rot=0",Q_NULLPTR));
        pos_text[3]->setText(QApplication::translate("MyPlugin","Rot=0",Q_NULLPTR));
        
    } // retranslateUi

    

};

namespace Ui {
    class MyPlugin: public Ui_MyPlugin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPLUGIN_H