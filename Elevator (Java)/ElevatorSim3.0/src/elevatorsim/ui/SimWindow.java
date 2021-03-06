/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package elevatorsim.ui;

import elevatorsim.controller.SimController;
import elevatorsim.data.Elevator;
import elevatorsim.data.Person;
import elevatorsim.data.State;
import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author jpaquette19
 */
public class SimWindow extends javax.swing.JFrame {

    private DrawTimer timer;
    private SimController controller;
    
    /**
     * Creates new form SimWindow
     */
    public SimWindow(SimController sc) {
        initComponents();
        controller= sc;
        timer = new DrawTimer(this, controller);
        jTBtnPlay.setSelected(true);
        jTBtnPlay.setEnabled(false);
        jTBtnPause.setSelected(false);
        jBtnViewStats.setEnabled(false);
    }

    
    public void reset(){
        jTBtnPlay.setSelected(true);
        jTBtnPlay.setEnabled(false);
        jTBtnPause.setSelected(false);
        jTBtnPause.setEnabled(true);
        jBtnViewStats.setEnabled(false);
        update();
    }
    
    public String getTimeString(){
        return labelTime.getText();
    }
    
    public void setTimeLabel(int time){
        int hours = time/3600;
        String timeString = "" + hours;
        time -= hours * 3600;
        time /= 60;
        if (time < 10){
            timeString += ":0" + time;
        } else {
            timeString += ":" + time;
        }
        
        labelTime.setText(timeString);
    }
    
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        labelTime = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jButtonEvacuate = new javax.swing.JButton();
        jPanelElevators = new javax.swing.JPanel();
        lblElevators = new javax.swing.JLabel();
        jPanelFloors = new javax.swing.JPanel();
        lblFloors = new javax.swing.JLabel();
        lblCalling = new javax.swing.JLabel();
        lblWalking = new javax.swing.JLabel();
        lblVisiting = new javax.swing.JLabel();
        jTBtnPlay = new javax.swing.JToggleButton();
        jTBtnPause = new javax.swing.JToggleButton();
        jTBtnStop = new javax.swing.JButton();
        jBtnViewStats = new javax.swing.JButton();
        jBtnReconfig = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        labelTime.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        labelTime.setText("24:00");
        labelTime.setToolTipText("");

        jLabel2.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        jLabel2.setText("SimTime:");

