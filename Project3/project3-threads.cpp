//https://www.modernescpp.com/index.php/dining-philiosophers-problem-i
// dp_5.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include <sstream>

#define n 5

using namespace std;

int myrand(int min, int max) 
{
  return rand()%(max-min)+min;
}

void lock(atomic<int>& m) 
{
  while (m)
    ; // busy waiting
  m=1;
}

void unlock(atomic<int>& m) 
{
  m=0;
}

struct philosp{
    int state = 0;
    int eat = 0;
}Philostatus[n];


void phil(int ph, atomic<int>& ma, atomic<int>& mb) {
  bool run = true;
  while(run) {

    //philosopaher states
    //int state1, state2, state3, state4, state5;
    //1 = thinking, 2 = has first chopstick, 3 = has second chopstick, 4 = eating

    int eat1, eat2, eat3, eat4, eat5;

    int duration=myrand(1000, 2000);
    cout<<ph<<" is thinking for "<<duration<<" ms\n";

    this_thread::sleep_for(chrono::milliseconds(duration));

    lock(ma);
    cout<<ph<<" got first chopstick\n";


    this_thread::sleep_for(std::chrono::milliseconds(1000));

    lock(mb);
    cout<<ph<<" got second chopstick\n";

    duration=myrand(1000, 2000);
    cout<<ph<<" is eating for "<<duration<<" ms\n";
    Philostatus[ph].eat += 1;
    cout << "Philosopher " << ph << " has eaten " << Philostatus[ph].eat << " times..." << endl;

    /*
    if (ph == 1)
    {
      eat1 +=1;
      cout << "Philosopher 1 has eaten " << eat1 << " times..." << endl;
    }
    else if (ph == 2)
    {
      eat2 +=1;
      cout << "Philosopher 2 has eaten " << eat2 << " times..." << endl;
    }
    else if (ph == 3)
    {
      eat3 +=1;
      cout << "Philosopher 3 has eaten " << eat3 << " times..." << endl;
    }
    else if (ph == 4)
    {
      eat4 +=1;
      cout << "Philosopher 4 has eaten " << eat4 << " times..." << endl;
    }
    else if (ph == 5)
    {
      eat5 +=1;
      cout << "Philosopher 5 has eaten " << eat5 << " times..." << endl;
    }
    */
    
    this_thread::sleep_for(std::chrono::milliseconds(duration));

    unlock(mb);
    unlock(ma);

  }
}

void showReport(string cmd)
{
  while(true)
  {
    string cmdline;
    cout << "\n[CMD]: " << endl;
    getline(cin, cmdline);
    stringstream cmdpipe(cmdline);
    cmdpipe >> cmd;

    cout << "Command: " << cmd << endl;

    if (cmd == "r")
    {
      cout << "\n======Plates======: " << endl; 
      for (int i=0; i <=4; i++) cout << "Philosopher " << i+1 << " has eaten " << Philostatus[i].eat << " times..." << endl;
      //cout << "Philosopher 1 has eaten " << Philostatus[0].eat << " times" << endl;
    }
  }
}

int main() {
  cout<<"dp_5\n";
  srand(time(nullptr));

  atomic<int> m1{0}, m2{0}, m3{0}, m4{0}, m5{0};

  string start, cmd;
  cout << "Begin Dinner? (Y/N): ";
  cin >> start;


  if (start == "Y" || start == "y")
  {


    cout << "Dinner Has Begun " << endl;

    thread t1([&] {phil(1, m1, m2);});
    thread t2([&] {phil(2, m2, m3);});
    thread t3([&] {phil(3, m3, m4);});
    thread t4([&] {phil(4, m4, m5);});
    thread t5([&] {phil(5, m1, m5);});

    thread report([&] {showReport(cmd);});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    report.join();

  }
  

}

/*
//report
    cout << "Current State of Philosophers: " << endl;
    if (state1 == 1) cout << "Philosopher 1 is thinking" << endl;
    else if (state1 == 2) cout << "Philosopher 1 has first chopstick" << endl;
    else if (state1 == 3) cout << "Philosopher 1 has second chopstick" << endl;
    else if (state1 == 4) cout << "Philosopher 1 is eating" << endl;

    if (state2 == 1) cout << "Philosopher 2 is thinking" << endl;
    else if (state2 == 2) cout << "Philosopher 2 has first chopstick" << endl;
    else if (state2 == 3) cout << "Philosopher 2 has second chopstick" << endl;
    else if (state2 == 4) cout << "Philosopher 2 is eating" << endl;

    if (state3 == 1) cout << "Philosopher 3 is thinking" << endl;
    else if (state3 == 2) cout << "Philosopher 3 has first chopstick" << endl;
    else if (state3 == 3) cout << "Philosopher 3 has second chopstick" << endl;
    else if (state3 == 4) cout << "Philosopher 3 is eating" << endl;

    if (state4 == 1) cout << "Philosopher 4 is thinking" << endl;
    else if (state4 == 2) cout << "Philosopher 4 has first chopstick" << endl;
    else if (state4 == 3) cout << "Philosopher 4 has second chopstick" << endl;
    else if (state4 == 4) cout << "Philosopher 4 is eating" << endl;

    if (state5 == 1) cout << "Philosopher 5 is thinking" << endl;
    else if (state5 == 2) cout << "Philosopher 5 has first chopstick" << endl;
    else if (state5 == 3) cout << "Philosopher 5 has second chopstick" << endl;
    else if (state5 == 4) cout << "Philosopher 5 is eating" << endl;

    cout << "\nNumber of time a Philosopher has eaten: " << endl;    
    cout << "Philosopher 1 has eaten " << eat1 << " times" << endl;
    cout << "Philosopher 2 has eaten " << eat2 << " times" << endl;
    cout << "Philosopher 3 has eaten " << eat3 << " times" << endl;
    cout << "Philosopher 4 has eaten " << eat4 << " times" << endl;
    cout << "Philosopher 5 has eaten " << eat5 << " times" << endl;
*/

