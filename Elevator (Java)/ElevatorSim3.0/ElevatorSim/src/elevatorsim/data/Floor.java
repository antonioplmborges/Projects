package elevatorsim.data;

import java.util.ArrayList;

public class Floor {
    
    private ElevatorBank bank;
    private ArrayList<Person> visitors;
    private int floorNumber;
    
    public void update(){
        
    }
    
    public void callElevator(){
        bank.call(floorNumber);
    }
    
    public void arrival(Elevator el){
        
    }
}
