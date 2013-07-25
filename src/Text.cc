#include <Qt/QtGui>

#include "Queue_gui.h"
#include "Queue.h"
#include <iostream>
#include <time.h>


#include <stdlib.h>
#include <stdio.h>
#include <string>




int main() {
  if(!RunStatus){
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
    switch(EventLength->currentIndex())
      {
      case 0:
	rvLen  = new rvCnst(CLen);
	break;
      case 1:
	rvLen  = new rvExp(CLen);
	break;
      default:
	throw;
      }
    
    //        switch(WaitL->currentIndex()){
    //            case 1:
    //                ipl=new IPpConst(0);
    //                break;
    //            case 0:
    //                ipl=new IPpConst(WaitLen->value());
    //                break;
    //            case 2:
    //                ipl=new IPpExp(WaitLen->value());
    //                break;
    //            default:
    //                throw;
    //        }        
    /* TODO: Dorobic wybor rozkladu */
    IRandVal *rvCall = new rvBin(Atot/CLen/NumUser);
    std::cout << "\nAtot " << Atot 
	      << "\nClen " << CLen 
	      << "\nNumUser " << NumUser 
	      << "\nMaxtime " << MaxTime;
    long double x = 1;
    x*=Atot;
    x/=CLen;
    x*= MaxTime;
    x/= NumUser;

    
    
    //IRandVal *rvLen  = new rvExp(CLen);
    /// IRandVal *rvLen  = new rvCnst (CLen);
        
    System = new SYSTEM(QueLen, NumSrvr, Stts);
    Users = new USERS(System, NumUser, rvCall, rvLen, Stts);
        
        
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
    /////////////////////////////
    delete Users;
    delete System;
    delete SimulationParameters; 
        
  }
    
}


void myQtApp::ToTheEnd() {
  ToEnd->setEnabled(false); 
  int lastMaxTime= MaxTime; 
    
    
  for( SimTime=1; SimTime<=MaxTime; SimTime++)
    {
      if (MaxTime != lastMaxTime) throw;    
    
      Users->GoOn();
      System->GoOn();
      
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
	
	  int timediff = time(NULL) - start_time;
	  LCDClock->display(timediff);

	  // FIXME: Jeśli kolejka jest mała to wychodzi błąd natężenia ruchu
	  double  A = stCalLen->returnSum()/MaxTime;
	  LCDA->display(A);
	  LCDErr->display(Atot - A);
	  LCDRejected->display(
			       System->reallyRejected
			       +System->Queue->waitedTooLong);

	  LCDServed->display(GOS->Get(System->SERVED));
	 
	  LCDQueUsage->display(System->Queue->Len());

	  SimulationParameters->pb = 100*(1.0-System->stGradeOfService->Avg());
	  SimulationParameters->nb = 0;
	  SimulationParameters->qa = System->stServedEvents->Avg();
	  SimulationParameters->nz = System->stServedEvents->Avg();
	  SimulationParameters->pr =  100.0*SimTime/MaxTime;
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



}



void myQtApp::RefreshData(){
  //std::cout
    
    
}


