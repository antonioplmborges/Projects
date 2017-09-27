/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package elevatorsim.data;

/**
 *
 * @author Christine
 */
public class Stats {
    private String time;                    // time of simulation
    private String elapsedTime;             // total time elapsed
    private int numElevators;               // number of elevators in the building
    private int numFloors;                  // number of floors in the building
    private int totalVisitors;              // total number of visitors to the building
    private int[] visitors;                 // total number of visitors to each floor
    private int[][] elFloorsStopped;        // number of times each elevator stopped at each floor
    private int[] maxRequests;              // maximum number of requests for each elevator
    private int[] elPassengers;             // number of passengers carried
    
    public Stats(int numFloors, int numElevators){
        this.numElevators = numElevators;
        this.numFloors = numFloors;
        time = "";
        elapsedTime = "";
        totalVisitors = 0;
        visitors = new int[numFloors];
        elFloorsStopped = new int[numElevators][numFloors];
        maxRequests = new int[numFloors];
        elPassengers = new int[numFloors];
    }
    
    public String getTime(){ return time; }
    public String getElapsedTime() { return elapsedTime; }
    public int getNumberOfFloors() { return numFloors; }
    public int getNumberOfElevators() { return numElevators; }
    public int getTotalVisitors() { return totalVisitors; }
    public int getVisitors(int floorNum) { return visitors[floorNum]; }
    public int getElevatorStopCount(int elevator, int floorNum) { return elFloorsStopped[elevator][floorNum]; }
    public int getMaxRequests(int elevator) { return maxRequests[elevator]; }
    public int getPassengerCount(int elevator) { return elPassengers[elevator]; }
    
    public void setTime(String value){ time = value; }
    public void setElapsedTime(String value) { elapsedTime = value; }
    public void incrementTotalVisitors() { ++totalVisitors; }
    public void incrementVisitors(int floorNum) { ++visitors[floorNum]; }
    public void incrementElevatorStopCount(int elevator, int floorNum) { ++elFloorsStopped[elevator][floorNum]; }
    public void setMaxRequests(int elevator, int value){ maxRequests[elevator] = value; }
    public void incrementPassengerCount(int elevator) { ++elPassengers[elevator]; }
}
