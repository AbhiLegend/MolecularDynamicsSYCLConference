#include <CL/sycl.hpp>
#include <iostream>
#include <cmath>
using namespace cl::sycl;

const int N = 1500; // number of particles
const float L = 10.0f; // size of simulation box
const float dt = 0.01f; // time step
const float eps = 1.0f; // Lennard-Jones epsilon parameter
const float sigma = 1.0f; // Lennard-Jones sigma parameter

// compute pairwise Lennard-Jones force between two particles
inline float lj_force(float r2) {
    float inv_r2 = 1.0f / r2;
    float inv_r6 = inv_r2 * inv_r2 * inv_r2;
    float f = 24.0f * eps * inv_r6 * (2.0f * inv_r6 - 1.0f) * inv_r2;
    return f;
}

int main() {
    std::vector<float> x(N), y(N), z(N); // particle positions
    std::vector<float> vx(N), vy(N), vz(N); // particle velocities
    // initialize particle positions and velocities
    for (int i = 0; i < N; i++) {
        x[i] = L * std::rand() / RAND_MAX;
        y[i] = L * std::rand() / RAND_MAX;
        z[i] = L * std::rand() / RAND_MAX;
        vx[i] = 0.0f;
        vy[i] = 0.0f;
        vz[i] = 0.0f;
    }

    {
        queue myQueue;
        buffer<float, 1> bufX(x.data(), range<1>(N));
        buffer<float, 1> bufY(y.data(), range<1>(N));
        buffer<float, 1> bufZ(z.data(), range<1>(N));
        buffer<float, 1> bufVx(vx.data(), range<1>(N));
        buffer<float, 1> bufVy(vy.data(), range<1>(N));
        buffer<float, 1> bufVz(vz.data(), range<1>(N));

        for (int step = 0; step < 1500; step++) {
            // calculate pairwise forces between particles
            myQueue.submit([&](handler& cgh) {
                auto accX = bufX.get_access<access::mode::read_write>(cgh);
                auto accY = bufY.get_access<access::mode::read_write>(cgh);
                auto accZ = bufZ.get_access<access::mode::read_write>(cgh);
                auto accVx = bufVx.get_access<access::mode::read_write>(cgh);
                auto accVy = bufVy.get_access<access::mode::read_write>(cgh);
                auto accVz = bufVz.get_access<access::mode::read_write>(cgh);
                cgh.parallel_for<class force_kernel>(range<1>(N), [=](id<1> i) {
                    float xi = accX[i];
                    float yi = accY[i];
                    float zi = accZ[i];
                    float fxi = 0.0f;
                    float fyi = 0.0f;
                    float fzi = 0.0f;
                    for (int j = 0; j < N; j++) {
                        if (i != j) {
                            float dx = xi - accX[j];
                            float dy = yi - accY[j];
                            float dz = zi - accZ[j];
                            // apply periodic boundary conditions
                            dx -= L * std::round(dx / L);
                            dy -= L * std::round(dy / L);
                            dz -= L * std::round(dz / L);
                            float r2 = dx * dx + dy * dy + dz * dz;
                            if (r2 < 4.0f * sigma * sigma) { // apply cutoff
                                float f = lj_force(r2);
                                fxi += f * dx;
                                fyi += f * dy;
                                fzi += f * dz;
                            }
                        }
                    }
                    accVx[i] += 0.5f * dt * fxi;
                    accVy[i] += 0.5f * dt * fyi;
                    accVz[i] += 0.5f * dt * fzi;
                    });
                });




            // update particle positions and velocities
            myQueue.submit([&](handler& cgh) {
                auto accX = bufX.get_access<access::mode::read_write>(cgh);
                auto accY = bufY.get_access<access::mode::read_write>(cgh);
                auto accZ = bufZ.get_access<access::mode::read_write>(cgh);
                auto accVx = bufVx.get_access<access::mode::read_write>(cgh);
                auto accVy = bufVy.get_access<access::mode::read_write>(cgh);
                auto accVz = bufVz.get_access<access::mode::read_write>(cgh);
                cgh.parallel_for<class update_kernel>(range<1>(N), [=](id<1> i) {
                    accX[i] += dt * accVx[i];
                    accY[i] += dt * accVy[i];
                    accZ[i] += dt * accVz[i];
                    // apply periodic boundary conditions
                    accX[i] -= L * std::round(accX[i] / L);
                    accY[i] -= L * std::round(accY[i] / L);
                    accZ[i] -= L * std::round(accZ[i] / L);
                    });
                });

            myQueue.wait();
        }

        // print final particle positions
        auto accX = bufX.get_access<access::mode::read>();
        auto accY = bufY.get_access<access::mode::read>();
        auto accZ = bufZ.get_access<access::mode::read>();
        for (int i = 0; i < N; i++) {
            std::cout << "Particle " << i << " position: (" << accX[i] << ", " << accY[i] << ", " << accZ[i] << ")" << std::endl;
        }
    }

    return 0;
}






