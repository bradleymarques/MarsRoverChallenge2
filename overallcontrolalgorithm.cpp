#include "overallcontrolalgorithm.h"
#include <QDebug>

OverallControlAlgorithm::OverallControlAlgorithm(QObject *parent) : QObject(parent)
{
    // reset worse case scenario's
    setWorst_case_scenario_time(0);
    setWorst_case_scenario_power(0);
}

int OverallControlAlgorithm::start_algorithm(int &zones_scanned,\
                                              int &sols_lasted)
{
    // Instantiate Classes
    RoverAPI rover_api;
    MarsTerrain mars_terrain;
    RoverPowerStorage rover_power;
    RoverTimeActions rover_time_actions;

    // -----------------------------
    // Determing worst case scenario
    // -----------------------------

    // iniatilise
    int error_code = 0;

    // Determine worst case scenaria per zone time
    setWorst_case_scenario_time(rover_time_actions.scan_using_camera() +\
                                (rover_time_actions.rotate_camera_by_90_degrees() * 3) +\
                                rover_time_actions.rotate_rover_by_90_degrees() +\
                                rover_time_actions.move_forward() +\
                                rover_time_actions.survey_zone_and_transmit_data());

    // Determine worst case scenaria per zone power
    setWorst_case_scenario_power(rover_power.scan_using_camera() +\
                                 (rover_power.rotate_camera_by_90_degrees() * 3) +\
                                 rover_power.rotate_rover_by_90_degrees() +\
                                 rover_power.move_forward() +\
                                 rover_power.survey_zone_and_transmit_data());

    // simulate contoller - loop until power left in capicitive to atleast survey and transmit data
    while(rover_power.total_capacitive_energy_store() > rover_power.survey_zone_and_transmit_data() \
          || error_code == -1)
    {
        // call simulate Sol Day
        error_code = simulate_sol_day(worst_case_scenario_time(),\
                                      worst_case_scenario_power(),\
                                      rover_power, \
                                      rover_time_actions, \
                                      rover_api, \
                                      mars_terrain);
    }

    // set values
    sols_lasted = mars_terrain.sol_days_spent_on_mars();
    zones_scanned = rover_api.zones_scanned();

    // return
    return error_code;
}

int OverallControlAlgorithm::simulate_sol_day(double worst_case_scenario_time_variable,\
                                              double worst_case_scenario_power_variable,\
                                              RoverPowerStorage &rover_power,\
                                              RoverTimeActions &rover_time_actions,\
                                              RoverAPI &rover_api,\
                                              MarsTerrain &mars_terrain)
{
    // declre temp variable
    int return_value = 0;

    // Check if daylight
    if(mars_terrain.day_light())
    {
        // - Day
        // Gain Solar energy during the day if there is sufficient
        // time to deploy and retract panels and if power is less than half its capacity
        day_light_processing(mars_terrain, \
                             rover_api, \
                             rover_power, \
                             rover_time_actions,\
                             worst_case_scenario_time_variable,\
                             worst_case_scenario_power_variable);
    }
    else
    {
        // - Night
        return_value = night_time_processing(mars_terrain, \
                                             rover_api, \
                                             rover_power, \
                                             rover_time_actions, \
                                             worst_case_scenario_time_variable, \
                                             worst_case_scenario_power_variable);

    }

    return return_value;
}

void OverallControlAlgorithm::survey_transmit(RoverPowerStorage &rover_power, MarsTerrain &mars_terrain, RoverAPI &rover_api, RoverTimeActions &rover_time_actions)
{
    // Survey and transmit and perform relevant calculations on power and time
    rover_api.survey_and_transmit_current_zone();

    // call power consumption and Time deduction Adjustment function
    expense_time_power(rover_power,\
                       rover_power.survey_zone_and_transmit_data(),\
                       rover_time_actions.survey_zone_and_transmit_data(),\
                       mars_terrain);
}

void OverallControlAlgorithm::expense_time_power(RoverPowerStorage &rover_power, double power_deduction, double rover_time_deduction, MarsTerrain &mars_terrain)
{
    // Power consumption
    rover_power.setCurrent_power_level(rover_power.current_power_level()-power_deduction);

    // Time spent
    mars_terrain.setSol_time_remaining(mars_terrain.sol_time_remaining()-rover_time_deduction);

}

bool OverallControlAlgorithm::scan_area(MarsTerrain &mars_terrain, RoverTimeActions &rover_time_actions, RoverPowerStorage &rover_power, RoverAPI &rover_api)
{
    // declare temp variable
    bool navigable = rover_api.scan_for_navigable();

    // call power consumption and Time deduction Adjustment function
    expense_time_power(rover_power,\
                       rover_power.scan_using_camera(),\
                       rover_time_actions.scan_using_camera(),\
                       mars_terrain);

    return navigable;
}

