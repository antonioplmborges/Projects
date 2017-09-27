package elevatorsim.data;

import elevatorsim.controller.SimController;
import elevatorsim.data.Constants.Direction;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

public class State {
    
    private SimController controller;
    private Scenario scenario;
    private Stats stats;                // statistics object to collect
    private int totalRunTimeInSeconds;  // how many updates should happen
    private int currentTimeInSeconds;   // how many updates have happened
    private int spawnTime;              // time in seconds(updates) to spawn a person
    private int peakSpawnTime;          // time in seconds(updates) to spawn a person during peak hours
    private int spawnCounter;           // time in seconds in between person spawn
    private Random rand;                // random number generator
    private ArrayList<Person> visitors;         // list of people in the building
    private ElevatorBank bank;          // elevator bank
    private boolean canSpawn;           // is it ok to spawn a person?
    
    public State(SimController controller, Scenario sc){
        rand = new Random();
        this.controller = controller;
        scenario = sc;
        stats = new Stats(sc.getNumberOfFloors(), sc.getNumberOfElevators());
        //create timer thread
        totalRunTimeInSeconds = (sc.getEndTime() - sc.getStartTime())*3600;
        currentTimeInSeconds = 0;
        
        //create elevator bank
        bank = new ElevatorBank(this, sc.getNumberOfElevators(), sc.getElevatorSpeed());
                
        // get time to spawn a person
        spawnCounter = 0;
        spawnTime = 3600/sc.getVisitorsPerHour();
        peakSpawnTime = 3600/sc.getMaxVisitorsPerHour();
        visitors = new ArrayList<>();
        canSpawn = true;
    }
    
    public void restart(){
        stats = new Stats(stats.getNumberOfFloors(), stats.getNumberOfElevators());
        totalRunTimeInSeconds = (scenario.getEndTime() - scenario.getStartTime())*3600;
        currentTimeInSeconds = 0;
        
        //create elevator bank
        bank = new ElevatorBank(this, scenario.getNumberOfElevators(), scenario.getElevatorSpeed());
                
        // get time to spawn a person
        spawnCounter = 0;
        spawnTime = 3600/scenario.getVisitorsPerHour();
        peakSpawnTime = 3600/scenario.getMaxVisitorsPerHour();
        visitors = new ArrayList<>();
        canSpawn = true;
    }
    
    public Stats getStats() { return stats;}
    public int getFloors() {return scenario.getNumberOfFloors();}
    public int getTime(){return scenario.getStartTime()*3600 + currentTimeInSeconds;}
    public int getElapsedTime() { return currentTimeInSeconds;}
   
    public ArrayList<Person> getPeople(){ return visitors; }
    public Elevator[] getElevators() {return bank.getElevators();}
    public int getNumberOfElevators() {return scenario.getNumberOfElevators();}
    
    // add a new person to the first floor or parking garage
    public void spawnPerson(){
        if (!canSpawn)
            return;
        int start = rand.nextInt(2);
        int dest = rand.nextInt(scenario.getNumberOfFloors() - 2) + 2 ;
        int stay = rand.nextInt(3600*2)+60;
        visitors.add(new Person(this, start, dest, stay));
        stats.incrementTotalVisitors();
    }
    
    public void update(){
        //check to see if we need to spawn a person this second
        boolean isPeakHour = scenario.isPeakHour(scenario.getStartTime() + (currentTimeInSeconds/3600));
        
        //increment spawn counter
        ++spawnCounter;
        
        //if it is currently a peak hour then use peakSpawnTime else use spawnTime
        if (isPeakHour) {
            if (spawnCounter >= peakSpawnTime){
                //spawn person
                spawnPerson();
                //reset counter
                spawnCounter = 0;
            }            
        } else {
            if (spawnCounter >= spawnTime) {
                //spawn person
                spawnPerson();
                //reset counter
                spawnCounter = 0;
            }
        }
        
        //update all objects in building
        //update elevator bank
        bank.update();
        
        
        ArrayList<Person> toRemove = new ArrayList<>();
        
        for (Person p : visitors){
            p.update();
            if (p.hasLeft())
                toRemove.add(p);
        }
        
        for (Person p : toRemove){
            if (visitors.contains(p))
                visitors.remove(p);
        }
        
        // decrement total
        if(++currentTimeInSeconds >= totalRunTimeInSeconds){
            //end the simulation
            controller.stopSim();
        }
    }
    
    public void incrementVisitors(int floorNum){
        stats.incrementVisitors(floorNum);
    }
    
    public void evacuate(){
        //turn off spawning
        canSpawn = false;
        
        //tell every person to get the hell out
        for(Person p : visitors){
            if (p == null)
                break;
            p.evacuate();
        }
    }
    
    //adds a request to the queue
    public void elevatorUpdate(Person p, int floor){
        bank.updateElevator(p, floor);
    }
    
    public void updateMaxRequestsStat(int elevatorID, int value){
        stats.setMaxRequests(elevatorID, value);
    }
    
    public ArrayList<Person> getCallers(int floor, Direction dir){
        ArrayList<Person> people = new ArrayList<>();
        for (Person p : visitors){
            if (p.isCalling() && p.getCurrentFloor() == floor && p.getDirection() == dir)
                people.add(p);
        }
        
        return people;
    }
    
    public void callElevator(int floor, Direction dir){
        // tell the elevator bank that we have a call
        bank.call(floor, dir);
    }
    
    //DEPRECATED
    public void removePerson(Person p){
    }
    
    public void elevatorArrived(Elevator el){
        el.unloadPassengers();
        el.loadVisitors(getCallers(el.getCurrentFloor(), el.getDirection()));
        stats.incrementElevatorStopCount(el.getID(), el.getCurrentFloor());
    }
    
    public void addPassengerStat(int elevator){
        stats.incrementPassengerCount(elevator);
    }
    
    
    //DEPRECATED
    public void print(){
        int[] floorCount = new int[getFloors()];
        for (int i = 0; i < getFloors(); ++i)
            floorCount[i] = 0;
        
        for (Person p : visitors){
            if (p.isRiding())
                continue;
            ++floorCount[p.getCurrentFloor()];
        }
        
        for (int i = 0; i < getFloors(); ++i){
            if (i == 0)
                System.out.print("Parking Garage: " + floorCount[i] + "\n");
            else
                System.out.print("Floor " + i + ": " + floorCount[i] + "\n");
        } 
        
        bank.print();
        
        for (Person p : visitors){
            p.print();
        }
    }
}
