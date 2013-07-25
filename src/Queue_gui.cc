#include <Qt/QtGui>

#include "Queue_gui.h"
#include "Queue.h"
#include <iostream>
#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include "Stts.cc"
//---------------------------------------------------------------------------
//  Log
//---------------------------------------------------------------------------

class QueueStatLoggger {
private:
    double sum, avg;
    int mxStp, crStp;
    FILE *f;
public:
    QueueStatLoggger (char *pth, int mxStp=50000);
    ~QueueStatLoggger (void);
    void Set (double val);
    double Avg (void);
};

  QueueStatLoggger::QueueStatLoggger (char *pth, int mxStp) : mxStp(mxStp)
    {
      sum = 0.0;
      crStp = 0;
      f = pth? fopen(pth, "wt"): NULL;
    };
    QueueStatLoggger::~QueueStatLoggger (void)
    {
      if (f)
        fclose(f);
    }
    void QueueStatLoggger::Set (double val)
    {
      crStp++;
      sum += val;

	if (f && crStp<mxStp)
        fprintf(f, "%10i\t%15f\n", crStp, val);
    }

myQtApp::myQtApp(QWidget *parent) {
  setupUi(this); // this sets up GUI
  RunStatus=false;
  // signals/slots mechanism in action
  connect( startButton, SIGNAL( clicked() ), this, SLOT( StartStop() ) );
  connect( ToEnd, SIGNAL( clicked() ), this, SLOT( ToTheEnd() ) );
  connect( QuiT, SIGNAL( clicked() ), this, SLOT(close() ) );
}

void myQtApp::StartStop() {
  if(!RunStatus){
    avgLog = new QueueStatLoggger("xyGOSlog.xy", MaxSimTime->value());
    start_time = time(NULL);
    EventTabs->setCurrentIndex(3);
    std::cout << "Start!\n";
    startButton->setText("Stop");
    RunStatus=true;
    SimulationParameters= new SimParams();
        
    //Czas symulacji
    SimulationParameters->TimeOfSimulation = MaxSimTime->value();	
        
    // Pewnie ilość serwerów
    SimulationParameters->NumberOfServers = ServersNum->value();
        
    //Ilość userów
    SimulationParameters->NumberOfUsers = UserNum->value();
	
        
    // Długość kolejki
    SimulationParameters->LengthOfQueue = QueueSize->value();
        
    //Natężenie ruchu
    SimulationParameters->DensityOfTraffic = TrafficDen->value();

    //Średni czas obsługi
    SimulationParameters->ModerateServiceTime = TrafficLen->value();

    //Czy statystyki
    SimulationParameters->GenerateStats = true;
        
        
        
    /* Jeszcze raz piszemy to samo dla kompatybilnosci wstecz */
    MaxTime = SimulationParameters->TimeOfSimulation;
    NumSrvr = SimulationParameters->NumberOfServers;
    NumUser = SimulationParameters->NumberOfUsers;
    QueLen  = SimulationParameters->LengthOfQueue;
    Atot = SimulationParameters->DensityOfTraffic;
    CLen = SimulationParameters->ModerateServiceTime;
    Stts = SimulationParameters->GenerateStats;
    ////////////////////

    IRandVal *rvLen;
    switch(EventLength->currentIndex()){
    case 0:
      rvLen  = new rvCnst(CLen);
      break;
    case 1:
      rvLen  = new rvExp(CLen);
      break;
    case 2:
      rvLen = new rvNormal(CLen,12);
      break;
    case 3:
      rvLen = new rvPoisson(CLen);
      break;
    case 4:
      rvLen = new rvErlang(CLen,12);
      break;
    default:
      std::cout << "EventLength: Unknown distribution\n";
      throw;
    }

    IRandVal *rvWait;
    int waitTime = WaitLen->value();
    // switch(WaitL->currentIndex()){
//     case 0:
       rvWait=new rvCnst(waitTime);
//       break;
//     case 1:
//       rvWait=new rvExp(waitTime);
//       break;
//     case 2:
//       rvWait = new rvNormal(waitTime,12);
//       break;
//     case 3:
//       rvWait = new rvPoisson(waitTime);
//       break;
//     case 4:
//       rvWait= new rvErlang(waitTime, 12);
//       break;
//     default:
//       std::cout << "WaitTime:Unknown distribution\n";
//       throw;
//     }       

    
    
    IRandVal *rvCall = new rvBin(Atot/CLen/NumUser);
    std::cout << "\nAtot " << Atot 
	      << "\nClen " << CLen 
	      << "\nNumUser " << NumUser 
	      << "\nMaxtime " << MaxTime
	      << "\nLambda"<< Atot/CLen/NumUser;

    long double x = 1;
    x*=Atot;
    x/=CLen;
    x*= MaxTime;
    x/= NumUser;

     
    
    //IRandVal *rvLen  = new rvExp(CLen);
    /// IRandVal *rvLen  = new rvCnst (CLen);
        
    System = new SYSTEM(QueLen, NumSrvr, Stts);
    Users = new USERS(System, NumUser, rvCall, rvLen, rvWait, Stts);
        
        
    /* Kompilator nie lubi niejawnej konwersji */
    int aa = (int)(Atot<NumSrvr? Atot+0.5: NumSrvr);
    /* Wstępne wypełnianie kolejki serwerów */
    for (int ne=0; ne<aa; ne++) {
      int LifeSpan = 0;
      while (!LifeSpan) LifeSpan = rvLen->Val();
      EVENT *E = new EVENT(NULL, LifeSpan);
      System->Servers->FreeSrv()->TakeEvent(E);
    }
      

            
            
    ToEnd->setEnabled(true);
        
    //
  }else{
    std::cout << "Stop!\n";
    startButton->setText("Start");
    RunStatus=false;
    ToEnd->setEnabled(false);
    std::cout << "Gui stopped\n";
    
    if(Users) {
      std::cout << "-Freeing of Users\n";
      delete Users;
    }else {
      std::cout << "!Double free of Users\n";
      throw;
    }
    if(System){
      std::cout << "-Freeing System\n";
      delete System;
    }else{ 
      std::cout << "!Double free of System\n";
      throw;
    }
    if(SimulationParameters){
      std::cout << "-Freeing SimulationParameters\n";
      delete SimulationParameters; 
    }else{ 
      std::cout << "!Double free of Users\n";
      throw;
    }

  }
    
}


