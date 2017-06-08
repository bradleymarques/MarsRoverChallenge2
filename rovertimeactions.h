#ifndef ROVERTIMEACTIONS_H
#define ROVERTIMEACTIONS_H

#include <QObject>

/*!
 * \brief The RoverTimeActions class - Declares the constant of rover actions and calculates relevant actions
 */
class RoverTimeActions
{
public:
    /*!
     * \brief RoverTimeActions
     */
    RoverTimeActions();

    // Getters of constants

    /*!
     * \brief move_forward
     * \return
     */
    double move_forward() const;

    /*!
     * \brief scan_using_camera
     * \return
     */
    double scan_using_camera() const;

    /*!
     * \brief deploy_solar_panels
     * \return
     */
    double deploy_solar_panels() const;

    /*!
     * \brief retract_solar_panels
     * \return
     */
    double retract_solar_panels() const;

    /*!
     * \brief rotate_rover_by_90_degrees
     * \return
     */
    double rotate_rover_by_90_degrees() const;

    /*!
     * \brief rotate_camera_by_90_degrees
     * \return
     */
    double rotate_camera_by_90_degrees() const;

    /*!
     * \brief survey_zone_and_transmit_data
     * \return
     */
    double survey_zone_and_transmit_data() const;

private:
    // Time constants "(converted) in seconds" as stipulated
    const double move_forward_                  = 360;
    const double scan_using_camera_             = 120;
    const double deploy_solar_panels_           = 9000;
    const double retract_solar_panels_          = 9000;
    const double rotate_rover_by_90_degrees_    = 65;
    const double rotate_camera_by_90_degrees_   = 5;
    const double survey_zone_and_transmit_data_ = 4020;
};

#endif // ROVERTIMEACTIONS_H
