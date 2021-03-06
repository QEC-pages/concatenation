//Weilei Zeng, Nov 26 2018
/*
This code produce two random quantum codes and construct concatenated codes and reduced code. Then check their distance.
 */
#include "weilei_lib/my_lib.h"
#include <itpp/itbase.h>
#include <ctime> //to get current time
using namespace itpp;
using namespace std;


/*int test(GF2mat &G){//test how to change a matrix in a function
  G.set(1,2,1);
  cout<<dec2bin(7,10)<<endl;
  cout<<dec2bin(7,8)<<endl;
  return 0;
  }*/

int main(int args, char ** argv){
  itpp::Parser parser;
  parser.init(args,argv);
  parser.set_silentmode(true);
  int mode = 1; parser.get(mode,"mode");
  int sub_mode = 1; parser.get(sub_mode,"sub_mode");
  std::string title_str;  parser.get(title_str,"title");
  const char * title = title_str.c_str();
  std::string note=""; parser.get(note,"note");
  int debug = 1; //default debug on
  parser.get(debug,"debug");
  int seed=1; parser.get(seed,"seed");
  //  std::cout<<"\t seed:"<<seed;
  if (debug) std::cout<<"input seed: "<<seed<<" --> ";
  //  seed = seed + std::time(nullptr);
  //  itpp::RNG_reset(std::time(nullptr)); 
  //  seed = seed + itpp::randi(1,1000000000);
  itpp::RNG_reset(seed+get_time(3)); 
  if (debug)   std::cout<<"converted seed:"<<seed;
  //std::cout<<std::endl;

  //  int na_input;  parser.get(na_input,"na_input");
  int n_low;  parser.get(n_low,"n_low");
  int n_high;  parser.get(n_high,"n_high");
  int k_low;  parser.get(k_low,"k_low");
  int k_high;  parser.get(k_high,"k_high");
  

  //  RNG_randomize();  

  Real_Timer timer;  timer.tic();

  GF2mat Gax,Gaz,Cax,Caz;
  GF2mat Gbx,Gbz,Cbx,Cbz;
  int na,ka, Gax_row,Gaz_row;//k is not necessary number of qubits
  int nb,kb, Gbx_row,Gbz_row;

  //int mode=atof(argv[1]);  
  //char * title = argv[2];
  char filename_Gax[256];char filename_Gaz[256];char filename_Gbx[256];char filename_Gbz[256];
  sprintf(filename_Gax,"%sGax.mm",title);  sprintf(filename_Gaz,"%sGaz.mm",title);      sprintf(filename_Gbx,"%sGbx.mm",title);  sprintf(filename_Gbz,"%sGbz.mm",title);

  if (debug)   cout<<mode<<endl<<title<<endl;
  switch( mode ){
    case 1://generate random codes and save
      na=randi(n_low,n_high); ka = randi(k_low,k_high);Gax_row=randi(1,na-ka-1); Gaz_row=na-ka-Gax_row;
      getGoodQuantumCode(na,Gax_row,Gaz_row,Gax,Gaz,Cax,Caz,debug);
      //getRandomQuantumCode(na,Gax_row,Gaz_row,Gax,Gaz,Cax,Caz);

      switch ( sub_mode){
        case 1: //two random codes
      
          //random code B
          nb=randi(n_low,n_high); kb = randi(k_low,k_high);Gbx_row=randi(1,nb-kb-1); Gbz_row=nb-kb-Gbx_row;
          getGoodQuantumCode(nb,Gbx_row,Gbz_row,Gbx,Gbz,Cbx,Cbz,debug);
          break;
        case 2: // identical reverse code A for code B  
          //reverse X and Z of code A for code B
          kb=ka;        
          nb=na;
          Gbx_row=Gaz_row;
          Gbz_row=Gax_row;
          Gbx=Gaz;
          Gbz=Gax;
          Cbx=Caz;
          Cbz=Cax;
          break;
        case 3: //identical code A for code B
          kb=ka;        
          nb=na;
          Gbx_row=Gax_row;
          Gbz_row=Gaz_row;
          Gbx=Gax;
          Gbz=Gaz;
          Cbx=Cax;
          Cbz=Caz;
          break;
      }
      //      cout<<"got two good quantum code"<<endl;
      GF2mat_to_MM(Gax,filename_Gax);      GF2mat_to_MM(Gaz,filename_Gaz);
      GF2mat_to_MM(Gbx,filename_Gbx);      GF2mat_to_MM(Gbz,filename_Gbz);
      break;
    case 2:      //from given input. This is to manually double check some result
      if (debug)  cout<<"check "<<title<<endl;
      Gax=MM_to_GF2mat(filename_Gax); Gaz=MM_to_GF2mat(filename_Gaz);
      Gbx=MM_to_GF2mat(filename_Gbx); Gbz=MM_to_GF2mat(filename_Gbz);
      na=Gax.cols();
      nb=Gbx.cols();

      Cax=getC(Gax,Gaz);
      Caz=getC(Gax,Gaz,1);
      Cbx=getC(Gbx,Gbz);
      Cbz=getC(Gbx,Gbz,1);


      if (debug)  {cout<<"Gax "<<Gax<<endl;  cout<<"Gaz "<<Gaz<<endl;  cout<<"Cax "<<Cax<<endl;  cout<<"Caz "<<Caz<<endl;}
      if (debug) { cout<<"Gbx "<<Gbx<<endl;  cout<<"Gbz "<<Gbz<<endl;  cout<<"Cbx "<<Cbx<<endl;  cout<<"Cbz "<<Cbz<<endl;}
      //      cout<<"debug"<<endl;
      break;
  }



  
  //  cout<<"check code A"<<endl;
  if (! is_quantum_code(Gax,Gaz,Cax,Caz)) throw "invalid code";

  int dax = quantum_dist_v2(Gax,Gaz);
  int daz = quantum_dist_v2(Gax,Gaz,1);

  //  cout<<"check code B"<<endl;
  if ( ! is_quantum_code(Gbx,Gbz,Cbx,Cbz)) throw "invalid code";
  //  cout<<"Gbx "<<Gbx<<endl;  cout<<"Gbz "<<Gbz<<endl;  cout<<"Cbx "<<Cbx<<endl;  cout<<"Cbz "<<Cbz<<endl;
  int dbx = quantum_dist_v2(Gbx,Gbz);
  int dbz = quantum_dist_v2(Gbx,Gbz,1);//1 to flip X and Z


  /*if ( debug) {
    cout<<"[Code A] na = "<<na<<", ";
    cout<<"dax = "<<dax<<", daz = "<<daz<<endl;
    cout<<"[Code B] nb = "<<nb<<", ";
    cout<<"dbx = "<<dbx<<", dbz = "<<dbz<<endl;
  }*/

  //  reduce(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz);
  //concatenate(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz);
  int flag_chain_complex=0; //run if 1
  //0 for reduce/subsystem, distance x
  if (product(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz,debug,0) == 2)   {
    std::cout<<title<<","<<note<<", time:"<<timer.toc()<<std::endl;
    flag_chain_complex=1;
  }
  //1 for reduce/subsystem, distance z
  if (product(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz,debug,1) == 2){
    std::cout<<title<<","<<note<<", time:"<<timer.toc()<<std::endl;
    //    std::cout<<title<<","<<note<<std::endl;
    //    std::cout<<title<<","<<note<<", sub_mode:"<<sub_mode<<std::endl;
    //    std::cout<<title<<std::endl;
    flag_chain_complex=1;
  }
  //2 for concatenate
  //  if ( product(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz,debug,2) == 2)    std::cout<<title<<std::endl;
  //  flag_chain_complex=1;
  if (     flag_chain_complex ){
    // 3 for chain complex with two length-3, z distance
    // 4 for chain complex with two length-3, x distance
    //    cout<<"mode 3 4"<<endl;
    if  (product(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz,debug,3) == 2)  
          std::cout<<title<<","<<note<<", time:"<<timer.toc()<<std::endl;
    //    std::cout<<title<<","<<note<<std::endl;
    //std::cout<<title<<","<<note<<",sub_mode: "<<sub_mode<<std::endl;
    //std::cout<<title<<std::endl;
    if  (product(Gax,Gaz,Gbx,Gbz,dax,daz,dbx,dbz,debug,4) == 2)  
          std::cout<<title<<","<<note<<", time:"<<timer.toc()<<std::endl;
    //    std::cout<<title<<","<<note<<std::endl;
    //std::cout<<title<<","<<note<<",sub_mode: "<<sub_mode<<std::endl;
    //std::cout<<title<<std::endl;
  }

  if ( debug )  timer.toc_print();
  return 0;
}
