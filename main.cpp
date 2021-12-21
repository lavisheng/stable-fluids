// for apple? No apple machine so I can't actually check if the full program works on apple
// but this is needed, i think. probably.
// i think this about when i wish I learned glfw instead of freeglut all those years ago
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "grid.h"
#include "apply_forces.h"
#include "assemble_laplacian.h"
#include "diffuse.h"
#include "dissipate.h"
#include "project.h"
#include "transport.h"

// some constants we use in rendering
#define DELTA 20.
#define BASEALPHA 0.1f
// constants for simulation
#define VISC 0.01
#define DT 0.1
// variables for simulation
Velocity v0;
Velocity tempV;
Velocity v1;
// force grids. Only have gravity acting upon it
Eigen::VectorXd Fxz;
Eigen::VectorXd Fy;
// density grids
Eigen::VectorXd S0;
Eigen::VectorXd tempS;
Eigen::VectorXd S1;
// source map for where the fluids was initially
Eigen::VectorXd source;
Eigen::SparseMatrixd A;//laplacian


void drawVoxels(){
  float sval, alpha;
  // premise is that we have delta be the total length of the cube
  // we then know that an individual voxel is then DELTA / G(X/Y/Z)
  // so we get the alpha value there, draw it at that voxel, and then move on
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glPushMatrix();
  
  
  glRotatef(20, 1.0, 0, 0);
  glRotatef(20, 0, 1.0, 0);
  glRotatef(1, 0, 0, 1.0);
  glScalef(1.0 / GX, 1.0 / GY, 1.0 /GZ);
  // halfway, so origin is in center
  glTranslatef(-DELTA / 2, -DELTA/2, -DELTA / 2);
  for(int k = 0; k < GZ; k++){
    for(int j = 0; j < GY; j++){
      for(int i = 0; i < GX; i++){
        // we control it via alpha
        // red fluids only
        // this is the density value
        sval = (float)S1(IND(i, j, k));
        // get alpha
        // need to make sure that the empty black cubes up front aren't blocking view of back
        // only show if 
        alpha = std::min(BASEALPHA, BASEALPHA * sval * 100);
        glColor4f(1.0f * sval * 20, 0, 0, alpha); 
        glutSolidCube(1.0);

        glTranslatef(DELTA / GX, 0.0, 0.0);
      }
      glTranslatef(-DELTA, DELTA / GY, 0);
    }
    glTranslatef(0, -DELTA, DELTA / GZ);
  }
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void simulation(){
  // velocity sim
  // forces
  apply_forces(v0.u1, Fxz, DT);
  apply_forces(v0.u2, Fy, DT);
  apply_forces(v0.u3, Fxz, DT);
  // transport step
  transport(v1.u1, v0.u1, v0, DT);
  transport(v1.u2, v0.u2, v0, DT);
  transport(v1.u3, v0.u3, v0, DT);
  // Difussion step
  diffuse(v0.u1, v1.u1, VISC, DT, A);
  diffuse(v0.u2, v1.u2, VISC, DT, A);
  diffuse(v0.u3, v1.u3, VISC, DT, A);
  // projection
  project(v1, v0, A);

  // scalar sim
  apply_forces(S0, source, DT);
  transport(S1, S0, v0, DT);
  diffuse(S0, S1, 0.001, DT, A);
  dissipate(S1, S0, 0.01, DT);
  // swap buffers
  tempV = v0;
  v0 = v1;
  v1 = tempV;
  tempS = S0;
  S0 = S1;
  S1 = tempS;
  glutPostRedisplay();
}
int main(int argc, char * argv[]){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(400, 400);
  glutCreateWindow("stable-fluids");

  glutDisplayFunc(drawVoxels);
  glutIdleFunc(simulation);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  // setup the two velocities
  v0.u1 = Eigen::VectorXd::Zero(GRIDSIZE);
  v0.u2 = Eigen::VectorXd::Zero(GRIDSIZE);
  v0.u3 = Eigen::VectorXd::Zero(GRIDSIZE);

  v1.u1 = Eigen::VectorXd::Zero(GRIDSIZE);
  v1.u2 = Eigen::VectorXd::Zero(GRIDSIZE);
  v1.u3 = Eigen::VectorXd::Zero(GRIDSIZE);

  // only external force is gravity
  Fxz = Eigen::VectorXd::Zero(GRIDSIZE);
  // recall, the y is pointing downwards here so positive 9.81 should go down
  Fy = Eigen::VectorXd::Ones(GRIDSIZE) * -9.81;

  S0 = Eigen::VectorXd::Zero(GRIDSIZE);
  S1 = Eigen::VectorXd::Zero(GRIDSIZE);

  source = Eigen::VectorXd::Zero(GRIDSIZE);
  assemble_laplacian(A);
  source[IND(GX-3,2,2)] = 1000;
  source[IND(10, 10, GZ-2)] = 1000;
  glutMainLoop();
}
