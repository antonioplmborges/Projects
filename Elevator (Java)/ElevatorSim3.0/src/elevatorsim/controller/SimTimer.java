package elevatorsim.controller;

import java.util.Timer;
import java.util.TimerTask;

public class SimTimer extends Timer{
    
    private SimController controller;
    private int clockSpeed;
    
    public SimTimer(int simSpeed, SimController c){
        clockSpeed = 1000/simSpeed;
        controller = c;
        this.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run(){
                if (controller.isLocked())
                    return;
                controller.lock();
                controller.update();
                controller.unlock();
            }}, 0, clockSpeed);
        System.out.println("Sim Timer: Thread ID ->"+ Thread.currentThread().getId());
    }
    
    
}
