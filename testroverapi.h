#ifndef TESTROVERAPI_H
#define TESTROVERAPI_H

#include <QObject>

/*!
 * \brief The TestRoverAPI class - Test Rover API Basic Functionality
 */
class TestRoverAPI : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TestRoverAPI
     * \param parent
     */
    explicit TestRoverAPI(QObject *parent = 0);

    /*!
     * \brief test_main
     * \return
     */
    int test_main();
signals:

public slots:
};

#endif // TESTROVERAPI_H
