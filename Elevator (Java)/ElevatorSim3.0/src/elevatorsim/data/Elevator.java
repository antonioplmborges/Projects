package elevatorsim.data;

import elevatorsim.data.Constants.Direction;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;

public class Elevator {
    
    private static final int STOP_TIME = 5;    // how long in seconds the elevator is stopped
    private static final int CAPACITY = 12;     // number of people that can fit into the elevator
    
    public enum States {MOVING, STOPPED};
    
    private ElevatorBank bank;                  // the elevator bank this elevator belongs too
    private int id;
    private int currentFloor;                   // current floor this elevator is on
                                                // becomes last floor passed if moving
    private int speed;                          // speed in seconds per floor
    private int stopCounter;                    // counter in seconds for how long an elevator has been stopped
    private ArrayList<Person> riders;           // collection of riders
    private LinkedList<Integer> requestQueue;   // collection of request queue
    private int maxRequests;                    // largest size of request queue
    private States state;                       // state of elevator
    private Direction dir;                      // direction the elevator is moving
    private float percentage;                   // percentage representing position of elevator in between floors
    private float percIncrease;                 // speed in seconds is translates to percent per update
    
    public Elevator(ElevatorBank bank, int id, int speed, int floor){
        this.bank = bank;
        this.id = id;
        this.speed = speed;
        stopCounter = STOP_TIME;
        this.currentFloor = floor;
        riders = new ArrayList<>();
        requestQueue = new LinkedList<>();
        maxRequests = 0;
        state = States.STOPPED;
        dir = Direction.UP;
        percentage = 0.0f;
        percIncrease = 100.0f/speed;
    }
    
    public int getID() { return id;}
    public Direction getDirection(){ return dir; }
    public boolean isStopped() { return (state == States.STOPPED); }
    
    public boolean canFitAnother() { return (riders.size() < CAPACITY); }
    
    //returns 0 if moving
    public int getCurrentFloor(){ return currentFloor; }
    public int getPassengers() { return riders.size(); }
    
    public void update(){
        switch(state){
            case MOVING:
                percentage += percIncrease;
                if (percentage >= 100.0f){
                    percentage = 0;
                    if (dir == Direction.UP){
                       ++currentFloor;
                    } else {
                       --currentFloor;
                    }
                    if (currentFloor == requestQueue.peekFirst()){
                        bank.arrived(this);
                        state = States.STOPPED;
                        requestQueue.removeFirst();
                    }       
                }
                break;
            case STOPPED:
                if(--stopCounter <= 0){
                    stopCounter = STOP_TIME;
                    checkMove();
                }
                break;
        }
        
        if (riders.size() > maxRequests){
            maxRequests = riders.size();
            bank.updateMaxRequestsStat(id, maxRequests);
        }
    }
    
    public boolean noRequests(){ return requestQueue.isEmpty(); }
    
    public void addRequest(int floorNumber, boolean ordered){
        if (!ordered){
            requestQueue.addLast(floorNumber);
            return;
        }
        boolean foundIndex = false;
        int idx = 0;
        for (Iterator<Integer> iter = requestQueue.listIterator(); iter.hasNext();){
            Integer f = iter.next();
            if (dir == Direction.DOWN){
                if (floorNumber > f){
                    foundIndex = true;
                    break;
                }
            } else if (dir == Direction.UP){
                if (floorNumber < f){
                    foundIndex = true;
                    break;
                }
            }
            ++idx;
        }
        if (foundIndex)
            requestQueue.add(idx, floorNumber);
        else
            requestQueue.addLast(floorNumber);
    }
    
    public boolean hasRequest(int floor){
        for (Integer request : requestQueue){
            if (request == floor)
                return true;
        }
        return false;
    }
    
    private void checkMove(){
        // if there are requests in queue
        if (requestQueue.size() > 0){
            //startmoving
            state = States.MOVING;
            if (currentFloor > requestQueue.peekFirst()){
                dir = Direction.DOWN;
                System.out.println("Elevator moving from " + currentFloor + " to " + (currentFloor - 1));
            }
            else if (currentFloor < requestQueue.peekFirst()){
                dir = Direction.UP;
                System.out.println("Elevator moving from " + currentFloor + " to " + (currentFloor + 1));
            }
            else
                state = States.STOPPED;
        }
    }
    
    public void addPerson(Person p){
        riders.add(p);
    }
    
    public void unloadPassengers(){
        for (Iterator<Person> iter = riders.iterator(); iter.hasNext(); ){
            Person p = iter.next();
            if (p.getDestinationFloor() == currentFloor){
                p.changeState();
                p.setCurrentFloor(currentFloor);
                iter.remove();
            }
        }
    }
    
    public void loadVisitors(ArrayList<Person> people){
        // load visitors on floor into elevator
        for (Person p : people){
            if (canFitAnother()){
                riders.add(p);
                bank.addPassengerStat(id);
                p.changeState();
                
                if (!hasRequest(p.getDestinationFloor()))
                    requestQueue.add(p.getDestinationFloor());
            }
        }
    }
    
    public boolean hasPerson(Person p){
        if (riders.contains(p))
            return true;
        return false;
    }
    
    // does the elevator have the floor on its request list?
    public boolean isDestination(int floorNumber){
        for (Iterator<Integer> iter = requestQueue.listIterator(); iter.hasNext();){
            Integer request = iter.next();
            if (request == floorNumber)
                return true;
        }
        return false;
    }
    
    // can the elevator pheasibly stop at this floor?
    public boolean canStop(int floorNumber, Direction dir){
        if (this.dir == dir){
            if (dir == Direction.UP && (currentFloor < floorNumber))
                return true;
            else if (dir == Direction.DOWN && (currentFloor > floorNumber))
                return true;
        }
        return false;
    }
    
    
    //DEPRECATED
    public void print(int idx){
        System.out.println("Elevator " + idx);
        System.out.println("    Current Floor: " + currentFloor);
        System.out.println("    Is Moving: " + ((state == States.MOVING)?"yes":"no"));
        System.out.println("    Direction: " + ((dir == Direction.UP)?"up":"down"));
        System.out.println("   Passengers: " + riders.size());
        System.out.print("     Requests: ");
        for (Integer i : requestQueue)
        {
            System.out.print(i + ", ");
        }
        System.out.println();
    }
}
