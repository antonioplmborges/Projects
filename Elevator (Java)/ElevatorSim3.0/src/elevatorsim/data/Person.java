package elevatorsim.data;

import elevatorsim.data.Constants.Direction;

public class Person {
    
    private static final int WALK_TIME = 12;    // the time it takes for a person to walk to the elevator
    private State stateObject;                  // the state this object belongs to
    private int startingFloor;                  // the floor the person started at (will end here as well)
    private int currentFloor;                   // the floor the person is currently on
    private int destinationFloor;               // the floor the person is trying to visit
    private int lengthOfStay;                   // how long a person will stay on the destination floor before leaving
    private int state;                          // the state the person is in
    private int walkTimer;                      // how long a person takes to get to the elevator or out the door
    private States schedule[];                  // array of states expected
    
     public enum States {
        RIDING, VISITING, CALLING, 
        WALKING, EXITED
    }
     
    public Person(State stateObject, int startFloor, int destFloor, int lengthOfStay){
        this.stateObject = stateObject;
        startingFloor = startFloor;
        currentFloor = startFloor;
        destinationFloor = destFloor;
        walkTimer = WALK_TIME;
        this.lengthOfStay = lengthOfStay;
        state = 0;
        schedule = new States[10];
        schedule[0] = States.WALKING;
        schedule[1] = States.CALLING;
        schedule[2] = States.RIDING;
        schedule[3] = States.WALKING;
        schedule[4] = States.VISITING;
        schedule[5] = States.WALKING;
        schedule[6] = States.CALLING;
        schedule[7] = States.RIDING;
        schedule[8] = States.WALKING;
        schedule[9] = States.EXITED;
        
    }
    
    public int getCurrentFloor() { return currentFloor; }
    public void setCurrentFloor(int floor) { currentFloor = floor; }
    
    public int getDestinationFloor() { return destinationFloor; }
    public boolean isCalling() { return (schedule[state] == States.CALLING); }
    public boolean isRiding() { return (schedule[state] == States.RIDING); }
    public boolean isWalking() { return (schedule[state] == States.WALKING); }
    public boolean isVisiting() { return (schedule[state] == States.VISITING); }
    
    public void update(){
        
        //do something based on person state
        switch (schedule[state]){
            case WALKING:
                //decrease walk timer
                if (--walkTimer <= 0)
                {
                    walkTimer = WALK_TIME;
                    changeState();
                }
                break;
            case RIDING:
                //do nothing
                break;
            case VISITING:
                if (--lengthOfStay <= 0)
                    changeState();
                break;
            case CALLING:
                //call elevator
                stateObject.callElevator(currentFloor, getDirection());
                break;
            case EXITED:
                //do nothing -- state will delete object
                break;
            default:
                break;
        }
        
    }
    
    public void changeState(){
        if (state == 9)
            return;
        ++state;
        if (isVisiting())
            stateObject.incrementVisitors(currentFloor);
        
        switch(state){
            case 3:
                destinationFloor = startingFloor;
                break;
        }
    }
    
    public boolean hasLeft(){ return (schedule[state] == States.EXITED); }
    
    public Direction getDirection(){
        if (currentFloor > destinationFloor)
            return Direction.DOWN;
        else
            return Direction.UP;
    }
    
    //DEPRECATED
    public void print(){
        System.out.println("\tPerson:\n"
                         + "\t Current Floor = " + currentFloor
                         + "\t         State = " + schedule[state].toString() + "\n"
                         + "\t   Destination = " + destinationFloor);
    }
    
    
    //changes the person's schedule to leave based on the state their in
    public void evacuate(){
        destinationFloor = startingFloor;
        switch(schedule[state]){
            case WALKING:
                if (currentFloor == startingFloor)
                    state = 8;
                else {
                    state = 5;
                }
                break;
            case RIDING:
                //do nothing
                state = 7;
                stateObject.elevatorUpdate(this, destinationFloor);
                break;
            case VISITING:
                changeState();
                break;
            case CALLING:
                if (startingFloor == currentFloor)
                    state = 8;
                break;
            case EXITED:
                //do nothing -- state will delete object
                break;
            default:
                break; 
        }
    }
}
