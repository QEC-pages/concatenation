#include "weilei_lib/my_lib.h"
#include <stdio.h>
#include <itpp/itbase.h>
#include <fstream>

//#include <cstdlib>
//#include <iostream>
#include <ctime> //get time in seconds
#include <chrono> // get time in milli seconds

int copy_test(){//fail
  cout<<"copy the text in a file to the end of another file"<<endl;
  ifstream infile("tmp/a.txt");
  ofstream outfile("tmp/b.txt");
  outfile << infile.rdbuf();
  infile.close();
  outfile.close();
  return 0;
}

int mm_test(int k){//test the limit of array length
  GF2mat G;
  //  int   k=750;//750, segmentation fault
  //  for ( int k=500;k<1000;k+=50){
  cout<<"k = "<<k<<endl;
  G.set_size(k,k,true);
  for (int i=0;i<k;i++){
    for ( int j=0;j<k;j++){
      G.set(i,j,1);
    }
  }
  GF2mat_to_MM(G,"data/tmp/bigG.mm");
    //}
  cout<<"done"<<endl;
  return 0;

}
int mm_test2(){
  GF2mat G;
  int   k=3;
  //  for ( int k=500;k<1000;k+=50){
  cout<<"k = "<<k<<endl;
  G.set_size(k,k,true);
  for (int i=0;i<k;i++){
    for ( int j=0;j<k;j++){
      G.set(i,i,1);
    }
  }
  GF2mat_to_MM(G,"data/tmp/smallG.mm");
    //}

  return 0;

}

int mm_test3(){
  GF2mat G;
  G = MM_to_GF2mat("data/tmp/bigG.mm7000");
  cout<<"got matrix G("<<G.rows()<<", "<<G.cols()<<")"<<endl;
  return 0;
}

int G_s_test(){  
  //check the rank of G_sx and G_sz for cubic repetition code
  //result:  G_sx.rows() = 1;
  char *filename_G_sx="data/repetition/cubic_size_5_G_sx.mm";
  char *filename_G_sz="data/repetition/cubic_size_5_G_sz.mm";
  cout<<filename_G_sx<<endl;
  GF2mat G_sx = MM_to_GF2mat(filename_G_sx);
  GF2mat G_sz = MM_to_GF2mat(filename_G_sz);
  cout<<G_sx.rows()<<" + "<<G_sx.cols()<<endl;
  cout<<G_sz.rows()<<" + "<<G_sz.cols()<<endl;
  return 0;
  
}

GF2mat * array_pointer(){
  GF2mat A=gf2dense_eye(2),B(3,3);
  static GF2mat  p[]={A,B};
  cout<<"A = "<<A<<endl;
  return &p[0];
}

int * array_pointer2(){
  const  int m=5;
  int d[m][m];
  d[0][0]=1;
  d[0][1]=2;
  d[1][1]=3;
  return &d[0][0];
}

int array_pointer_test(){
  GF2mat *p;
  p= array_pointer();
  cout<<p<<endl;
  cout<<*(p+1)<<endl;

  //  const  int m=5;
  int *d;//[m][m];
  d=array_pointer2();
  cout<<d<<endl;
  cout<<*(d+1)<<endl;
  return 0;
}

vector<vector<int> > vector_test(){
  vector<vector<int> > vec(10);
  vector<int> sub(10);
  sub[0]=1;
  vec[0]=sub;
  for ( int i=0;i<10;i++){
    cout<<vec[i][i]<<endl;
  }
  return vec;
}

int run_vector_test(){
  vector<vector<int> > vec;
  //  cout<<vec<<endl;
  //cout<<vec[1]<<endl;
  vec = vector_test();
  for ( int i=0;i<10;i++){
    cout<<vec[i][i]<<endl;
  }

  return 0;
}



int pointer_test(){
  int max=3;
  GF2mat *ptr[max];
  //int var[]={1,3,5};
  GF2mat G(2,3);
  cout<<G<<endl;
  ptr[0]=&G;
  GF2mat Q=*ptr[0];
  cout<<Q<<endl;
  GF2mat H[]={G,G};
  cout<<sizeof(H)/sizeof(H[0])<<endl;

  GF2mat F[]={G};
  cout<<sizeof(F)/sizeof(F[0])<<endl;

  
  /*
  for (int i=0;i<max;i++){
    ptr[i] = &var[i];
  }
  for ( int i = 0; i < max; i++) {
    printf("Value of var[%d] = %d\n", i, *ptr[i] );
  }
  */
  
  return 0;
}

