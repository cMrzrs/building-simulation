/* ! CPP PROGRAM == OBJECTS THAT SEND/RECEIVE MESSAGES ! */
//~~~~~~~
//TODO: trades visitors metaksy xwrwn ???
// probz prepei oi exit na epistrefoun visitor*
// wste na mhn antigrafoume olh thn wra memory
// opt == optional

#include <iostream>
#include <cstdio>

using namespace std;

/* ============================= */ 
/* I'm finished here [Harry] */
class visitor
{
  int floor;
  int office_num;
  int priority; 
public:
  visitor(int fl, int off);
  void set_priority(int);
  int get_priority();
  int get_office_num();
  int get_floor();
};

visitor::visitor(int fl, int off){
  floor = fl;
  office_num = off;
}

void visitor::set_priority(int pr){ priority = pr; }

int visitor::get_priority()  { return priority; }
int visitor::get_office_num(){ return office_num; }
int visitor::get_floor()     { return floor; }


/* ============================= */
class waiting_room
{
  int cap;
  int curr;
  visitor* visitors;  // can be done w/ list
public:
  waiting_room(int N);
  ~waiting_room();
  void enter(visitor);
  visitor exit(visitor); // orismata?
  int get_cap();
  int get_curr();
};

/* ============================= */
class ground_level
{
  int cap;
  int curr;
  waiting_room wr; // TODO: orismata gia init
public:
  ground_level(int Ng);
  ~ground_level();
  void enter(visitor);
  visitor exit(visitor); // orismata?
  void wait(visitor); //metaferei ton visitor sto wr (?)/nai
};

/* ============================= */
// Tsekare to
class office
{
  int number;
  int cap;
  int total; // total visitors, used to prioritize ppl (bank-style)
  queue *visitors;
public:
  office(int No, int num);
  ~office();
  void enter(visitor *);
  visitor *exit();
  int get_cap(); // opt?
};

office::office(int No, int num){
  cap    = No;
  number = num;
  visitors = new queue;
  std::cout << "Office #" << number << "has been created" << endl;
}

office::~office(){ 
//  visitors.destroy(); // ? prepei arage na to kserei to office? mallon i delete 8a kalesei ton destructor ths queue, not sure.
  delete visitors;
  std::cout << "End of the work!" << endl;
}

int office::get_cap(){ return cap; }

void office::enter(visitor *vst){
  ++total;
  vst.set_priority(total); // TODO: test an 8a doulepsei xwris pointers ???
  if (visitors.get_size() == cap)
    std::cout << "Please, wait outside for entrance in the office. Your priority is: " << total << endl;
  else {
    visitors.insert(vst);
    std::cout << "Entering office #" << number << endl;
  }
} 

visitor *office::exit(){ 
  return visitors.remove();
}

/* ============================= */
// TODO!!! (Spyro ;]])
//void queue.insert(visitor *);  // insert a visitor in the queue (sto telos)
//int queue.get_size(); // return the valid-data nodes of the q
//visitor *queue.remove(); //epistrefei deikth pros ton visitor pou teleiwse & afaire to 1o melos ths ouras

/* ============================= */
class floor
{
  int cap; //opt ? 
  int curr;//opt ?
  waiting_room wr;
  office off[10]; //TODO: dynamic
public:
  floor(int Nf);
  ~floor();
  void enter(visitor);
  visitor exit(visitor);
  int get_cap();
  int get_curr();
};

/* ============================= */
class elevator  //TODO: all of it
{
  int cap;
  int curr;
  visitor* visitors;
  void enter(visitor);
  visitor exit(visitor);
  void stop_up();   //TODO: orismata
  void stop_down(); //TODO: orismata  
  void empty_all(); //TODO: orismata
public: // [YES] isws ola ektos apo operate prepei n mpoun private, dunno
  elevator(int Nl);
  ~elevator();
  void operate();
  int get_cap();
  int get_curr();
};


/* ============================= */
class building
{
  int cap;  /* capacity */
  int curr; /*  current ppl inside */
  ground_level ground;
  floor fl[4];  // TODO: dynamic
  elevator el;
public:
  building(int N, int Nf, int Ng, int No, int Nl);
  ~building();
  void enter(visitor);
  visitor exit(visitor); // orismata?
};

/* ============================= */


int main(int argc, char const *argv[])
{
  if (argc != 7) {  /* Error check */
    cerr << "\nUsage:\n" << argv[0] 
    << " <max_cap> <floor_cap> <office_cap> <elevator_cap>" 
    << " <number_of_visitors> <elevator_circles>\n" << endl;
    exit(EXIT_FAILURE); 
  }

  int max_cap = atoi(argv[1]);
  int cap_flr = atoi(argv[2]);
  int cap_off = atoi(argv[3]);
  int cap_elv = atoi(argv[4]);
  int num_vst = atoi(argv[5]);
  int l_circl = atoi(argv[6]);
  
  /* Generate visitors required */
  srand(45);
  visitor **ppl = new visitor *[num_vst];
  for (int i = 0; i < num_vst; ++i)
  {
    int fl  = rand() % 4  + 1;  // opt: den exei kalh diaspora
    int off = rand() % 11 + 1; 
    ppl[i]  = new visitor(fl, off);
  }

  // for (int i = 0; i < num_vst; ++i)
  //   cout << "floor: " << ppl[i]->get_floor() << " office:" << ppl[i]->get_office_num() << endl;

  // // test
  // visitor harry(3, 7);
  // cout << harry.get_floor() << endl;
  // cout << harry.get_office_num() << endl;
  // harry.set_priority(667);
  // cout << harry.get_priority() << endl;
  
  /* Cleanup section */
  for (int i = 0; i < num_vst; ++i)
    delete ppl[i];
  delete[] ppl;

  return 0;
}