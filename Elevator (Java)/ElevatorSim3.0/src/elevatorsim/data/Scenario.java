package elevatorsim.data;

public class Scenario {
    private int visitPerHour;
    private int maxVisitPerHour;
    private int numElevators;
    private int elevatorSpeed;
    private int numFloors;
    private int simSpeed;
    private boolean[] peakHours;
    private int startTime;
    private int endTime;
    
    
    public Scenario(){}
    
    public int getVisitorsPerHour(){return visitPerHour;}
    public int getMaxVisitorsPerHour() {return maxVisitPerHour;}
    public int getNumberOfElevators() {return numElevators;}
    public int getElevatorSpeed() {return elevatorSpeed;}
    public int getNumberOfFloors() {return numFloors;}
    public int getSimulationSpeed() {return simSpeed;}
    public boolean[] getPeakHours() {return peakHours;}
    public int getStartTime() {return startTime;}
    public int getEndTime() {return endTime;}
    
    public void setVisitorsPerHour(int num){ visitPerHour = num;}
    public void setMaxVisitorsPerHour(int num) {maxVisitPerHour = num;}
    public void setNumberOfElevators(int num) {numElevators = num;}
    public void setElevatorSpeed(int num) {elevatorSpeed = num;}
    public void setNumberOfFloors(int num) {numFloors = num;}
    public void setSimulationSpeed(int num) {simSpeed = num;}
    public void setPeakHours(boolean[] peakHours) {this.peakHours = peakHours;}
    public void setStartTime(int num) {startTime = num;}
    public void setEndTime(int num) {endTime = num;}
    
    
    public boolean isPeakHour(int hour) {return peakHours[hour];}
    
}
