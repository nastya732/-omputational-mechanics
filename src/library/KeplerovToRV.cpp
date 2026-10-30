#include <cmath>
#include <Eigen/Dense>
#include "KeplerovToRV.hpp"

Cartesian KeplerovToRV(const KeplerovElements& kep, const double mu) {
    const double cos_nu = std::cos(kep.nu);
    const double sin_nu = std::sin(kep.nu);
    const double p      = kep.a * (1.0 - kep.e * kep.e);   // фокальный параметр
    const double r_mod  = p / (1.0 + kep.e * cos_nu);      // модуль радиус-вектора

    // Положение и скорость в орбитальной (перифокальной) системе
    const Vector_3D r_orb(r_mod * cos_nu, r_mod * sin_nu, 0.0);

    const double v_scale = std::sqrt(mu / p);             // масштаб скорости
    const Vector_3D v_orb(-v_scale * sin_nu, v_scale * (kep.e + cos_nu), 0.0);

    // Поворот орбитальная -> инерциальная: Rz(RAAN) * Rx(i) * Rz(w)
    const Eigen::Matrix3d rot =
        (Eigen::AngleAxisd(kep.RAAN, Vector_3D::UnitZ()) *
         Eigen::AngleAxisd(kep.i,    Vector_3D::UnitX()) *
         Eigen::AngleAxisd(kep.w,    Vector_3D::UnitZ())).toRotationMatrix();
// // из перифокальной в инерциальную
    const Vector_3D r = rot * r_orb;
    const Vector_3D v = rot * v_orb;

    return {.r = r, .v = v};
}