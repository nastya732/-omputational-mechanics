#pragma once
#include <Eigen/Dense>

struct KeplerovElements {
    double a;    // Большая полуось
    double e;    // Эксцентриситет
    double i;    // Наклонение
    double RAAN; // Долгота восходящего узла
    double w;    // Аргумент перицентра
    double nu;   // Истинная аномалия
};

struct Cartesian{
    Eigen::Vector3d v;
    Eigen::Vector3d r;
};