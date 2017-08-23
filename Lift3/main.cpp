#include <iostream>
#include <thread>
#include <cstdlib>
using namespace std;

#define MIN_FLOOR 0
#define MAX_FLOORS 10

#ifdef _win32
#define sleepCommand "timeout 1"
#endif


#ifdef _win64
#define sleepCommand "timeout 1"
#endif

#ifdef __linux
#define sleepCommand "sleep 1"
#endif

char sleepCommand[] = "timeout 1";

enum movement {
        STOP,
        UP, 
        DOWN
    };
    
class Passenger {
	
	private:
		int mCurrentFloor;
		int mTargetFloor;
		
	public:
		
		Passenger() {
			
			mCurrentFloor = MIN_FLOOR;
			mTargetFloor = MAX_FLOORS;
			
		}
		
		Passenger(int currentFloor, int targetFloor) {
			
			mCurrentFloor = currentFloor;
			mTargetFloor = targetFloor;
			
		}
		
		void setCurrentFloor(int currentFloor) { mCurrentFloor = currentFloor; }
		
		void setTargetFloor(int targetFloor) { mTargetFloor = targetFloor; }
		
		int getCurrentFloor() { return mCurrentFloor; }
	
		int getTargetFloor() { return mTargetFloor; }
	
	
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
        
        system("CLS");
       
        int i = 0;
        int j = this->getCurrentFloor();
        
        cout << "Moving the lift..." << endl << endl;
        
        while (i < this->getCurrentFloor()) {
        
            cout << "-" ;
            i++;
            
        }
        
        //Check the current floor to print "G"/"T" instead of 0 or maxFloor respectively
        if (this->getCurrentFloor() == 0) cout << "G";
        
      	else if (this->getCurrentFloor() == this->getMaxFloor()) cout << "T";
        
		else cout << this->getCurrentFloor();
        
        
        while (j < this->getMaxFloor()) {
        
            cout << "-" ;
            j++;
            
        }
        
        cout << endl;
        
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

void setPassengerDetails(Passenger& passenger) {
	
	int currentFloor, targetFloor;
	
	cout << "Enter the current and target floor of the passenger: "; 
	cin >> currentFloor >> targetFloor;
	
	passenger.setCurrentFloor(currentFloor);
	passenger.setTargetFloor(targetFloor);
	
	cout << endl;
	
}
    

int main() {
    
    int userChoice, num;
    char finalChoice;
    
    Lift lift(MIN_FLOOR, MAX_FLOORS, 0);
    
    do {
        
        system("CLS");
        
        cout << "Lift status " << endl << "Min Floor: " << lift.getMinFloor() << endl << "Max Floor: " << lift.getMaxFloor() << endl << "Current Floor: " << lift.getCurrentFloor() << endl << endl;
    
    	cout << "Enter the number of passengers: " ;
    	cin >> num;
    	
    	Passenger passenger[num];
    	
    	for (int i = 0; i < num; i++) {
   	
    		system("CLS");
    		cout << "PASSENGER " << i + 1 << endl;
    		
			setPassengerDetails(passenger[i]);
			
			cout << endl;    		
    	}
    	
    	cout << "Showing the details of the passengers" << endl; 
    	cout << "C   T" << endl;
    	cout << "-----" << endl;
    
    	for (int i = 0; i < num; i++) {
    		
			cout << passenger[i].getCurrentFloor() << "   " << passenger[i].getTargetFloor();
			
			cout << endl;    		
    	}
    	
    	
    	
    	
        cout << "What do you want to do with the lift?" << endl;
        cout << "1. Move the lift to desired floor (preliminary movement)" << endl;
        cout << "2. OPTION 2 " << endl; //TODO
        cout << "3. OPTION 3" << endl;	//TODO
        cout << "Enter your choice: " ;
        
        cin >> userChoice;
        
        switch(userChoice) {
            
            case 1:{
                
                int floor = MIN_FLOOR;
                
                do {
                    
                    if(floor > MAX_FLOORS) cout << "Bummer! Please enter a valid value between " << MIN_FLOOR << " and " << MAX_FLOORS << "!" << endl;
                    
                    cout << endl << "Enter the floor to which you want to move the lift on: ";
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
