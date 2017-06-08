#ifndef MARSTERRAIN_H
#define MARSTERRAIN_H

#include <QObject>

/*!
 * \brief The MarsTerrain class - contains basic info about Mars Life (Day, Night and and rover interaction on Mars)
 */
class MarsTerrain : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief MarsTerrain - constructor
     * \param parent
     */
    explicit MarsTerrain(QObject *parent = 0);

    /*!
     * \brief day_light_minutes - return number of seconds for a Sol day (daylight)
     * \return
     */
    double day_light_seconds() const;

    /*!
     * \brief night_duration_seconds  - return number of seconds for a Sol day (night)
     * \return
     */
    double night_duration_seconds() const;

    /*!
     * \brief sol_time_remaining - return number of seconds remaining for that Sol day
     * \return
     */
    double sol_time_remaining() const;

    /*!
     * \brief setSol_time_remaining
     * \param sol_time_remaining
     */
    void setSol_time_remaining(double sol_time_remaining);

    /*!
     * \brief day_light (return Is it daylight)
     * \return
     */
    bool day_light() const;

    /*!
     * \brief setDay_light
     * \param day_light
     */
    void setDay_light(bool day_light);

    /*!
     * \brief sol_days_spent_on_mars - returns number of days spent on mars
     * \return
     */
    int sol_days_spent_on_mars() const;

    /*!
     * \brief setSol_days_spent_on_mars
     * \param sol_days_spent_on_mars
     */
    void setSol_days_spent_on_mars(int sol_days_spent_on_mars);

    /*!
     * \brief sol_days_spent_in_hibernation - returns number of daylight days Rover spent charging
     * \return
     */
    int sol_days_spent_in_hibernation() const;

    /*!
     * \brief setSol_days_spent_in_hibernation
     * \param sol_days_spent_in_hibernation
     */
    void setSol_days_spent_in_hibernation(int sol_days_spent_in_hibernation);

signals:

public slots:

private:
    // Sol Day counter
    int sol_days_spent_on_mars_;
    int sol_days_spent_in_hibernation_;

    // time remaining per sol in seconds
    double sol_time_remaining_;

    // day or night
    bool day_light_;

    // time constants "in seconds"
    const double day_light_seconds_      = 44400;
    const double night_duration_seconds_ = 44400;

};

#endif // MARSTERRAIN_H
