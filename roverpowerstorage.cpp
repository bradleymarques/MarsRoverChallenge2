#include "roverpowerstorage.h"

RoverPowerStorage::RoverPowerStorage(QObject *parent) : QObject(parent)
{
    // set default Assumption Power Storage
    // - Power at full capaicity
    setCurrent_power_level(initial_capacitive_energy_store());
    // - set Initial Value Confirmed
    setTotal_capacitive_energy_store(initial_capacitive_energy_store());
}

double RoverPowerStorage::solar_power_gain_day() const
{
    return solar_power_gain_day_;
}

double RoverPowerStorage::solar_power_gain_night() const
{
    return solar_power_gain_night__;
}

double RoverPowerStorage::rotate_rover_by_90_degrees() const
{
    return rotate_rover_by_90_degrees_;
}

double RoverPowerStorage::rotate_camera_by_90_degrees() const
{
    return rotate_camera_by_90_degrees_;
}

double RoverPowerStorage::scan_using_camera() const
{
    return scan_using_camera_;
}

double RoverPowerStorage::survey_zone_and_transmit_data() const
{
    return survey_zone_and_transmit_data_;
}

double RoverPowerStorage::move_forward() const
{
    return move_forward_;
}

double RoverPowerStorage::deploy_solar_panels() const
{
    return deploy_solar_panels_;
}

double RoverPowerStorage::retract_solar_panels() const
{
    return retract_solar_panels_;
}

double RoverPowerStorage::capacitive_store_loss_while_charging() const
{
    return capacitive_store_loss_while_charging_;
}

double RoverPowerStorage::current_power_level() const
{
    return current_power_level_;
}

void RoverPowerStorage::setCurrent_power_level(double current_power_level)
{
    current_power_level_ = current_power_level;
}

void RoverPowerStorage::setTotal_capacitive_energy_store(double total_capacitive_energy_store)
{
    total_capacitive_energy_store_ = total_capacitive_energy_store;
}

double RoverPowerStorage::initial_capacitive_energy_store() const
{
    return initial_capacitive_energy_store_;
}


double RoverPowerStorage::total_capacitive_energy_store() const
{
    return total_capacitive_energy_store_;
}

