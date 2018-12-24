#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include "Point.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::Matrix4d;
using Eigen::Matrix3d;
using Eigen::Quaterniond;
using Eigen::AngleAxisd;
using Eigen::Vector3d;

class CoordinateSystem {

  Matrix4d affine; //transform from this system to world

public:
  CoordinateSystem() : affine{Eigen::MatrixXd::Identity(4,4)} {}

  CoordinateSystem(const Matrix4d &m) : affine{m} {}

  Matrix4d get() {
    return affine;
  }

  Point3D transformIntoSystem(const Point3D &p, const CoordinateSystem &other) const {
    Point3D ret = p.transpose() * (other.affine * affine.inverse());
    return ret;
  }

  void rotate(Quaterniond q) {
    Matrix4d m;
    m << q.toRotationMatrix(), Vector3d(0,0,0), 0,0,0,1;

    affine *= m;
  }

  void rotate(Matrix3d m) {
    Matrix4d trans;
    trans << m, Vector3d(0,0,0),0,0,0,1;

    affine *= trans;
  }

  void rotateX(double x) {
    rotate(Quaterniond(AngleAxisd(x, Vector3d::UnitX())));
  }

  void rotateY(double y) {
    rotate(Quaterniond(AngleAxisd(y, Vector3d::UnitY())));
  }

  void rotateZ(double z) {
    rotate(Quaterniond(AngleAxisd(z, Vector3d::UnitZ())));
  }

  void translate(Vector3d trans) {
    affine.block<1,3>(3,0) += trans;
  }

};

#endif