        jButtonEvacuate.setBackground(new java.awt.Color(204, 0, 0));
        jButtonEvacuate.setText("Evacuate");
        jButtonEvacuate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonEvacuateActionPerformed(evt);
            }
        });

        jPanelElevators.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Elevators", javax.swing.border.TitledBorder.LEFT, javax.swing.border.TitledBorder.DEFAULT_POSITION));

        lblElevators.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        lblElevators.setText("Elevators");
        lblElevators.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        javax.swing.GroupLayout jPanelElevatorsLayout = new javax.swing.GroupLayout(jPanelElevators);
        jPanelElevators.setLayout(jPanelElevatorsLayout);
        jPanelElevatorsLayout.setHorizontalGroup(
            jPanelElevatorsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelElevatorsLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(lblElevators, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanelElevatorsLayout.setVerticalGroup(
            jPanelElevatorsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelElevatorsLayout.createSequentialGroup()
                .addComponent(lblElevators, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        jPanelFloors.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Floors", javax.swing.border.TitledBorder.RIGHT, javax.swing.border.TitledBorder.DEFAULT_POSITION));

        lblFloors.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblFloors.setText("NUMBER:");
        lblFloors.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        lblCalling.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblCalling.setText("CALLING:");
        lblCalling.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        lblWalking.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblWalking.setText("WALKING:");
        lblWalking.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        lblVisiting.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblVisiting.setText("VISITING:");
        lblVisiting.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        javax.swing.GroupLayout jPanelFloorsLayout = new javax.swing.GroupLayout(jPanelFloors);
        jPanelFloors.setLayout(jPanelFloorsLayout);
        jPanelFloorsLayout.setHorizontalGroup(
            jPanelFloorsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelFloorsLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(lblVisiting, javax.swing.GroupLayout.PREFERRED_SIZE, 87, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblWalking, javax.swing.GroupLayout.PREFERRED_SIZE, 87, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblCalling, javax.swing.GroupLayout.PREFERRED_SIZE, 90, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblFloors, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanelFloorsLayout.setVerticalGroup(
            jPanelFloorsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelFloorsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                .addComponent(lblWalking, javax.swing.GroupLayout.DEFAULT_SIZE, 582, Short.MAX_VALUE)
                .addComponent(lblVisiting, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(lblCalling, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(lblFloors, javax.swing.GroupLayout.PREFERRED_SIZE, 563, javax.swing.GroupLayout.PREFERRED_SIZE))
        );

        jTBtnPlay.setIcon(new javax.swing.ImageIcon(getClass().getResource("/elevatorism/Image/run.png"))); // NOI18N
        jTBtnPlay.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTBtnPlayActionPerformed(evt);
            }
        });

        jTBtnPause.setIcon(new javax.swing.ImageIcon(getClass().getResource("/elevatorism/Image/pause.png"))); // NOI18N
        jTBtnPause.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTBtnPauseActionPerformed(evt);
            }
        });

        jTBtnStop.setIcon(new javax.swing.ImageIcon(getClass().getResource("/elevatorism/Image/stop.png"))); // NOI18N
        jTBtnStop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTBtnStopActionPerformed(evt);
            }
        });

        jBtnViewStats.setText("View Stats");
        jBtnViewStats.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBtnViewStatsActionPerformed(evt);
            }
        });

        jBtnReconfig.setText("Reconfigure Scenario");
        jBtnReconfig.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBtnReconfigActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jPanelFloors, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jBtnViewStats, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jTBtnPlay, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTBtnPause, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTBtnStop, javax.swing.GroupLayout.PREFERRED_SIZE, 38, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 78, Short.MAX_VALUE)
                        .addComponent(jBtnReconfig, javax.swing.GroupLayout.PREFERRED_SIZE, 230, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(jPanelElevators, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addContainerGap())
                    .addGroup(layout.createSequentialGroup()
                        .addGap(0, 107, Short.MAX_VALUE)
                        .addComponent(jButtonEvacuate)
                        .addGap(18, 18, 18)
                        .addComponent(jLabel2)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(labelTime, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel2, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jButtonEvacuate)
                            .addComponent(labelTime, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jBtnReconfig, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addGap(38, 38, 38))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(jTBtnPause, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jTBtnStop, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jTBtnPlay, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jBtnViewStats)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jPanelFloors, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanelElevators, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButtonEvacuateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonEvacuateActionPerformed
        // TODO add your handling code here:
        while (controller.isLocked())
            ;
        controller.lock();
        controller.evacuate();
        controller.unlock();
    }//GEN-LAST:event_jButtonEvacuateActionPerformed

    private void jTBtnPlayActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTBtnPlayActionPerformed
        // TODO add your handling code here:
        jTBtnPause.setSelected(false);
        jTBtnPause.setEnabled(true);
        jTBtnPlay.setEnabled(false);
        controller.restartScenario();
        jBtnViewStats.setEnabled(false);
    }//GEN-LAST:event_jTBtnPlayActionPerformed

    private void jTBtnStopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTBtnStopActionPerformed
        jTBtnPlay.setSelected(false);
        jTBtnPlay.setEnabled(true);
        jTBtnPause.setSelected(false);
        jTBtnPause.setEnabled(false);
        controller.pause(true);
        jBtnViewStats.setEnabled(true);
    }//GEN-LAST:event_jTBtnStopActionPerformed

    public void stop(){
        jTBtnPlay.setSelected(false);
        jTBtnPlay.setEnabled(true);
        jTBtnPause.setSelected(false);
        jTBtnPause.setEnabled(false);
        controller.pause(true);
        jBtnViewStats.setEnabled(true);
    }
    
    private void jTBtnPauseActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTBtnPauseActionPerformed
        controller.pause(jTBtnPause.isSelected());
        jBtnViewStats.setEnabled(jTBtnPause.isSelected());
    }//GEN-LAST:event_jTBtnPauseActionPerformed

    private void jBtnReconfigActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBtnReconfigActionPerformed
        // TODO add your handling code here:
        controller.reconfig();
    }//GEN-LAST:event_jBtnReconfigActionPerformed

    private void jBtnViewStatsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBtnViewStatsActionPerformed
        // TODO add your handling code here:
       controller.showStats();
    }//GEN-LAST:event_jBtnViewStatsActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBtnReconfig;
    private javax.swing.JButton jBtnViewStats;
    private javax.swing.JButton jButtonEvacuate;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JPanel jPanelElevators;
    private javax.swing.JPanel jPanelFloors;
    private javax.swing.JToggleButton jTBtnPause;
    private javax.swing.JToggleButton jTBtnPlay;
    private javax.swing.JButton jTBtnStop;
    private javax.swing.JLabel labelTime;
    private javax.swing.JLabel lblCalling;
    private javax.swing.JLabel lblElevators;
    private javax.swing.JLabel lblFloors;
    private javax.swing.JLabel lblVisiting;
    private javax.swing.JLabel lblWalking;
    // End of variables declaration//GEN-END:variables
    
    public void update(){
        if (controller.getState() == null)
           return;
        State state = controller.getState();
        Elevator[] elevators = state.getElevators();
        ArrayList<Person> people = state.getPeople();
        String elevatorText = "<html><br>";
        String floorsText = "<html><br>";
        String callText = "<html>CALLING:<br>";
        String walkText = "<html>WALKING:<br>";
        String visitText = "<html>VISITING:<br>";
        
        
        int[] floorCount = new int[state.getFloors()];
        int[] callingCount = new int[state.getFloors()];
        int[] walkCount = new int[state.getFloors()];
        int[] visitingCount = new int[state.getFloors()];
        for (int i = 0; i < state.getFloors(); ++i){
            floorCount[i] = 0;
            callingCount[i] = 0;
            walkCount[i] = 0;
            visitingCount[i] = 0;
        }
        
        for (Person p : people){
            if (p.isRiding())
                continue;
            ++floorCount[p.getCurrentFloor()];
            if(p.isWalking())
                ++walkCount[p.getCurrentFloor()];
            else if (p.isCalling())
                ++callingCount[p.getCurrentFloor()];
            else if (p.isVisiting())
                ++visitingCount[p.getCurrentFloor()];
        }
        
        for (int i = state.getFloors() - 1; i >= 0; --i){
            for (int j = 0; j < state.getNumberOfElevators(); ++j){
                if (elevators[j].getCurrentFloor() == i)
                    elevatorText += "|| Elevator " + (j+1) + ": " + elevators[j].getPassengers();
            }
            elevatorText += "<br>";
            
            if (i == 0)
                floorsText += "Garage:<br>";
            else
                floorsText += "Floor " + i + ":<br>";
            
            callText += "" + callingCount[i] + "<br>";
            walkText += "" + walkCount[i] + "<br>";
            visitText += "" + visitingCount[i] + "<br>";
        }
        
        elevatorText += "</html>";
        lblElevators.setText(elevatorText);
        
        floorsText += "</html>";
        lblFloors.setText(floorsText);
        
        callText += "</html>";
        lblCalling.setText(callText);
        
        walkText += "</html>";
        lblWalking.setText(walkText);
        
        visitText += "</html>";
        lblVisiting.setText(visitText);
    }

}
