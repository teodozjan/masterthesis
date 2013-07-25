//  
// File:   Queue_gui.h
// Author: kamil
//
// Created on 6 kwiecień 2008, 13:23
//


#ifndef _QUEUE_GUI_H
#define	_QUEUE_GUI_H

#include "ui_Queue_gui.h"
#include "Queue.h"
#include <string>

class QueueStatLoggger;
/* class ILog { */
/* public: */
/*   virtual ~ILog (void) {}; */
/*   virtual void Set (double val) = 0; */
/* }; */



class myQtApp : public QWidget, private Ui::Form {
    Q_OBJECT
private:
    bool RunStatus;  
    IRandVal *rvCall;
    IRandVal *rvLen;
    QueueStatLoggger *avgLog;
    
    USERS* Users;
    SYSTEM* System;
    SERVERS *Servers;
    int MaxSimTimeVal;
    int SimTime;
    int MaxTime;
   
    int SimPr;
    SimParams *SimulationParameters;
   
   
    int NumSrvr;
    int NumUser;
    int QueLen;
    double Atot;
    double CLen;
    int Stts;
    int start_time;

    
    void RefreshData(void);
   
    
public:
    myQtApp(QWidget *parent = 0);
    
    
public slots:
    void StartStop();
    void ToTheEnd();
    
};
#endif	/* _QUEUE_GUI_H */

