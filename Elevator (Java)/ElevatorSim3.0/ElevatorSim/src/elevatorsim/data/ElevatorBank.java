package elevatorsim.data;

import java.util.ArrayList;

public class ElevatorBank {
    
    private Scheduler scheduler;
    private ArrayList<Elevator> elevators;
    
    public void update(){
        //update all elevators
        for(Elevator el : elevators){
            el.update();
        }        
    }
    
    public void call(int floorNumber){
        //make a decision as to which elevator will be sent
        scheduler.dispatch(elevators, floorNumber);
    }
    
}
