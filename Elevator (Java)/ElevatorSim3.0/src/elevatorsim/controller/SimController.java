package elevatorsim.controller;

import elevatorsim.data.Scenario;
import elevatorsim.data.State;
import elevatorsim.data.Stats;
import elevatorsim.ui.ConfigWindow;
import elevatorsim.ui.SimWindow;
import elevatorsim.ui.StatsWindow;

public class SimController {
    
    private ConfigController configController;
    private boolean isLocked;
    private boolean isPaused;
    private SimWindow win;
    private StatsWindow statWin;
    private SimTimer timer;
    private State state;
    
    public SimController(){
        win = new SimWindow(this);
        statWin = new StatsWindow(this);
        
        state = null;
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(ConfigWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(ConfigWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(ConfigWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(ConfigWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                win.setVisible(false);
            }
        });
        
        
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                statWin.setVisible(false);
            }
        });
        
        
        isLocked = false;
        isPaused = false;
    }
    
    public boolean isLocked() { return isLocked;}
    public void lock() {isLocked = true;}
    public void unlock() {isLocked = false;}
    
    public void printState(){
        while (isLocked())
            ;
        lock();
        state.print();
        unlock();
    }
    
    public void swapReference(ConfigController cc){
        configController = cc;
        cc.setSimController(this);
    }
    
    public void loadScenario(Scenario sc){
        //create the state
        state = new State(this, sc);
        win.setTimeLabel(state.getTime());
        win.reset();
        win.setVisible(true);
        //init the timer thread
        if (timer != null)
            timer.cancel();
        
        timer = new SimTimer(sc.getSimulationSpeed(), this);
        isPaused = false;
    }
    
    public void restartScenario(){
        state.restart();
        win.setTimeLabel(state.getTime());
        isPaused = false;
    }
    
    public void update(){
        if (isPaused)
            return;
        state.update();
        win.setTimeLabel(state.getTime());
        win.update();
    }
    
    public State getState(){
        return state;
    }
    
    public void evacuate(){
        state.evacuate();
    }
    
    public void stopSim(){
        win.stop();
    }
    
    public void pause(boolean value){
        isPaused = value;
    }
    
    public void reconfig(){
        win.stop();
        win.setVisible(false);
        timer.cancel();
        configController.reconfig();
    }
    
    public void showStats(){
        win.setVisible(false);
        
        statWin.setStats(win.getTimeString(), state.getElapsedTime(), state.getStats());
        statWin.setVisible(true);
    }
    
    public void showSimWindow(){
        statWin.setVisible(false);
        win.setVisible(true);
    }
}
