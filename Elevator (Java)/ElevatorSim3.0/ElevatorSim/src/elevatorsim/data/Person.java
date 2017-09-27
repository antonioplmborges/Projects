package elevatorsim.data;

public class Person {
    
    private int currentFloor;
    private int destinationFloor;
    private int lengthOfStay;
    private Elevator currentElevator;
    private States state;
    
    public enum States {
        RIDING, VISITING, CALLING, WAITING, EXITED
    }
    
    public void update(){
        
        //do something based on person state
        switch (state){
            case RIDING:
                //do nothing
                break;
            case VISITING:
                //decrease time of stay
                break;
            case CALLING:
                //call elevator
                break;
            case WAITING:
                //do nothing
                break;
            case EXITED:
                //kill object
                break;
            default:
                break;
        }
        
    }
    
    
}
