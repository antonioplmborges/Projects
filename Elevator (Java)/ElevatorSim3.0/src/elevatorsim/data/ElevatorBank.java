package elevatorsim.data;

import elevatorsim.data.Constants.Direction;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

public class ElevatorBank {
    
    private State state;
    private Scheduler scheduler;
    private int numElevators;
    private Elevator[] elevators;
    private State stateObject;
    
    public ElevatorBank(State state, int numberOfElevators, int elevatorSpeed){
        this.state = state;
        scheduler = new Scheduler(state);
        elevators = new Elevator[numberOfElevators];
        for(int i = 0; i < numberOfElevators; ++i){
            Random rand = new Random();
            int randomNum = rand.nextInt(state.getFloors());
            elevators[i] = new Elevator(this, i, elevatorSpeed, randomNum);
        }
        numElevators = numberOfElevators;
    }
    
    public void updateMaxRequestsStat(int elevatorID, int value){
        state.updateMaxRequestsStat(elevatorID, value);
    }
    
    public void addPassengerStat(int elevator){
        state.addPassengerStat(elevator);
    }
    
    public Elevator[] getElevators() { return elevators; }
    
    public void update(){
        //update all elevators
        for(int i = 0; i < numElevators; ++i){
            elevators[i].update();
        }        
    }
    
    public void call(int floor, Direction dir){
        //make a decision as to which elevator will be sent
        scheduler.dispatch(elevators, numElevators, floor, dir);
    }
    
    public void arrived(Elevator el){
        state.elevatorArrived(el);
    }
    
    public void updateElevator(Person p, int floor){
        for(int i = 0; i < numElevators; ++i)
        {
            if (elevators[i].hasPerson(p) && !elevators[i].hasRequest(floor)){
                elevators[i].addRequest(floor, false);
                return;
            }
        }
    }
    
    public void print(){
        for (int i = 0; i < numElevators; ++i){
            elevators[i].print(i);
        }
    }
}
