#ifndef TESTMARSTERRAIN_H
#define TESTMARSTERRAIN_H

#include <QObject>

/*!
 * \brief The TestMarsTerrain class - performs test on Mars Terrain Class
 */
class TestMarsTerrain : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TestMarsTerrain
     * \param parent
     */
    explicit TestMarsTerrain(QObject *parent = 0);

    /*!
     * \brief test_main
     * \return
     */
    int test_main();

signals:

public slots:
};

#endif // TESTMARSTERRAIN_H
