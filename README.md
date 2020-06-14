# ClockSim

Clock Based Cycle Accurate Simulation using all best practices

### Some highlights : 
1. Uses Cmake
2. Uses Unit testing using Catch
3. Uses Modern C++11 techniques, Idioms, patterns as much as possible.

### Goals : 
1. Enable rapid prototyping of Architectures
2. Excellent debug-ability and visualization capabilities just like RTL

### Examples :  

![Sample VCD waveform](images/and_gate.png)  
Figure 1 (above) shows the simulation of an AND gate using this cycle accurate simulation framework.  

![Sample VCD waveform](images/combo_circuit.png)  
Figure 2.  

![Simple Combo Ciruit](images/circuit.png)  
Figure 3.  

Figure 2 shows the simulation of a simple combinatorial circuit (Figure 3) using multiple logic gate components.  

![Sample VCD waveform](images/Flop_Int.png)  
Figure 4 (above) shows the simulation of a Flop / Register which holds an Integer Value.  
Note that the output is delayed by 1 clock, and the register also features a reset option.  
