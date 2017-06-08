#include "roverapi.h"

// All comments are found in the relevant .h Files

RoverAPI::RoverAPI(QObject *parent) : QObject(parent)
{
    // Set default Assumption Values on deployment of Rover
    // - Set rover orientation
    setCurrent_rover_orientation(NORTH);
    // - Set rover camera orientation
    setCurrent_camera_orientation(NORTH);
    // - set rover active
    setRover_in_hibernation(false);
    // -  reset zone scanned
    setZones_scanned(0);
    // - set rover x and Y coordinates to random value for calculations of zones scanned and history
    // - set to center of grid, Grid set to max surface area of Mars (200k * 200k)
    int position = 100000;
    setCurrent_x(position);
    setCurrent_y(position);
}

void RoverAPI::move()
{
    // Move Rover forward based on its orientation
    switch (current_rover_orientation()) {
    case NORTH:
        setCurrent_y(current_y()+1);
        break;
    case SOUTH:
        setCurrent_y(current_y()-1);
        break;
    case EAST:
        setCurrent_x(current_x()+1);
        break;
    case WEST:
        setCurrent_x(current_x()-1);
        break;
    default:
        break;
    }

}

void RoverAPI::rotate(DIRECTION direction)
{
    switch (direction) {
    case CLOCKWISE:
        switch (current_rover_orientation()) {
        case NORTH:
            setCurrent_rover_orientation(EAST);
            break;
        case SOUTH:
            setCurrent_rover_orientation(WEST);
            break;
        case EAST:
            setCurrent_rover_orientation(SOUTH);
            break;
        case WEST:
            setCurrent_rover_orientation(NORTH);
            break;
        }
        break;
    case ANTI_CLOCKWISE:
        switch (current_rover_orientation()) {
        case NORTH:
            setCurrent_rover_orientation(WEST);
            break;
        case SOUTH:
            setCurrent_rover_orientation(EAST);
            break;
        case EAST:
            setCurrent_rover_orientation(NORTH);
            break;
        case WEST:
            setCurrent_rover_orientation(SOUTH);
            break;
        }
        break;
    }
}

bool RoverAPI::scan_for_navigable()
{
    // temp values
    bool return_value = true;

    int low_value  = 1;
    int high_value = 10;
    int benchmark  = 7;

    // generate random number between high and low
    int random_value = qrand()%((high_value+1)-low_value)+low_value;

    // 70% chance of navigable terrain
    if(random_value < benchmark)
    {
        // good terrain -> Navigable
        return_value = true;
    }
    else
    {
        // Bad Terrain -> NOT-Navigable
        return_value = false;
    }

    return return_value;
}

void RoverAPI::deploy_solar_panels()
{
    setSolar_panels_deployed(true);
}

void RoverAPI::retract_solar_panels()
{
    setSolar_panels_deployed(false);
}

void RoverAPI::survey_and_transmit_current_zone()
{
    // temp value
    QPair<int, int> temp_value;
    temp_value.first = current_x();
    temp_value.second = current_y();

    // set location as zoned (history)
    zoned_areas_.append(temp_value);

    // -  reset zone scanned
    setZones_scanned(zones_scanned()+1);
}

int RoverAPI::current_x() const
{
    return current_x_;
}

void RoverAPI::setCurrent_x(int current_x)
{
    current_x_ = current_x;
}

int RoverAPI::current_y() const
{
    return current_y_;
}

void RoverAPI::setCurrent_y(int current_y)
{
    current_y_ = current_y;
}

CARDINAL_POINTS RoverAPI::current_rover_orientation() const
{
    return current_rover_orientation_;
}

void RoverAPI::setCurrent_rover_orientation(const CARDINAL_POINTS &current_rover_orientation)
{
    current_rover_orientation_ = current_rover_orientation;
}

CARDINAL_POINTS RoverAPI::current_camera_orientation() const
{
    return current_camera_orientation_;
}

void RoverAPI::setCurrent_camera_orientation(const CARDINAL_POINTS &current_camera_orientation)
{
    current_camera_orientation_ = current_camera_orientation;
}

bool RoverAPI::rover_in_hibernation() const
{
    return rover_in_hibernation_;
}

void RoverAPI::setRover_in_hibernation(bool rover_in_hibernation)
{
    rover_in_hibernation_ = rover_in_hibernation;
}

int RoverAPI::zones_scanned() const
{
    return zones_scanned_;
}

void RoverAPI::setZones_scanned(int zones_scanned)
{
    zones_scanned_ = zones_scanned;
}

QList<QPair<int, int> > RoverAPI::zoned_areas() const
{
    return zoned_areas_;
}

bool RoverAPI::solar_panels_deployed() const
{
    return solar_panels_deployed_;
}

void RoverAPI::setSolar_panels_deployed(bool solar_panels_deployed)
{
    solar_panels_deployed_ = solar_panels_deployed;
}
