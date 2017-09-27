package elevatorsim.ui;

import elevatorsim.controller.SimController;
import java.util.Timer;
import java.util.TimerTask;

public class DrawTimer extends Timer {
    
    private SimWindow win;
    private SimController controller;
    
    public DrawTimer(SimWindow w, SimController c){
        int clockspeed = 1000/45;
        win = w;
        this.controller = c;
        this.scheduleAtFixedRate(new TimerTask() { public void run(){
             //if (controller.isLocked())
             //   return;
             //controller.lock();
             //win.update();
             //controller.unlock();
        }}, 0, clockspeed);
    }
}