void OverallControlAlgorithm::rover_camera_alignment(RoverAPI &rover_api, MarsTerrain &mars_terrain, RoverPowerStorage &rover_power, RoverTimeActions &rover_time_actions)
{
    if(rover_api.current_rover_orientation() != rover_api.current_camera_orientation())
    {
        // Rotate Rover
        // get current rover orientation
        if((rover_api.current_rover_orientation() == NORTH &&
            rover_api.current_camera_orientation() == EAST) ||
                (rover_api.current_rover_orientation() == EAST &&
                 rover_api.current_camera_orientation() == SOUTH) ||
                (rover_api.current_rover_orientation() == WEST &&
                 rover_api.current_camera_orientation() == NORTH) ||
                (rover_api.current_rover_orientation() == SOUTH &&
                 rover_api.current_camera_orientation() == WEST))
        {
            rover_api.rotate(CLOCKWISE);
        }
        else
        {
            rover_api.rotate(ANTI_CLOCKWISE);
        }

        // call power consumption and Time deduction Adjustment function
        expense_time_power(rover_power,\
                           rover_power.rotate_rover_by_90_degrees(),\
                           rover_time_actions.rotate_rover_by_90_degrees(),\
                           mars_terrain);

    }
}

void OverallControlAlgorithm::best_alignment_rover_camera_heading(RoverPowerStorage &rover_power, RoverAPI &rover_api, MarsTerrain &mars_terrain, RoverTimeActions &rover_time_actions)
{
    CARDINAL_POINTS direction_to_head_in;

    // check if area zoned previously

    switch (rover_api.current_camera_orientation()) {
    case NORTH:
    case SOUTH:
        if(!area_prev_zoned(rover_api.current_x()+1, rover_api.current_y(), rover_api))
            direction_to_head_in = (EAST);
        else if(!area_prev_zoned(rover_api.current_x()-1, rover_api.current_y(), rover_api))
            direction_to_head_in = (WEST);
        break;

    case EAST:
    case WEST:
        if(!area_prev_zoned(rover_api.current_x()+1, rover_api.current_y(), rover_api))
            direction_to_head_in = (SOUTH);
        else if(!area_prev_zoned(rover_api.current_x()-1, rover_api.current_y(), rover_api))
            direction_to_head_in = (NORTH);
        break;

    default:
        break;
    }

    // Rotate Camera
    rover_api.setCurrent_camera_orientation(direction_to_head_in);

    // call power consumption and Time deduction Adjustment function
    expense_time_power(rover_power,\
                       rover_power.rotate_camera_by_90_degrees(),\
                       rover_time_actions.rotate_camera_by_90_degrees(),\
                       mars_terrain);
}

bool OverallControlAlgorithm::area_prev_zoned(int x, int y, RoverAPI &rover_api)
{
    // set values
    QPair<int, int> temp_value;
    temp_value.first = x;
    temp_value.second = y;

    bool zoned_area = false;

    // --- mission continue
    for(int i = 0; i < rover_api.zoned_areas().size(); i++)
    {
        // ---- loop through to validate history of scanned zones
        if(rover_api.zoned_areas().at(i) == temp_value)
        {
            zoned_area = true;
        }
    }

    return zoned_area;
}

void OverallControlAlgorithm::day_light_processing(MarsTerrain &mars_terrain, \
                                                   RoverAPI &rover_api, \
                                                   RoverPowerStorage &rover_power, \
                                                   RoverTimeActions &rover_time_actions,\
                                                   double worst_case_scenario_time_variable,\
                                                   double worst_case_scenario_power_variable)
{
    // check if time available for deployment and retraction of solar panels and
    // check if enough energy stored to deploy solar panels
    if((mars_terrain.sol_time_remaining() >
        (rover_time_actions.deploy_solar_panels() + rover_time_actions.retract_solar_panels())) &&
            rover_power.current_power_level() <= (rover_power.deploy_solar_panels() + rover_power.deploy_solar_panels())+worst_case_scenario_power_variable)
    {
        // if solar panels not deployed... DEPLOY
        if(!rover_api.solar_panels_deployed())
        {
            // deploy solar panels
            rover_api.deploy_solar_panels();

            // --- adjust power, time variables
            // --- power deduction
            expense_time_power(rover_power,\
                               rover_power.deploy_solar_panels(),\
                               rover_time_actions.deploy_solar_panels(),\
                               mars_terrain);
        }


        // gain energy until capictive is full or day time runs out with
        // enough time to retract solar panels to start immedietly at nightfall
        // convert time "seconds" into solar gain hours minus the time taken to retract solar panels
        double time_remaining_seconds = mars_terrain.sol_time_remaining() - rover_time_actions.retract_solar_panels();
        // convert to hours
        double time_remaining_hours = (time_remaining_seconds / 60)/60;

        // gain energy per hour
        rover_power.setCurrent_power_level((rover_power.solar_power_gain_day()*time_remaining_hours)+rover_power.current_power_level());

        // capicitive Storage loss
        rover_power.setTotal_capacitive_energy_store(rover_power.total_capacitive_energy_store() - (rover_power.capacitive_store_loss_while_charging()*time_remaining_hours));


        // only retract once energy levels ae optimised... hibernate (keep solar panels active) until then
        if(rover_power.current_power_level() > (rover_power.deploy_solar_panels() + rover_power.deploy_solar_panels())+worst_case_scenario_power_variable)
        {
            // retract solar panels
            rover_api.retract_solar_panels();

            // --- adjust power, time variables
            // --- power deduction
            expense_time_power(rover_power,\
                               rover_power.retract_solar_panels(),\
                               rover_time_actions.retract_solar_panels(),\
                               mars_terrain);
        }


        // set to night
        mars_terrain.setDay_light(false);

        // reset time remaing per sol
        mars_terrain.setSol_time_remaining(mars_terrain.day_light_seconds() + mars_terrain.night_duration_seconds());

        // end of SOL day (incrent counters)
        mars_terrain.setSol_days_spent_on_mars(mars_terrain.sol_days_spent_on_mars()+1);
    }
    else
    {
        // return
    }
}

