#include <iostream>
#include <cmath>
#include <tuple>
#include <Eigen/Geometry>
// siline
// нужно реализовать беблиотеку 2 - h и 2 - cpp
//  в Cmake.txt дописать добавив две свои библиотке ( из rv в rv)
using Vector_3D = Eigen::Vector3d;

struct KeplerovElements {
    double a;    // Большая полуось
    double e;    // Эксцентриситет
    double i;    // Наклонение
    double RAAN; // Долгота восходящего узла
    double w;    // Аргумент перицентра
    double nu;   // Истинная аномалия
};

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

int main() {
    std::cout << "It works" << '\n';
}

