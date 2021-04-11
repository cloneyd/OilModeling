#ifndef POLLUTION_SOURCE_TYPES_HPP
#define POLLUTION_SOURCE_TYPES_HPP
// QT
#include <QString>

struct PointSource
{
    static constexpr int number_of_properties{ 8 };
    // known
    QString m_name;
    double m_x;
    double m_y;
    double m_spending;

    // computated
    double m_initial_dilution_ratio;
    double m_main_dilution_ratio;
    double m_common_dilution_ratio;
    double m_vat;
};

struct DiffusionSource : public PointSource
{
    static constexpr int number_of_properties{ 11 };
    // known
    double m_length;
    double m_direction; // degrees
    int m_tubes_number;
};

struct PollutionMatter
{
    static constexpr int number_of_properties{ 9 };
    // known
    QString m_name;
    QString m_group;
    double m_part; // Доля ЛПВ
    double m_mpc; // ПДК
    double m_bc; // Фоновая концентрация
    double m_sewerc; // Сточная концентрация
    // computated
    double m_maxc; // Максимальная концентрация на заданном расстоянии
    double m_averagec; // Средняя концентрация на заданном радиусе
    double m_maxsewerc; // Допустимая сточная концентрация
};

#endif // POLLUTION_SOURCE_TYPES_HPP
