#include<iostream>
#include<string>
#include<sstream>
 
#define n 5
 
using namespace std;
 
int compltedPhilo = 0,i;
int exitStatus = 0;
int philoCustomers[5]={0,0,0,0,0};
 
struct fork{
    int taken;
}ForkAvil[n];
 
struct philosp{
    int left;
    int right;
    int saturation;
}Philostatus[n];
 
int callRand(){
    int roll;
    roll = (rand() % 10) + 1;
    cout << roll << "--------\n";
    return roll;
} 

void helpCMD ()
{
  cout<<"\nLists of possible commands: \n"
      <<"* n            - next step \n"
      <<"* exit            - closes the program"<<endl;
}

void goForDinner(int philID){ //same like threads concept here cases implemented
if(Philostatus[philID].left==10 && Philostatus[philID].right==10){
        cout<<"Philosopher "<<philID+1<<" completed his dinner\n";
        philoCustomers[philID] = 1;

        if( callRand() > 7){
            philoCustomers[philID] = 0;
            Philostatus[philID].left = 0;
            Philostatus[philID].right = 0;
            Philostatus[philID].saturation = 0;
            cout<<"Philosopher "<<philID+1<<" is hungry again\n";
        }
}
//if already completed dinner
else if(Philostatus[philID].left==1 && Philostatus[philID].right==1){
            //if just taken two forks
            cout<<"Philosopher "<<philID+1<<" took a bite, and is now eating\n";
            philoCustomers[philID] = -1;
            Philostatus[philID].saturation += 1;

            if(Philostatus[philID].saturation == 3){
            cout<<"Philosopher "<<philID+1<<" completed his dinner\n";
                Philostatus[philID].left = Philostatus[philID].right = 10; //remembering that he completed dinner by assigning value 10
                philoCustomers[philID]=1;
                int otherFork = philID-1;
    
                if(otherFork== -1)
                    otherFork=(n-1);
    
                ForkAvil[philID].taken = ForkAvil[otherFork].taken = 0; //releasing forks
                cout<<"Philosopher "<<philID+1<<" released fork "<<philID+1<<" and fork "<<otherFork+1<<"\n";
                compltedPhilo++;
            }
        }
        else if(Philostatus[philID].left==1 && Philostatus[philID].right==0){ //left already taken, trying for right fork
                if(philID==(n-1)){
                    if(ForkAvil[philID].taken==0){ //KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
                        ForkAvil[philID].taken = Philostatus[philID].right = 1;
                        cout<<"Fork "<<philID+1<<" taken by philosopher "<<philID+1<<"\n";
                    }else{
                        cout<<"Philosopher "<<philID+1<<" is waiting for fork "<<philID+1<<"\n";
                    }
                }else{ //except last philosopher case
                    int dupphilID = philID;
                    philID-=1;
 
                    if(philID== -1)
                        philID=(n-1);
 
                    if(ForkAvil[philID].taken == 0){
                        ForkAvil[philID].taken = Philostatus[dupphilID].right = 1;
                        cout<<"Fork "<<philID+1<<" taken by Philosopher "<<dupphilID+1<<"\n";
                    }else{
                        cout<<"Philosopher "<<dupphilID+1<<" is waiting for Fork "<<philID+1<<"\n";
                    }
                }
            }
            else if(Philostatus[philID].left==0){ //nothing taken yet
                    if(philID==(n-1)){
                        if(ForkAvil[philID-1].taken==0){ //KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
                            ForkAvil[philID-1].taken = Philostatus[philID].left = 1;
                            cout<<"Fork "<<philID<<" taken by philosopher "<<philID+1<<"\n";
                        }else{
                            cout<<"Philosopher "<<philID+1<<" is waiting for fork "<<philID<<"\n";
                        }
                    }else{ //except last philosopher case
                        if(ForkAvil[philID].taken == 0){
                            ForkAvil[philID].taken = Philostatus[philID].left = 1;
                            cout<<"Fork "<<philID+1<<" taken by Philosopher "<<philID+1<<"\n";
                        }else{
                            cout<<"Philosopher "<<philID+1<<" is waiting for Fork "<<philID+1<<"\n";
                        }
                    }
        }else{}
}
int alldone(){
    int sum=0;
    for(int k=0; k<5; k++){
        sum = sum+ philoCustomers[k];
    }
    return sum;
}
 
int main(){

string cmdline, cmd;
int j=0;


for(i=0;i<n;i++)
        ForkAvil[i].taken=Philostatus[i].left=Philostatus[i].right=0;
 
while(exitStatus < n){
/* Observe here carefully, while loop will run until all philosophers complete dinner
Actually problem of deadlock occur only thy try to take at same time
This for loop will say that they are trying at same time. And remaining status will print by go for dinner function
*/

//PARSING PROCESS (reads lines up to ARG_MAXX arguments)
        //parameters are identified after every -space- character
    cout<<"[USER]:";
    cin.clear();
    getline(cin, cmdline);
    stringstream cmdpipe(cmdline);
    cmdpipe >> cmd;

    if(cmd == "n"){
        int countin=0;
        do{
            goForDinner(j%5);
            if (countin ==4){
                for(int zz=0; zz<5; zz++){
                    switch(philoCustomers[zz]){
                        case 0:
                            cout << "PhD #" << zz+1 << "is thinking" << endl;
                            break;
                        
                        case 1:
                            cout << "PhD #" << zz+1 << "is full" << endl;
                            break;

                        case -1:
                            cout << "PhD #" << zz+1 << "is eating" << endl;
                            break;
                    }
                }
            }
            j++;
            countin++;
        }while(countin < 5);

    exitStatus = alldone();
    cout << "System Check:" << endl;
    for(int m=0; m<5; m++){
        cout << philoCustomers[m] <<"|"<< Philostatus[m].left << "|"<< Philostatus[m].right<<endl;
        
    }
    if(cmd == "exit"){
        exitStatus = n;
    }
    }
    else if(cmd == "exit"){
        exitStatus = n;
    }
    else if(cmd == "help"){
        helpCMD();
    }

    /*for(i=0;i<n;i++)
                goForDinner(i);
    cout<<"\nTill now num of philosophers completed dinner are "<<compltedPhilo<<"\n\n";
    */
}
 
return 0;
}