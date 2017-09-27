package elevatorsim.controller;

import elevatorsim.data.Scenario;
import elevatorsim.ui.ConfigWindow;

public class MainApp {   
     
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        ConfigController cc = new ConfigController();
        SimController sc = new SimController();
        sc.swapReference(cc);
    }
}
