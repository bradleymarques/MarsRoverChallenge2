#include <QApplication>
#include <QDebug>

#include <roverapi.h>
#include <marsterrain.h>
#include <overallcontrolalgorithm.h>

#include <testroverapi.h>
#include <testmarsterrain.h>
#include <testoverallcontrolalgorithm.h>
#include <testroverpowerstorage.h>

/*!
 * \brief confirmDeploymentAssumptions - Display to console Dashboard before deployment
 * \param mars_terrain
 */
void confirmDeploymentAssumptions(MarsTerrain &mars_terrain)
{
    qDebug() << "Mars Rover Challenge 2";
    qDebug() << "Rover Deployed at 23:59";
    qDebug() << "Rover daylight time: " << mars_terrain.day_light_seconds();
    qDebug() << "Rover night duration time: " << mars_terrain.night_duration_seconds();
    qDebug() << "Assumption at deployment: Rover is fully charged and Daylight has ended... Confirmed";
    qDebug() << "Assumption Rover is facing North... Confirmed";
    qDebug() << "Assumption Rover Camera is facing North... Confirmed";
    qDebug() << "Assumption Rover Solar panels are retracted... Confirmed";
    qDebug() << "Location and Terrain of Rover is Unknown";
    qDebug() << "Algorithm caters for a 70% chance of uneven terrain";
    qDebug() << "Algorithm determines action based on random terrain to scan, rotate, survey, move and so forth";
    qDebug() << "Not all Sol days are surveying and scanning based on time and power constraints";
    qDebug() << " ";
}


/*!
 * \brief qMain - Main.cpp - Instantiates and processes Algorithm
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // declare temp variables as return values
    int error                            = -1;
    int return_value_success             = 0;
    int sols_rover_will_last_for         = 0;
    int possible_zones_to_be_scanned     = 0;

    // test classes on startup
    TestRoverAPI test_rover_api;
    TestMarsTerrain test_mars_terrain;
    TestRoverPowerStorage test_rover_power;
    TestOverallControlAlgorithm test_overall_control_algorithm;

    // Assert statements - "Will beak execution if tests fail"
    if(test_rover_api.test_main() != return_value_success)
        return error;
    else
        qDebug() << "Rover API: Test Passed";

    if(test_mars_terrain.test_main() != return_value_success)
        return error;
    else
        qDebug() << "Mars Terrain: Test Passed";

    if(test_rover_power.test_main() != return_value_success)
        return error;
    else
        qDebug() << "Rover Power: Test Passed";

    if(test_overall_control_algorithm.test_main() != return_value_success)
        return error;
    else
        qDebug() << "Algorithm: Test Passed";



    // instantiate Mars terrain
    MarsTerrain             mars_terrain;
    // instantiate algorithm
    OverallControlAlgorithm overall_control_algorithm;

    // Display Deployment Assumptions from Challenge
    confirmDeploymentAssumptions(mars_terrain);

    // begin algorithm
    overall_control_algorithm.start_algorithm(possible_zones_to_be_scanned,\
                                              sols_rover_will_last_for);

    // Display results
    qDebug() << "Possible Max Zones Scanned: " << possible_zones_to_be_scanned;
    qDebug() << "Sols Rover will last for  : " << sols_rover_will_last_for;


    return 0;
    return a.exec();
}



