#include <cmath>
#include "RVToKeplerov.hpp"

KeplerovElements RVToKeplerov(const Cartesian& state, const double mu) {

    const double r_mod = (state.r).norm();
    const double v_sq  = (state.v).squaredNorm();     // квадрат модуля скорости
    const double rv    = (state.r).dot((state.v));            // скалярное произведение r·v

    // Вектор удельного момента импульса
    const Eigen::Vector3d L = (state.r).cross((state.v));
    const double L_mod = L.norm();

    // Большая полуось через энергию
    const double a = 1.0 / (2.0 / r_mod - v_sq / mu);

    // Вектор эксцентриситета
    const Eigen::Vector3d e = ((v_sq - mu / r_mod) * (state.r) - rv * (state.v)) / mu;
    const double e_norm = e.norm();

    // Наклонение
    const double i = std::acos(L.z() / L_mod);
    // Вектор линии узлов
    const double z_L_norm = Eigen::Vector3d::UnitZ().cross(L).norm();
    const Eigen::Vector3d N = z_L_norm != 0 ? Eigen::Vector3d (Eigen::Vector3d::UnitZ().cross(L) / z_L_norm) : Eigen::Vector3d (Eigen::Vector3d::UnitX());   // результат = условие ? значение_если_истина : значение_если_ложь;
    
    // Долгота восходящего узла
    const double RAAN = atan2(N.y(), N.x());
    const Eigen::Vector3d e1 = N;
    const Eigen::Vector3d e2 = (L).cross(N).normalized();

    // введём базис в орбитальной плоскости g
    const Eigen::Vector3d g1 = e_norm != 0 ? (e/ e_norm) : e1;
    const Eigen::Vector3d g2 = (L/L_mod).cross(g1);
    
    // Аргумент перицентра
    const double w = atan2(g1.dot(e2), g1.dot(e1));

    // Истинная аномалия
    const double nu = atan2((((state.r)).dot(g2)), (((state.r)).dot(g1)));

    return KeplerovElements{
        .a    = a,
        .e    = e_norm,
        .i    = i,
        .RAAN = RAAN,
        .w    = w,
        .nu   = nu
    };
}