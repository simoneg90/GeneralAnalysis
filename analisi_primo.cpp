//Programma di test per lo studio di istogrammi

#include "sound.cc"
#include "utility.cc"

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include <iomanip>
#include <fstream>

#include "TStopwatch.h"

#define NUMBER 1000

int main(int argc, char* argv[]){

  /*for(char& c : str){
    if(c=='_')y=1;
    if(y!=1){
    x_axis+=c;
    }
    std::cout<<"Prova: "<<c<<std::endl;
    }*/

  TH1D *histoD[NUMBER];
  TH1F *histoF[NUMBER];
  TH2D *histo2D[NUMBER];
  TH2F *histo2F[NUMBER];
  TCanvas *c[NUMBER];
  TLegend *leg[NUMBER];
  TFile *file[NUMBER];

  TStopwatch time;
  time.Start(true);

  if(argc<=1){
  
    breakLine();
    std::cout<<"Attenzione! Numero di argomenti insufficiente!"<<std::endl;
    std::cout<<"Digitare './analisi --help' per informazioni!"<<std::endl;
    breakLine();
    say("Errore");
    //return 0;
    exit(-1);
  
  }//end if for "just program execution"

  if(strcmp(argv[1],"--help")==0){
    breakLine();
    std::cout<<"Questo programma analizza i file per diverse masse di DM e sovrappone diversi istogrammi"<<std::endl;
    std::cout<<"Utilizzo del programma:"<<std::endl;
    std::cout<<"./analisi nome_file1 nome_file2 nome_file3"<<std::endl;
    breakLine();
    exit(-1);

  }

  //== Segmentation Fault protection ==
  if(argc>NUMBER+1){
    breakLine();
    std::cout<<"ATTENTION! TOO MANY FILE ADDED!"<<std::endl;
    std::cout<<"Exiting program"<<std::endl;
    breakLine();
    exit(-1);
  }

  for(int j=0; j<(argc-1);++j){

    file[j]=TFile::Open(argv[j+1]);
    if(file[j]==0){
      breakLine();
      std::cout<<"ATTENTION! "<<argv[1]<<" doesn't exists!"<<std::endl;
      breakLine();
      exit(-1);

    }//end if (file exists)

  }//end loop over files

  /*}else if(argc<4){
  
    if(strcmp(argv[1],"--help")==0){
    breakLine();
    std::cout<<"Questo programma analizza i file per diverse masse di DM e sovrappone diversi istogrammi"<<std::endl;
    std::cout<<"Utilizzo del programma:"<<std::endl;
    std::cout<<"./analisi nome_file1 nome_file2 nome_file3"<<std::endl;
    breakLine();
    exit(-1);
  
    }else{   //end if "information"
 
    breakLine();
    std::cout<<"Attenzione! Numero di argomenti insufficiente!"<<std::endl;
    std::cout<<"Digitare './analisi --help' per informazioni!"<<std::endl;
    breakLine();
    exit(-1);

    }
    }//end if argc<4

    //Starting the analysis part -- Filling and drawing histos from different datasets
    //First: dataset name

    std::string runFile1="root file num.1";
    runFile1=argv[1];
    std::string runFile2="root file num.2";
    runFile2=argv[2];
    std::string runFile3="root file num.3";
    runFile3=argv[3];

    file[0] = TFile::Open(runFile1.c_str());  //Open file num.1 (first mass)

    if(file[0]==0){

    breakLine();
    std::cout<<argv[1]<<" doesn't exists!"<<std::endl;
    breakLine();
    exit(-1);
    }

    file[1] = TFile::Open(runFile2.c_str());  //Open file num.2 (second mass)
                       
    if(file[1]==0){
                      
    breakLine();
    std::cout<<argv[2]<<" doesn't exists!"<<std::endl;
    breakLine();
    exit(-1);
    }
                     
    file[2] = TFile::Open(runFile3.c_str());  //Open file num.3 (third mass)
                    
    if(file[2]==0){
                   
    breakLine();
    std::cout<<argv[1]<<" doesn't exists!"<<std::endl;
    breakLine();
    exit(-1);
    }
  */              
  breakLine();
  std::cout<<"Launching histo_config script!"<<std::endl;
  LS_config(argv[2],"config_file.txt");
  breakLine();

  ifstream inFile;
  inFile.open("config_file.txt");

  //== Variables declaration ==

  int i=0;
  int histo_type=0; // =1: TH1D; =-1: TH1F; =2: TH2D; =-2 TH2F;
  int key_costraint=0;
  int histoD_counter,histoF_counter,histo2D_counter,histo2F_counter;
  int canvas_counter=0;
  double histo_max=0;
  int histo_index=0;
  std::string word;
  std::string title;
  histoD_counter=histoF_counter=histo2D_counter=histo2F_counter=0;

  std::string x_axis="";
      
  //== STARING LOOP OVER HISTOS ==

  while(inFile.good()){
    inFile>>word;

    //== Segmentation Fault protection ==
    if(histoD_counter>(NUMBER-argc+1) || histoF_counter>(NUMBER-argc+1) || histo2D_counter>(NUMBER-argc+1) || histo2F_counter>(NUMBER-argc+1)){
      breakLine();
      std::cout<<"ATTENTION!!! TOO MANY ARGUMENTS INSERTED!!! PLEASE CHANGE VARIABLE 'NUMBER'"<<std::endl;
      std::cout<<"# TH1D = "<<histoD_counter<<" # TH1F = "<<histoF_counter<<" # TH2D = "<<histo2D_counter<<" # TH2F = "<<histo2F_counter<<std::endl;
      std::cout<<"# Canvas = "<<canvas_counter<<" # File = "<<argc-1<<std::endl;
      breakLine();
      
      std::cout << "------ TIME ELAPSED DURING ANALYSIS  ----- " << time.RealTime() << " s" <<std::endl;

      exit(-1);
    }//end if for Segmentation Fault protection



    if(histo_type!=0){//reading histo name

      std::cout<<"Histo name: "<<(word.substr(0,word.size()-2)).c_str()<<std::endl;
      c[canvas_counter]=new TCanvas(Form("c%d",canvas_counter),Form("c%d",canvas_counter), 200,10,600,400);
      leg[canvas_counter]=new TLegend(0.7,0.7,0.9,0.9);
      for(int y=0; word[y]!='_'&& word[y]!='.';++y){
           
	x_axis+=word[y];

      }

      for(int j=0;j<(argc-1);++j){//Loop over files

        //if(histo_type==1)histo[histo_counter]=((TH1D *)(file1->Get((word.substr(0,word.size()-2)).c_str())));

        if(histo_type==1){
          histoD[histoD_counter]=((TH1D *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())));
	  if((((TH1D *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())))->GetMaximum())>histo_max){
            
            histo_max=((TH1D *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())))->GetMaximum(); 
            histo_index=j;

          }

         
	  histoD[histoD_counter]->SetStats(0);
          TH1D_config(histoD[histoD_counter],"",x_axis.c_str(),"# Events",j+1);
          //leg[canvas_counter]->AddEntry(histoD[histoD_counter],Form("file%d",j),"lp");
          title=argv[j+1];
          leg[canvas_counter]->AddEntry(histoD[histoD_counter],(title.substr(0,title.size()-5)).c_str(),"lp");

          //if(j==0)histoD[histoD_counter]->Draw();
          //if(j>0)histoD[histoD_counter]->Draw("SAME");
          ++histoD_counter;
        }//end if TH1D
        if(histo_type==-1){
          histoF[histoF_counter]=((TH1F *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())));
          if((((TH1F *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())))->GetMaximum())>histo_max){
           
            histo_max=((TH1F *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())))->GetMaximum();
            histo_index=j;
            
          }

          histoF[histoF_counter]->SetStats(0);
          TH1F_config(histoF[histoF_counter],"",x_axis.c_str(),"# Events",j+1);
          title=argv[j+1];
          leg[canvas_counter]->AddEntry(histoF[histoF_counter],(title.substr(0,title.size()-5)).c_str(),"lp");
          
          if(j==0) histoF[histoF_counter]->Draw();
          if(j>0) histoF[histoF_counter]->Draw("SAME");
          ++histoF_counter;
        }//end if TH1F
        if(histo_type==2){
          histo2D[histo2D_counter]=((TH2D *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())));
          histo2D[histo2D_counter]->SetStats(0);
          TH2D_config(histo2D[histo2D_counter],"Titolo","x-axis","y-axis",j+1);
          title=argv[j+1];
          leg[canvas_counter]->AddEntry(histo2D[histo2D_counter],(title.substr(0,title.size()-5)).c_str(),"lp");

          if(j==0) histo2D[histo2D_counter]->Draw();
          if(j>0) histo2D[histo2D_counter]->Draw("SAME");
          ++histo2D_counter;  
        }//end if TH2D
        if(histo_type==-2){
          histo2F[histo2F_counter]=((TH2F *)(file[j]->Get((word.substr(0,word.size()-2)).c_str())));
          histo2F[histo2F_counter]->SetStats(0);
          TH2F_config(histo2F[histo2F_counter],"","x-axis","y-axis",j+1);
          leg[canvas_counter]->AddEntry(histo2F[histo2F_counter],Form("file%d",j),"lp");

          if(j==0) histo2F[histo2F_counter]->Draw();
          if(j>0) histo2F[histo2F_counter]->Draw("SAME");
          ++histo2F_counter;
        }//end if TH2F
      }//end for file_number

      double integral, integral0;
      
      //== Draw INFO ==
      //== Scaling to the histo with more events ==
      if(histo_type==1){
        integral0=histoD[histoD_counter-argc+1+histo_index]->Integral();
        histoD[histoD_counter-argc+1+histo_index]->Scale(1/integral0);
	histoD[histoD_counter-argc+1+histo_index]->Draw();

	for(int j=0; j<(argc-1);++j){
          integral=histoD[histoD_counter-argc+1+j]->Integral();
          if(j!=histo_index){
            histoD[histoD_counter-argc+1+j]->Scale(1/integral);
            //histoD[histoD_counter-argc+1+j]->Scale(integral0/integral);
            histoD[histoD_counter-argc+1+j]->Draw("SAME");
          }
	}

      }

      if(histo_type==-1){
        histoF[histoF_counter-argc+1+histo_index]->Draw();
        integral0=histoF[histoF_counter-argc+1+histo_index]->Integral();
     
        for(int j=0; j<(argc-1);++j){
          integral=histoF[histoF_counter-argc+1+j]->Integral();
          if(j!=histo_index){
            histoF[histoF_counter-argc+1+j]->Scale(integral0/integral);
            histoF[histoF_counter-argc+1+j]->Draw("SAME");
          }
        }

      }

      //== End Draw INFO==
  
      x_axis="";
      leg[canvas_counter]->Draw("SAME");
      c[canvas_counter]->SaveAs(Form("grafici/%s.pdf",(word.substr(0,word.size()-2)).c_str()));
      ++canvas_counter;
      histo_type=0;
         
    }//end if histo name

    if(key_costraint==1){//We are reading the histo type

      if(strcmp(word.c_str(),"TH1D")==0) histo_type=1;
      if(strcmp(word.c_str(),"TH1F")==0) histo_type=-1;
      if(strcmp(word.c_str(),"TH2D")==0) histo_type=2;
      if(strcmp(word.c_str(),"TH2F")==0) histo_type=-2;

      std::cout<<"Histo type: "<<histo_type<<" "<<word.c_str()<<std::endl;

      key_costraint=0;

    }//end if for histo type

    if(strcmp(word.c_str(),"KEY:")==0){
      key_costraint=1;
      ++i;
    }//end if (KEY: costraint)

    histo_max=0;
    
  }//end while inFile.good()

  breakLine();
  std::cout<<"# TH1D = "<<histoD_counter<<" # TH1F = "<<histoF_counter<<" # TH2D = "<<histo2D_counter<<" # TH2F = "<<histo2F_counter<<std::endl;
  std::cout<<"# Canvas = "<<canvas_counter<<" # File = "<<argc-1<<std::endl;
  breakLine();

  //== Printing pretty table!!! ==

  std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
  //printing record
  std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "Object" <<std::setw(1) << "|" << std::setw(15) << std::left << "Created" <<std::setw(1) << "|"  <<std::setw(5) << std::left << "Max" <<std::setw(1) << "|" << std::endl;
  //printing border
  std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
  //printing record
  std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TH1D" <<std::setw(1) << "|" << std::setw(15) << std::left << histoD_counter <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
  //printing border
  std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
  //printing record
  std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TH1F" <<std::setw(1) << "|" << std::setw(15) << std::left << histoF_counter <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
  //printing border
  std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
  //printing record
  std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TH2D" <<std::setw(1) << "|" << std::setw(15) << std::left << histo2D_counter <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
  //printing border
  std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
   //printing record
  std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TH2F" <<std::setw(1) << "|" << std::setw(15) << std::left << histo2F_counter <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
   //printing border
   std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
   //printing record   
   std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TCanvas" <<std::setw(1) << "|" << std::setw(15) << std::left << canvas_counter <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
   //printing border
   std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;
   //printing record   
   std::cout << std::setfill(' ') << std::setw(1) << "|" << std::setw(15) << std::left << "TFile" <<std::setw(1) << "|" << std::setw(15) << std::left << argc-1 <<std::setw(1) << "|"  <<std::setw(5) << std::left << NUMBER <<std::setw(1) << "|" << std::endl;
   //printing border
   std::cout << std::setfill('-') << std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" << std::setw(15) << "-" <<std::setw(1) << "+" <<std::setw(5) << "-" <<std::setw(1) << "+" << std::endl;

  std::cout<<""<<std::endl;
  std::cout << "------ TIME ELAPSED DURING ANALYSIS  ----- " << time.RealTime() << " s" <<std::endl;
  std::cout<<""<<std::endl;


  return 0;

}
