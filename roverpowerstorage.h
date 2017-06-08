#ifndef ROVERPOWERSTORAGE_H
#define ROVERPOWERSTORAGE_H

#include <QObject>

/*!
 * \brief The RoverPowerStorage class - declares rovers constants and calculates power consumption
 */
class RoverPowerStorage : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief RoverPowerStorage
     * \param parent
     */
    explicit RoverPowerStorage(QObject *parent = 0);

    /*!
     * \brief solar_power_gain_day
     * \return
     */
    double solar_power_gain_day() const;

    /*!
     * \brief solar_power_gain_night
     * \return
     */
    double solar_power_gain_night() const;

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
     * \brief scan_using_camera
     * \return
     */
    double scan_using_camera() const;

    /*!
     * \brief survey_zone_and_transmit_data
     * \return
     */
    double survey_zone_and_transmit_data() const;

    /*!
     * \brief move_forward
     * \return
     */
    double move_forward() const;

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
     * \brief capacitive_store_loss_while_charging
     * \return
     */
    double capacitive_store_loss_while_charging() const;

    /*!
     * \brief current_power_level
     * \return
     */
    double current_power_level() const;

    /*!
     * \brief setCurrent_power_level
     * \param current_power_level
     */
    void setCurrent_power_level(double current_power_level);


    /*!
     * \brief total_capacitive_energy_store
     * \return
     */
    double total_capacitive_energy_store() const;

    /*!
     * \brief setTotal_capacitive_energy_store
     * \param total_capacitive_energy_store
     */
    void setTotal_capacitive_energy_store(double total_capacitive_energy_store);

    /*!
     * \brief initial_capacitive_energy_store
     * \return
     */
    double initial_capacitive_energy_store() const;

signals:

public slots:

private:
    // Power Storage (non constant)
    double current_power_level_;
    double total_capacitive_energy_store_;

    // Power Storage constants "in (converted) Joules (J) per hour" as stipulated
    const double initial_capacitive_energy_store_      = 20500;
    const double move_forward_                         = 1020;
    const double scan_using_camera_                    = 30;
    const double solar_power_gain_day_                 = 36;
    const double deploy_solar_panels_                  = 600;
    const double retract_solar_panels_                 = 600;
    const double solar_power_gain_night__              = 0;
    const double rotate_rover_by_90_degrees_           = 103;
    const double rotate_camera_by_90_degrees_          = 9.45;
    const double survey_zone_and_transmit_data_        = 500;
    const double capacitive_store_loss_while_charging_ = 3.6;
};

#endif // ROVERPOWERSTORAGE_H