int OverallControlAlgorithm::night_time_processing(MarsTerrain &mars_terrain,\
                                                   RoverAPI &rover_api,\
                                                   RoverPowerStorage &rover_power,\
                                                   RoverTimeActions &rover_time_actions,\
                                                   double worst_case_scenario_time_variable,\
                                                   double worst_case_scenario_power_variable)
{
    // initialise temp variables
    bool navigable  = false;
    bool zoned_area = false;

    // - Check Minutes & Power remaining against worst case scenaria Time and Power &
    // - Check Minutes & Power consumption remaing against deploying solar panels
    // - Check if solar panels are dployed
    if(((mars_terrain.sol_time_remaining() >= worst_case_scenario_time_variable) &&
        rover_power.current_power_level()  >= worst_case_scenario_power_variable) &&
            (rover_power.current_power_level() >= (rover_power.deploy_solar_panels()+rover_power.retract_solar_panels())+worst_case_scenario_power_variable) &&
            (mars_terrain.sol_time_remaining() >= rover_time_actions.deploy_solar_panels()) &&
            (!rover_api.solar_panels_deployed()))
    {
        // -- Perform Operation
        if(rover_api.zones_scanned() == 0)
        {
            // --- Rover started
            // --- Survey current zone and transmit
            survey_transmit(rover_power, mars_terrain, rover_api, rover_time_actions);

            // --- return
            return 0;
        }
        else
        {
            // check if area zoned previously
            zoned_area = area_prev_zoned(rover_api.current_x(), rover_api.current_y(), rover_api);

            // not zoned area
            if(!zoned_area)
            {
                // --- Rover started
                // --- Survey current zone and transmit
                survey_transmit(rover_power, mars_terrain, rover_api, rover_time_actions);

                // --- return
                return 0;
            }
            else
            {
                // --- current zone, zoned

                // --- scan along current zone
                navigable = scan_area(mars_terrain, rover_time_actions, rover_power, rover_api);

                if(navigable)
                {
                    // set camera and rover to face same direection
                    rover_camera_alignment(rover_api, mars_terrain, rover_power, rover_time_actions);

                    // Move
                    rover_api.move();

                    // --- adjust power, time variables
                    // --- power deduction
                    expense_time_power(rover_power,\
                                       rover_power.move_forward(),\
                                       rover_time_actions.move_forward(),\
                                       mars_terrain);

                    // --- Survey current zone and transmit
                    survey_transmit(rover_power, mars_terrain, rover_api, rover_time_actions);

                    // --- return
                    return 0;

                }
                else
                {
                    // Not naviagble
                    best_alignment_rover_camera_heading(rover_power, \
                                                        rover_api, \
                                                        mars_terrain, \
                                                        rover_time_actions);
                    // return 0;
                    return 0;
                }
            }
        }
    }
    else
    {
        if(rover_api.solar_panels_deployed())
        {
            // increment counter to days spent charging
            mars_terrain.setSol_days_spent_in_hibernation(mars_terrain.sol_days_spent_in_hibernation()+1);
        }

        // -- Hibernate Rover Until DayLight (To store energy)
        rover_api.setRover_in_hibernation(true);

        // -- Wait until DayLight (Simmulate moving of time... To Day (1/2 of Sol Time left) SOl = Night + Day)
        mars_terrain.setSol_time_remaining(mars_terrain.night_duration_seconds());

        // -- set flags
        mars_terrain.setDay_light(true);

    }
}

double OverallControlAlgorithm::worst_case_scenario_time() const
{
    return worst_case_scenario_time_;
}

double OverallControlAlgorithm::worst_case_scenario_power() const
{
    return worst_case_scenario_power_;
}

void OverallControlAlgorithm::setWorst_case_scenario_time(double worst_case_scenario_time)
{
    worst_case_scenario_time_ = worst_case_scenario_time;
}

void OverallControlAlgorithm::setWorst_case_scenario_power(double worst_case_scenario_power)
{
    worst_case_scenario_power_ = worst_case_scenario_power;
}
