#include <iostream>
#include <thread>
#include <cstdlib>
using namespace std;

#define MIN_FLOOR 0
#define MAX_FLOORS 5

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
    
    int getCurrentFloor() { return mCurrentFloor; }
    
    void setCurrentFloor(int currentFloor) { mCurrentFloor = currentFloor; }
    
    void moveLift(int targetFloor) {
        
        mTargetFloor = targetFloor;
        
       if (mTargetFloor > mCurrentFloor) {
                
            mCurrentMovement = UP;
            
            while(mTargetFloor != mCurrentFloor) {
             
                setCurrentFloor(mCurrentFloor = mCurrentFloor + 1);
                system("sleep 0.5");
                cout << "Current Floor: " << mCurrentFloor << endl;
                
            }
            
            cout << "REQUEST COMPLETE" << endl;
            
        }
        
        else if (mTargetFloor < mCurrentFloor) {
                
            mCurrentMovement = DOWN;
            
            while(mTargetFloor != mCurrentFloor) {
             
                setCurrentFloor(mCurrentFloor = mCurrentFloor - 1);
                system("sleep 0.5");
                cout << "Current Floor: " << mCurrentFloor << endl;
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
    
    Lift lift(MIN_FLOOR, MAX_FLOORS, 0);
    
    cout << "Lift with the properties created: " << endl << "Min Floor: " << lift.getMinFloor() << endl << "Max Floor: " << lift.getMaxFloor() << endl << "Current Floor: " << lift.getCurrentFloor() << endl;
    
   thread t1(testMovement, ref(lift));
   
   
    
   thread t2(AskUser, ref(lift));
   
   t1.join();
   t2.join();
    
    cout << lift.getCurrentFloor() << endl;
    
    
   
    
    
    
    //MAIN END
    cout << "MAIN END";
   
    return 0;
}
