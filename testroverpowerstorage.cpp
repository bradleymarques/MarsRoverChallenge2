#include "testroverpowerstorage.h"
#include <QtGlobal>
#include <roverpowerstorage.h>

TestRoverPowerStorage::TestRoverPowerStorage(QObject *parent) : QObject(parent)
{

}

int TestRoverPowerStorage::test_main()
{
    RoverPowerStorage rover_power;

    int return_value = 0;
    int temp_var = 600;

    // test functions Initialisations
    Q_ASSERT_X(rover_power.total_capacitive_energy_store() == rover_power.initial_capacitive_energy_store(), "total Capacitive Energy Store Default", "Value not set");

    Q_ASSERT_X(rover_power.current_power_level() == rover_power.initial_capacitive_energy_store(), "Rover not fully charged on deployment", "Value not set");

    // test set functions
    rover_power.setCurrent_power_level(temp_var);
    Q_ASSERT_X(rover_power.current_power_level() == temp_var, "Rover charge value", "Value not set");

    rover_power.setTotal_capacitive_energy_store(temp_var);
    Q_ASSERT_X(rover_power.total_capacitive_energy_store() == temp_var, "Rover Battery Capacity", "Value not set");


    return return_value;

}
