//
// File:   Main.cc
// Author: kamil
//
// Created on 6 kwiecień 2008, 09:41
//


//#include "Queue.h"
#include <QApplication>
#include <QPushButton>
#include "Queue_gui.h"




int main(int argc,   char** argv) {
    
    QApplication app(argc, argv);
    
    myQtApp hello;
    
    hello.show();
    return app.exec();
    
}




