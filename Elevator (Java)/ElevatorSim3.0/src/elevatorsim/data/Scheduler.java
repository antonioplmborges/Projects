package elevatorsim.data;

import elevatorsim.data.Constants.Direction;
import java.util.ArrayList;
import java.util.Iterator;


public class Scheduler {
    
    private State stateObject;          // reference to State object
    public Scheduler(State s){
        stateObject = s;
    }
    
    public void dispatch(Elevator[] elevators, int numberOfElevators, int floor, Direction dir){
        //decide which elevator is going
        //add the request to the elevator queue
        for (int i = 0; i < numberOfElevators; ++i){
            if (elevators[i].getCurrentFloor() == floor && elevators[i].isStopped() && elevators[i].canFitAnother()){
                elevators[i].loadVisitors(stateObject.getCallers(floor, dir));
                return;
            }
        }
        
        for (int i = 0; i < numberOfElevators; ++i){
            if (elevators[i].isDestination(floor)){
                return;
            }
        }
        for (int i = 0; i < numberOfElevators; ++i){    
            if (elevators[i].canStop(floor, dir)){
                elevators[i].addRequest(floor, true);
                return;
            }
        }
        for (int i = 0; i < numberOfElevators; ++i){
            if (elevators[i].noRequests()){
                elevators[i].addRequest(floor, true);
                return;
            } 
        }
    }
}
