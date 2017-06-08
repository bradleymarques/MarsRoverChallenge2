#ifndef TESTOVERALLCONTROLALGORITHM_H
#define TESTOVERALLCONTROLALGORITHM_H

#include <QObject>

/*!
 * \brief The TestOverallControlAlgorithm class - test functionality of Algorithm functions
 */
class TestOverallControlAlgorithm : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TestOverallControlAlgorithm
     * \param parent
     */
    explicit TestOverallControlAlgorithm(QObject *parent = 0);

    /*!
     * \brief test_main
     * \return
     */
    int test_main();
signals:

public slots:
};

#endif // TESTOVERALLCONTROLALGORITHM_H
