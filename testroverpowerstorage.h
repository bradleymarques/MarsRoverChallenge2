#ifndef TESTROVERPOWERSTORAGE_H
#define TESTROVERPOWERSTORAGE_H

#include <QObject>

/*!
 * \brief The TestRoverPowerStorage class - tests the rover power storage and consumption class
 */
class TestRoverPowerStorage : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TestRoverPowerStorage
     * \param parent
     */
    explicit TestRoverPowerStorage(QObject *parent = 0);

    /*!
     * \brief test_main
     * \return
     */
    int test_main();
signals:

public slots:
};

#endif // TESTROVERPOWERSTORAGE_H
