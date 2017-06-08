#include "testoverallcontrolalgorithm.h"
#include <QDebug>
#include <QtGlobal>


#include <roverapi.h>
#include <marsterrain.h>
#include <roverpowerstorage.h>
#include <rovertimeactions.h>
#include <overallcontrolalgorithm.h>

TestOverallControlAlgorithm::TestOverallControlAlgorithm(QObject *parent) : QObject(parent)
{

}

int TestOverallControlAlgorithm::test_main()
{
    OverallControlAlgorithm process;
    RoverAPI rover_api;
    MarsTerrain mars_terrain;
    RoverPowerStorage rover_power;
    RoverTimeActions rover_time_actions;

    int temp_six_hundred_var = 600;

    // "survey and transmit" tested in Rover API

    // test power consumption and time spent deduction function
    process.expense_time_power(rover_power,\
                               temp_six_hundred_var,\
                               temp_six_hundred_var,\
                               mars_terrain);

    Q_ASSERT_X(rover_power.current_power_level() == (rover_power.total_capacitive_energy_store()-temp_six_hundred_var), "Algorithm - Power consumption", "Value not updated");
    Q_ASSERT_X(mars_terrain.sol_time_remaining() == (mars_terrain.day_light_seconds()+mars_terrain.night_duration_seconds())-temp_six_hundred_var, "Algorithm - Time Spent Deduction", "Value not updated");

    // test alignment of rover and camera
    rover_api.setCurrent_rover_orientation(NORTH);
    rover_api.setCurrent_camera_orientation(EAST);
    process.rover_camera_alignment(rover_api,\
                                   mars_terrain,
                                   rover_power,\
                                   rover_time_actions);

    Q_ASSERT_X(rover_api.current_rover_orientation() == rover_api.current_camera_orientation(), "Algorithm - Camera and Rover - Not aligned", "Value not updated");


}
