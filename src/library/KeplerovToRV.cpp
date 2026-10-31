#include <cmath>
#include "KeplerovToRV.hpp"

Cartesian KeplerovToRV(const KeplerovElements& kep, const double mu) {
    const double cos_nu = std::cos(kep.nu);
    const double sin_nu = std::sin(kep.nu);
    const double p      = kep.a * (1.0 - kep.e * kep.e);   // фокальный параметр
    const double r_mod  = p / (1.0 + kep.e * cos_nu);      // модуль радиус-вектора

    // Положение и скорость в орбитальной (перифокальной) системе
    const Eigen::Vector3d r_orb{ r_mod * cos_nu, r_mod * sin_nu, 0.0 };;

    const double v_scale = std::sqrt(mu / p);             // масштаб скорости
    const Eigen::Vector3d  v_orb{ -v_scale * sin_nu, v_scale * (kep.e + cos_nu), 0.0 };

    // Поворот орбитальная -> инерциальная: Rz(RAAN) * Rx(i) * Rz(w)
    const Eigen::Matrix3d rot =
        (Eigen::AngleAxisd(kep.RAAN, Eigen::Vector3d::UnitZ()) *
         Eigen::AngleAxisd(kep.i,    Eigen::Vector3d::UnitX()) *
         Eigen::AngleAxisd(kep.w,    Eigen::Vector3d::UnitZ())).toRotationMatrix();
// // из перифокальной в инерциальную
    const Eigen::Vector3d r = rot * r_orb;
    const Eigen::Vector3d v = rot * v_orb;

    return {.v = v, .r = r};
}