void myQtApp::ToTheEnd() {
  ToEnd->setEnabled(false); 
  int lastMaxTime= MaxTime; 
  

  
  for( SimTime=1; SimTime<=MaxTime; SimTime++)
    {
      ///500000 zapisow do pliku --> zaboli
      double aGOS = 100*(1.0-System->stGradeOfService->Avg());
      aGOS = aGOS==100.0? 0:aGOS;
      avgLog->Set(aGOS);
      

      if (MaxTime != lastMaxTime){std::cout << "Timing problem\n"; throw;    }
    
      Users->GenTraffic();
      System->Work();
      
      /* Nie ma sensu za każdym razem gui updatować */
      if(SimTime%100==0 || SimTime==MaxTime)
	{

	  
	  //SttsSmp* stServedEventsRef = (SttsSmp*)System->stServedEvents;
	  SttsTab *stCalLen = (SttsTab*)Users->stCalLen;

	  ProgressSim->setValue(100*SimTime/MaxTime);
	  ProgressGOS->setValue(100*System->stGradeOfService->Avg()+0.5);
	  LCDGOS->display(100-100*System->stGradeOfService->Avg());	
	  
	  SttsSmp* GOS= (SttsSmp*)System->stGradeOfService;
	  LCDAll->display(GOS->returnSum());
	  SttsTab *stQueWaitTime = (SttsTab*)System->stQueueWaitingTime;
	  LCDAvgWait->display(stQueWaitTime->Avg());
	  int timediff = time(NULL) - start_time;
	  LCDClock->display(timediff);

	  // FIXME: Jeśli kolejka jest mała to wychodzi błąd natężenia ruchu
	  double  A = stCalLen->returnSum()/MaxTime;

	  //double  A = stCalLen->Avg();
	  LCDA->display(A);
	  LCDErr->display(Atot - A);
	  LCDRejected->display(
 			       System->reallyRejected
 			       +System->Queue->waitedTooLong);

	  LCDServed->display(GOS->Get(System->SERVED));
	 
	  LCDQueUsage->display(System->Queue->Len());

	  // SimulationParameters->pb = 100*(1.0-System->stGradeOfService->Avg());
// 	  SimulationParameters->nb = 0;
// 	  SimulationParameters->qa = System->stServedEvents->Avg();
// 	  SimulationParameters->nz = System->stServedEvents->Avg();
// 	  SimulationParameters->pr =  100.0*SimTime/MaxTime;
	  
	}
    
    }

  std::cout << "Symulacja zakończona\n";

  FILE *log = fopen("Log.txt", "at");
  fprintf(log, "%12i\t%6i\t%6i\t%6i\t%10.2f\t%10.2f\t%10.2f\t%10.2f\n",
	  MaxTime, NumSrvr, NumUser, QueLen,
	  Atot, CLen, 100*(1.0-System->stGradeOfService->Avg()),
	  System->stServedEvents->Avg()
	  );
  fclose(log);

  delete avgLog;



}



void myQtApp::RefreshData(){
  //std::cout
    
    
}


