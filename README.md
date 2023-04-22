# MolecularDynamicsSYCLConference


# what is the code doing
 <br>The SYCL code simulates the motion of particles in a box using the Lennard-Jones potential. The simulation is performed using the SYCL programming model, which is designed for parallel computing on heterogeneous systems, such as CPUs and GPUs. </br>

<br>The program starts by defining some parameters, such as the number of particles, the size of the box, and the time step. It then initializes the positions and velocities of the particles randomly.</br>

<br>The simulation is then performed in a loop that runs for a fixed number of steps. In each step, the program calculates the pairwise forces between all pairs of particles using the Lennard-Jones potential. It then updates the velocities of the particles using the calculated forces and a half-time step. Finally, it updates the positions of the particles using the updated velocities and a full-time step. The positions are then printed out at the end of the simulation.</br>

<br>To perform the calculations in parallel, the program uses the SYCL programming model. It creates a queue object that represents the device on which the calculations will be performed. It then creates buffers that hold the particle positions and velocities, and submits two parallel_for kernels that perform the force calculation and position/velocity updates, respectively. The wait() function is called to ensure that the kernels have completed before the next step of the simulation is started. Finally, the updated particle positions are read back from the buffers and printed out. </br>







 
