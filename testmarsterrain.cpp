#include "testmarsterrain.h"
#include <marsterrain.h>
#include <QtGlobal>

TestMarsTerrain::TestMarsTerrain(QObject *parent) : QObject(parent)
{

}

int TestMarsTerrain::test_main()
{
    MarsTerrain mars;

    int return_value = 0;
    int seconds = 20000;
    int temp_zero_var = 0;

    // test set functions
    mars.setSol_time_remaining(seconds);
    Q_ASSERT_X(mars.sol_time_remaining() == seconds, "Sol Time Remaining", "Value not set");

    mars.setDay_light(false);
    Q_ASSERT_X(mars.day_light() == false, "Sol is daylight", "Value not set");

    mars.setSol_days_spent_on_mars(temp_zero_var);
    Q_ASSERT_X(mars.sol_days_spent_on_mars() == temp_zero_var, "Days spent on Mars", "Value not set");

    mars.setSol_days_spent_in_hibernation(temp_zero_var);
    Q_ASSERT_X(mars.sol_days_spent_in_hibernation() == temp_zero_var, "Days spent in hibernation", "Value not set");

    return return_value;

}
