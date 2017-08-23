#include <iostream>
#include <thread>
#include <cstdlib>
using namespace std;

#define MIN_FLOOR 0
#define MAX_FLOORS 5

#ifdef _win64
#define sleepCommand "timeout 3"
#endif

#ifdef __linux
#define sleepCommand "sleep 1"
#endif

enum movement {
        STOP,
        UP, 
        DOWN
    };

class Lift {
    
private:
    movement mCurrentMovement;
    int mCurrentFloor;
    int mTargetFloor;
    int mMaxFloor;
    int mMinFloor;
        
public:
    Lift(int minFloor, int maxFloor, int currentFloor) {
     
       mMaxFloor = maxFloor;
       mMinFloor = minFloor;
       mCurrentFloor = currentFloor;
        
    }
    
    void Request(int targetFloor) {
        
        mTargetFloor = targetFloor;
        
        moveLift(mTargetFloor);
        
        
        
    }
    
    void showLiftStatus() {
        
        system("clear");
       
        int i = 0;
        
        while (i <= this->getCurrentFloor()) {
        
            cout << " " ;
            i++;
            
        }
        
        cout << this->getCurrentFloor() << endl;
        
    }
    
    int getCurrentFloor() { return mCurrentFloor; }
    
    void setCurrentFloor(int currentFloor) { mCurrentFloor = currentFloor; }
    
    void moveLift(int targetFloor) {
        
        mTargetFloor = targetFloor;
        
       if (mTargetFloor > mCurrentFloor) {
                
            mCurrentMovement = UP;
            
            while(mTargetFloor != mCurrentFloor) {
             
                setCurrentFloor(mCurrentFloor = mCurrentFloor + 1);
                system(sleepCommand);
                showLiftStatus();
                
            }
            
            cout << "REQUEST COMPLETE" << endl;
            
        }
        
        else if (mTargetFloor < mCurrentFloor) {
                
            mCurrentMovement = DOWN;
            
            while(mTargetFloor != mCurrentFloor) {
             
                setCurrentFloor(mCurrentFloor = mCurrentFloor - 1);
                system(sleepCommand);
                showLiftStatus();
            }
            
            cout << "REQUEST COMPLETE" << endl;
        }
        
        else if (mTargetFloor == mCurrentFloor) {
            
            mCurrentMovement = STOP;
            
            cout << "Already on the floor: " << mTargetFloor << endl;
            
        } 
        
    }
    
    int getMovement() { return mCurrentMovement; }
    
    int getMinFloor() { return mMinFloor; }
    
    int getMaxFloor() { return mMaxFloor; }
    
    
};

void AskUser(Lift& lift) {

    int floor;
    
    cout << "Enter the floor to go on: " ;
    cin >> floor;
    
    lift.Request(floor);
    
}

void testMovement(Lift& lift) {
    
    lift.Request(3);
    lift.Request(1);
    lift.Request(5);
    
}

void lol(Lift lift) {
}
    

int main() {
    
    int userChoice;
    char finalChoice;
    
    Lift lift(MIN_FLOOR, MAX_FLOORS, 0);
    
    cout << "Lift with the properties created: " << endl << "Min Floor: " << lift.getMinFloor() << endl << "Max Floor: " << lift.getMaxFloor() << endl << "Current Floor: " << lift.getCurrentFloor() << endl;
  
    do {
        
        system("clear");
    
        cout << "What do you want to do with the lift?" << endl;
        cout << "1. Move the lift to desired floor" << endl;
        cout << "2. Halt the lift in between" << endl;
        cout << "3. Enter a set of floors to simulate the movement" << endl;
        cout << "Enter your choice: " ;
        
        cin >> userChoice;
        
        switch(userChoice) {
            
            case 1:{
                
                int floor = MIN_FLOOR;
                
                do {
                    
                    if(floor > MAX_FLOORS) cout << "Bummer! Please enter a valid value between " << MIN_FLOOR << " and " << MAX_FLOORS << "!" << endl;
                    
                    cout << "Enter the floor to which you want to move the lift on: ";
                    cin >> floor;
                
                    
                } while (floor > MAX_FLOORS);
                    
                cout << "Starting the lift to move to the floor " << floor << endl;
                lift.moveLift(floor);
                
                if (lift.getCurrentFloor() == floor) cout << "Lift moved to floor " << floor << " successfully " << endl;
                
                break;
            }
                
            
        }
        
        cout << "Do you want to perform any other operation?[Y/N]: " ;
        cin >> finalChoice;
        
    } while (finalChoice == 'y' || finalChoice == 'Y');
        
  // thread t1(testMovement, ref(lift));
   ///thread t2(AskUser, ref(lift));
   
  // t1.join();
   //t2.join();
    
   // cout << lift.getCurrentFloor() << endl;
    
    
   
    
    
    
    //MAIN END
    cout << "MAIN END";
   
    return 0;
}