int char_test(){
  char a[]="left";//b[]="right";

  if (a=="left"){
    cout<<"done"<<endl;
  }
  return 0;

}


int if_test(){

  int a= (3>2)? 1:0;
  cout<<a<<endl;
  int b= (3>3)? 1:0;
  cout<<b<<endl;
  return 0;
}

int pointer_array_test(){
  int **board = new int*[4];
  for (int i = 0; i < 4; i++) {
    board[i] = new int[10];
  }
  return 0;
}

void copy2(GF2mat &G){
  G.set(1,1,G(1,1)+G(1,2));
  return;
}

void copy1(){
  // check the initialization of GF2mat.
  // result: each time when assgin G to a new matrix. It will copy a new one instead to pointing to the target.
  GF2mat G(2,2),H(2,2);
  H.set(1,2,1);
  copy2(H);
  G=H;
  cout<<G<<endl;
  cout<<H<<endl;
  copy2(H);
  cout<<G<<endl;
  cout<<H<<endl;
  return;
}

int combine_random(int seed){
  //  int seed = 1;
  itpp::RNG_reset(seed);
  int a = randi(1,100000000);
  std::cout<<a<<"\t";
  std::cout<<std::time(nullptr)<<"\t";
  itpp::RNG_reset(std::time(nullptr));
  int b = randi(1,std::time(nullptr));
  std::cout<<b<<"\t";
  itpp::RNG_reset(b+seed);
  std::cout<<randi(1,100000000)<<"\t";
  std::cout<<std::endl;
  return 0;
}
 
int cpp_random() 
{
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  int random_variable = std::rand();
  std::cout << "Random value on [0 " << RAND_MAX << "]: " 
	    << random_variable <<"\t";
 
  // roll a 6-sided die 20 times
  for (int n=0; n != 20; ++n) {
    int x = 7;
    while(x > 6) 
      x = 1 + std::rand()/((RAND_MAX + 1u)/6);  // Note: 1+rand()%6 is biased
    std::cout << x << ' ';
  }
  std::cout<<endl;
  return 0;
}

void random_test(int seed){
  //  RNG_randomize();


  

  auto now = std::chrono::system_clock::now();
  auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

  auto value = now.time_since_epoch();
  long duration = value.count();

  int remain = duration % 1000000000;
  //  cout<<duration<<"\t";
  //cout<<remain<<"\t";
  std::chrono::milliseconds dur(duration);

  std::chrono::time_point<std::chrono::system_clock> dt(dur);
  /*
  if (dt != now_ms)
    std::cout << "Failure.\t";
  else
    std::cout << "Success.\t";
  */
  //  auto start = std::chrono::steady_clock::now();
  //  std::cout<<"now:"<<(double)start<<"\t";


  std::cout<<get_time(1)<<"\t";
  std::cout<<get_time(2)<<"\t";
  std::cout<<get_time(3)<<"\t";
  remain = get_time(2);
  //  cout<<std::time(nullptr)<<"\t";
  //  cout<<remain<<"\t";

  seed=remain;
  itpp::RNG_reset(seed);
  //  ivec state;
  //  itpp::RNG_get_state(state);
  //  std::cout<<state<<endl;
  for ( int i = 0; i < 7; i++){
    cout<<randi(0,10000)<<"\t";
    //cout<<randb(5)<<"\t";
  }
  cout<<endl;
  return;
}

void switch_test(int k){
  switch (k) {
  case 1:
  case 2:
    cout<<"case 1 2\t";
    break;
  case 3:
    cout<<"case 3\t";
    break;
  case 4:
    cout<<"case 4\t";
  case 5:
    cout<<"case 5\t";
    break;
  default:
    cout<<"case otherwise\t";
  }
  cout<<endl;
  return;
}


void syntax_test(){

  GF2mat G = gf2dense_eye(5);
  G
    .transpose();
  cout<<G<<endl;
  return;
}


int main(int args, char ** argvs){
  //  cout<<"begin test"<<endl;
   cout<<"args = "<<argvs[1] <<"\t";
  int k=atof(argvs[1]);
  
  //  mm_test(k);//big G
  //mm_test2();//small G
  //mm_test3();//read
  //  copy_test();

  //G_s_test();
  //    pointer_test();
  //  array_pointer_test();
  //  char_test();
  //  run_vector_test();
  //  if_test();
  //  pointer_array_test();

  //  copy1();
   //   cpp_random();
    random_test(k);
  //combine_random(k);
  //  switch_test(k);

  //  syntax_test();
  //cout<<"finish test"<<endl;
  return 0;
}
