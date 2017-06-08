#ifndef ROVERAPI_H
#define ROVERAPI_H

#include <QObject>
#include <marsterrain.h>
#include <rovertimeactions.h>
#include <roverpowerstorage.h>

/*!
 * \brief The DIRECTION enum - Enums are all CAPTIAL LETTERS with an E_ preceding the enumorator
 */
enum DIRECTION{
    CLOCKWISE = 0,
    ANTI_CLOCKWISE = 1
};

/*!
 * \brief The CARDINAL_POINTS ENUM - Cardinal Points as Indexes
 */
enum CARDINAL_POINTS{
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST = 3
};

/*!
 * \brief The RoverAPI class - This class simulates the Rover API with added relevant functionality
 */
class RoverAPI : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief RoverAPI - constructor
     * \param parent
     */
    explicit RoverAPI(QObject *parent = 0);

    /*!
     * \brief move (API Defined)
     */
    void move();

    /*!
     * \brief rotate (API Defined) - rotate rover
     * \param direction
     */
    void rotate(DIRECTION direction);

    /*!
     * \brief scan_for_navigable - scan zone ahead
     * \return
     */
    bool scan_for_navigable();

    /*!
     * \brief deploy_solar_panels (API Defined)
     */
    void deploy_solar_panels();

    /*!
     * \brief retract_solar_panels (API Defined)
     */
    void retract_solar_panels();

    /*!
     * \brief survey_and_transmit_current_zone
     */
    void survey_and_transmit_current_zone();

    /*!
     * \brief current_x - location stored to calculate zones surveyed already
     * \return
     */
    int current_x() const;

    /*!
     * \brief setCurrent_x
     * \param current_x
     */
    void setCurrent_x(int current_x);

    /*!
     * \brief current_y - location stored to calculate zones surveyed already
     * \return
     */
    int current_y() const;

    /*!
     * \brief setCurrent_y
     * \param current_y
     */
    void setCurrent_y(int current_y);

    /*!
     * \brief current_rover_orientation
     * \return
     */
    CARDINAL_POINTS current_rover_orientation() const;

    /*!
     * \brief setCurrent_rover_orientation
     * \param current_rover_orientation
     */
    void setCurrent_rover_orientation(const CARDINAL_POINTS &current_rover_orientation);

    /*!
     * \brief current_camera_orientation
     * \return
     */
    CARDINAL_POINTS current_camera_orientation() const;

    /*!
     * \brief setCurrent_camera_orientation
     * \param current_camera_orientation
     */
    void setCurrent_camera_orientation(const CARDINAL_POINTS &current_camera_orientation);

    /*!
     * \brief rover_in_hibernation - rover not performing any action until oportune time arrives to perform relevant action
     * \return
     */
    bool rover_in_hibernation() const;

    /*!
     * \brief setRover_in_hibernation
     * \param rover_in_hibernation
     */
    void setRover_in_hibernation(bool rover_in_hibernation);

    /*!
     * \brief zones_scanned - return number of zones scanned
     * \return
     */
    int zones_scanned() const;

    /*!
     * \brief setZones_scanned
     * \param zones_scanned
     */
    void setZones_scanned(int zones_scanned);

    /*!
     * \brief zoned_areas - return list of zones(x, y) scan to validate if zoned already
     * \return
     */
    QList<QPair<int, int> > zoned_areas() const;

    /*!
     * \brief solar_panels_deployed - returns if the solar panels are deployed
     * \return
     */
    bool solar_panels_deployed() const;

    /*!
     * \brief setSolar_panels_deployed
     * \param solar_panels_deployed
     */
    void setSolar_panels_deployed(bool solar_panels_deployed);

signals:
    
public slots:
    
private:
    // counter
    int zones_scanned_;
    // bool
    bool rover_in_hibernation_;
    bool solar_panels_deployed_;

    // Rover Position X, Y
    int current_x_;
    int current_y_;

    // zoned areas
    QList< QPair <int, int> > zoned_areas_;

    // Rover Orientation
    CARDINAL_POINTS current_rover_orientation_;
    // Camera Orientation
    CARDINAL_POINTS current_camera_orientation_;


};

#endif // ROVERAPI_H
