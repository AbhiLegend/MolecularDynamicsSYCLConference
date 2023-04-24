# MolecularDynamicsSYCLConference


# what is the code doing
 <br>The SYCL code simulates the motion of particles in a box using the Lennard-Jones potential. The simulation is performed using the SYCL programming model, which is designed for parallel computing on heterogeneous systems, such as CPUs and GPUs. </br>

<br>The program starts by defining some parameters, such as the number of particles, the size of the box, and the time step. It then initializes the positions and velocities of the particles randomly.</br>

<br>The simulation is then performed in a loop that runs for a fixed number of steps. In each step, the program calculates the pairwise forces between all pairs of particles using the Lennard-Jones potential. It then updates the velocities of the particles using the calculated forces and a half-time step. Finally, it updates the positions of the particles using the updated velocities and a full-time step. The positions are then printed out at the end of the simulation.</br>

<br>To perform the calculations in parallel, the program uses the SYCL programming model. It creates a queue object that represents the device on which the calculations will be performed. It then creates buffers that hold the particle positions and velocities, and submits two parallel_for kernels that perform the force calculation and position/velocity updates, respectively. The wait() function is called to ensure that the kernels have completed before the next step of the simulation is started. Finally, the updated particle positions are read back from the buffers and printed out. </br>

## Ultimate goal of the program

<br>Overall, this program simulates the motion of a set of particles in a box using the Lennard-Jones potential to calculate the interactions between particles. The simulation is carried out using SYCL, a programming model for heterogeneous computing systems that allows the use of accelerators such as GPUs or FPGAs to speed up the calculations.</br>


## THE NEXT ANALYSIS FOR SYCL CODE WITHIN VISUAL STUDIO 


#The Sample output in console
Here is how the sample output for the program looks like in console.

![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(56).png) <br />

#We will now look at offloading our  program results with Visual Studio Community edition

#We can take a look at entire snapshot of the application
These are the type of analysis we do with the code
#Some good analysis that can be done with the above code are:-
For Algorithms finding hotspots and anamoly detection
Microarchitecture exploration
Parallelism with focus on Threading and HPC performance Charaterization
Accelerators GPU offload and GPU Compute/Media Hotspots


![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(62).png) <br />






#With the VTune analysis we look at memory error analysis
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(65).png) <br />


#We look at CPU Bandwidth utilization for the program as shown below.
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(67).png) <br />



HPC Performance characterization shows how the program has utilized the hardware.

![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(68).png) <br />


With the help of GPU offloading we analyse part of the code that has spent time on the GPU.Also it gives insight
into the GPU Software queue and other things in a complete way.
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(72).png) <br />



With the Intel Advisor we show which part of code can be improved with changes
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(80).png) <br />


#The entire SYCL code run can be analysed as shown below.
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%20(85).png) <br />

# How to get Started with Intel Advisor for the above SYCL code.
Make sure you have installed Intel oneAPI Base toolkit.
Start the oneAPI Command prompt,we will see that the environment is intialized.
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%202023-04-19%20013635.png) <br />


# To start the advisor gui we key in the command
*advisor-gui* in the command prompt window with oneAPI environment enabled.

# Comparing Hotspots for the code
We run the code with two alterations both codes have been provided.one with 1000 particles and other with 1500 particles and compare the results with advisor.
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%202023-04-21%20032405hspot.png) <br />


# The summary shows how the code has behaved
![alt text](https://github.com/AbhiLegend/MolecularDynamicsSYCLConference/blob/main/Screenshot%202023-04-21%20032405hspot.png
) <br />














 
