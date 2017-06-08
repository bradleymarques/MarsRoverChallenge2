#include "rovertimeactions.h"

RoverTimeActions::RoverTimeActions()
{
}

double RoverTimeActions::move_forward() const
{
    return move_forward_;
}

double RoverTimeActions::scan_using_camera() const
{
    return scan_using_camera_;
}

double RoverTimeActions::deploy_solar_panels() const
{
    return deploy_solar_panels_;
}

double RoverTimeActions::retract_solar_panels() const
{
    return retract_solar_panels_;
}

double RoverTimeActions::rotate_rover_by_90_degrees() const
{
    return rotate_rover_by_90_degrees_;
}

double RoverTimeActions::rotate_camera_by_90_degrees() const
{
    return rotate_camera_by_90_degrees_;
}

double RoverTimeActions::survey_zone_and_transmit_data() const
{
    return survey_zone_and_transmit_data_;
}
