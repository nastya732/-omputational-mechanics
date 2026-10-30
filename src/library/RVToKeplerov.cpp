#include <cmath>
#include <Eigen/Dense>
#include "RVToKeplerov.hpp"

KeplerovElements RVToKeplerov(const Vector_3D& r, const Vector_3D& v, const double mu) {

    const double r_mod = r.norm();
    const double v_sq  = v.squaredNorm();     // квадрат модуля скорости
    const double rv    = r.dot(v);            // скалярное произведение r·v

    // Вектор удельного момента импульса
    const Vector_3D L = r.cross(v);
    const double L_mod = L.norm();

    // Большая полуось через энергию
    const double a = 1.0 / (2.0 / r_mod - v_sq / mu);

    // Вектор эксцентриситета
    const Vector_3D e = ((v_sq - mu / r_mod) * r - rv * v) / mu;
    const double e_norm = e.norm();

    // Наклонение
    const double i = std::acos(L.z() / L_mod);
    // Вектор линии узлов
    const double z_L_norm = Vector_3D::UnitZ().cross(L).norm();
    const Vector_3D N = z_L_norm != 0 ? Vector_3D (Vector_3D::UnitZ().cross(L) / z_L_norm) : Vector_3D (Vector_3D::UnitX());   // результат = условие ? значение_если_истина : значение_если_ложь;
    
    // Долгота восходящего узла
    const double RAAN = atan2(N.y(), N.x());
    const Vector_3D e1 = N;
    const Vector_3D e2 = (L).cross(N).normalized();

    // введём базис в орбитальной плоскости g
    const Vector_3D g1 = e_norm != 0 ? (e/ e_norm) : e1;
    const Vector_3D g2 = (L/L_mod).cross(g1);
    
    // Аргумент перицентра
    const double w = atan2(g1.dot(e2), g1.dot(e1));

    // Истинная аномалия
    const double nu = atan2(((r).dot(g2)), ((r).dot(g1)));

    return KeplerovElements{
        .a    = a,
        .e    = e_norm,
        .i    = i,
        .RAAN = RAAN,
        .w    = w,
        .nu   = nu
    };
}