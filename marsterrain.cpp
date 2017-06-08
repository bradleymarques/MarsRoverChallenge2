#include "marsterrain.h"

MarsTerrain::MarsTerrain(QObject *parent) : QObject(parent)
{
    // Set assumptions
    // - rover deployed at exactly begining of Nightfall
    setSol_time_remaining(day_light_seconds()+night_duration_seconds());
    // confirm assumption, rover lands at 23:59 " Considering it to be the begining of night"
    // one sol day consist from begining of night to end of day"
    setDay_light(false);
    // -  reset counter
    setSol_days_spent_on_mars(0);
    setSol_days_spent_in_hibernation(0);

}

double MarsTerrain::day_light_seconds() const
{
    return day_light_seconds_;
}

double MarsTerrain::night_duration_seconds() const
{
    return night_duration_seconds_;
}

double MarsTerrain::sol_time_remaining() const
{
    return sol_time_remaining_;
}

void MarsTerrain::setSol_time_remaining(double sol_time_remaining)
{
    sol_time_remaining_ = sol_time_remaining;
}

bool MarsTerrain::day_light() const
{
    return day_light_;
}

void MarsTerrain::setDay_light(bool day_light)
{
    day_light_ = day_light;
}

int MarsTerrain::sol_days_spent_on_mars() const
{
    return sol_days_spent_on_mars_;
}

void MarsTerrain::setSol_days_spent_on_mars(int sol_days_spent_on_mars)
{
    sol_days_spent_on_mars_ = sol_days_spent_on_mars;
}

int MarsTerrain::sol_days_spent_in_hibernation() const
{
    return sol_days_spent_in_hibernation_;
}

void MarsTerrain::setSol_days_spent_in_hibernation(int sol_days_spent_in_hibernation)
{
    sol_days_spent_in_hibernation_ = sol_days_spent_in_hibernation;
}
