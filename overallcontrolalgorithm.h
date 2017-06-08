#ifndef OVERALLCONTROLALGORITHM_H
#define OVERALLCONTROLALGORITHM_H

#include <QObject>
#include <roverapi.h>
#include <marsterrain.h>
#include <rovertimeactions.h>
#include <roverpowerstorage.h>
#include <overallcontrolalgorithm.h>

/*!
 * \brief The OverallControlAlgorithm class - Includes the main algorithm with helping functions
 */
class OverallControlAlgorithm : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief OverallControlAlgorithm
     * \param parent
     */
    explicit OverallControlAlgorithm(QObject *parent = 0);

    /*!
     * \brief start_algorithm
     * \param zones_scanned
     * \param sols_lasted
     * \return
     */
    int start_algorithm(int &zones_scanned, \
                         int &sols_lasted);

    /*!
     * \brief expense_time_power - calculates the power consumption of action and time spent (Updates relevant classes)
     * \param rover_power
     * \param power_deduction
     * \param rover_time_deduction
     * \param mars_terrain
     */
    void expense_time_power(RoverPowerStorage &rover_power, \
                           double power_deduction,\
                           double rover_time_deduction, \
                           MarsTerrain &mars_terrain);

    /*!
     * \brief rover_camera_alignment - calls to align the rover orintation with camera
     * \param rover_api
     * \param mars_terrain
     * \param rover_power
     * \param rover_time_actions
     */
    void rover_camera_alignment(RoverAPI &rover_api, \
                                MarsTerrain &mars_terrain, \
                                RoverPowerStorage &rover_power, \
                                RoverTimeActions &rover_time_actions);


    /*!
     * \brief worst_case_scenario_time - return the worst case scenario in terms of time spent for several actions
     * \return
     */
    double worst_case_scenario_time() const;

    /*!
     * \brief worst_case_scenario_power - return the worst case scenario in terms of power consumed for several actions
     * \return
     */
    double worst_case_scenario_power() const;

signals:

public slots:

private:
    // variables for worst case scenarios used as validation criteria before an action is performed
    // this reduces the failing of rover
    double worst_case_scenario_time_;
    double worst_case_scenario_power_;

    /*!
     * \brief simulate_sol_day  - second to main algorithm simulating SOL Days
     * \param worst_case_scenario_time_variable
     * \param worst_case_scenario_power_variable
     * \param rover_power
     * \param rover_time_actions
     * \param rover_api
     * \param mars_terrain
     * \return
     */
    int simulate_sol_day(double worst_case_scenario_time_variable, \
                           double worst_case_scenario_power_variable, \
                           RoverPowerStorage &rover_power, \
                            RoverTimeActions &rover_time_actions, \
                            RoverAPI &rover_api, \
                            MarsTerrain &mars_terrain);

    /*!
     * \brief survey_transmit - call to rover api to survey and transmit
     * \param rover_power
     * \param mars_terrain
     * \param rover_api
     * \param rover_time_actions
     */
    void survey_transmit(RoverPowerStorage &rover_power, \
                         MarsTerrain &mars_terrain, \
                         RoverAPI &rover_api, \
                         RoverTimeActions &rover_time_actions);


    /*!
     * \brief scan_area - call to rover api to scan area
     * \param mars_terrain
     * \param rover_time_actions
     * \param rover_power
     * \param rover_api
     * \return
     */
    bool scan_area(MarsTerrain &mars_terrain, \
                   RoverTimeActions &rover_time_actions, \
                   RoverPowerStorage &rover_power, \
                   RoverAPI &rover_api);


    /*!
     * \brief best_alignment_rover_camera_heading - calculates best orientation before scanning
     * \param rover_power
     * \param rover_api
     * \param mars_terrain
     * \param rover_time_actions
     */
    void best_alignment_rover_camera_heading(RoverPowerStorage &rover_power, \
                                             RoverAPI &rover_api, \
                                             MarsTerrain &mars_terrain, \
                                             RoverTimeActions &rover_time_actions);

    /*!
     * \brief area_prev_zoned - checks if specified surronding area scanned
     * \param x
     * \param y
     * \param rover_api
     * \return
     */
    bool area_prev_zoned(int x, int y, RoverAPI &rover_api);


    /*!
     * \brief day_light_processing - perform actions during day
     * \param mars_terrain
     * \param rover_api
     * \param rover_power
     * \param rover_time_actions
     * \param worst_case_scenario_time_variable
     * \param worst_case_scenario_power_variable
     */
    void day_light_processing(MarsTerrain &mars_terrain, \
                              RoverAPI &rover_api, \
                              RoverPowerStorage &rover_power, \
                              RoverTimeActions &rover_time_actions,\
                              double worst_case_scenario_time_variable,\
                              double worst_case_scenario_power_variable);


    /*!
     * \brief night_time_processing - perform actions during night
     * \param mars_terrain
     * \param rover_api
     * \param rover_power
     * \param rover_time_actions
     * \param worst_case_scenario_time
     * \param worst_case_scenario_power
     */
    int night_time_processing(MarsTerrain &mars_terrain, \
                               RoverAPI &rover_api, \
                               RoverPowerStorage &rover_power, \
                               RoverTimeActions &rover_time_actions, \
                               double worst_case_scenario_time_variable, \
                               double worst_case_scenario_power_variable);


    /*!
     * \brief setWorst_case_scenario_time
     * \param worst_case_scenario_time
     */
    void setWorst_case_scenario_time(double worst_case_scenario_time);

    /*!
     * \brief setWorst_case_scenario_power
     * \param worst_case_scenario_power
     */
    void setWorst_case_scenario_power(double worst_case_scenario_power);
};

#endif // OVERALLCONTROLALGORITHM_H
