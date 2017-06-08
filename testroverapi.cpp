#include "testroverapi.h"
#include <QtGlobal>
#include <roverapi.h>

TestRoverAPI::TestRoverAPI(QObject *parent) : QObject(parent)
{

}

int TestRoverAPI::test_main()
{
    RoverAPI rover;

    int return_value = 0;
    int temp_zero_var = 0;

    // test functions
    rover.setCurrent_x(temp_zero_var);
    rover.setCurrent_y(temp_zero_var);
    Q_ASSERT_X(rover.current_x() == temp_zero_var, "Current X", "Value not set");
    Q_ASSERT_X(rover.current_y() == temp_zero_var, "Current Y", "Value not set");

    // test Camera rotate
    rover.setCurrent_camera_orientation(NORTH);
    Q_ASSERT_X(rover.current_camera_orientation() == NORTH, "Camera Orientation", "Value not set");

    // test rover rotate
    rover.rotate(CLOCKWISE);
    Q_ASSERT_X(rover.current_rover_orientation() == EAST, "ROVER Orientation", "Value not set");

    // test move
    rover.move();
    Q_ASSERT_X(rover.current_x() == temp_zero_var+1, "Rover Move", "Value not set");

    // test solar deployment
    rover.deploy_solar_panels();
    Q_ASSERT_X(rover.solar_panels_deployed() == true, "Solar Panels Deploy", "Value not set");


    // test solar deployment
    rover.retract_solar_panels();
    Q_ASSERT_X(rover.solar_panels_deployed() == false, "Solar Panels Retracted", "Value not set");


    // test survey and transmit and zone flagged
    rover.survey_and_transmit_current_zone();
    Q_ASSERT_X(rover.zones_scanned() == 1, "Number of areas scanned", "Value not set");


    return return_value;

}
