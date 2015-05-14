#ifndef INPUTTHROTTLER_H
#define INPUTTHROTTLER_H

#include <joystickconnector.h>
#include <QString>
#include <QMutex>

#define JOY_RANGE               32767
#define BITS_PER_MSG_WHEELE     4               // 3 + signe bit
#define JOY_PER_MSG_SCALAR      (short)(JOY_RANGE / 7)

class InputThrottler : public QThread
{
    Q_OBJECT
    public:

        enum eOperationMode
        {
            eSafety = 0,
            eAuto,
            eManual
        };

        explicit InputThrottler(QObject* parent = 0L);
        virtual ~InputThrottler();

        void SetMode(const eOperationMode mode);

    public slots:
        void    DeviceUpdate(const InputUpdate& state);
        void    UpdateRateChanged(unsigned int ms);
        void    DeviceBtnUpdate( eBtnState state,
                                 int btnID );

    signals:
        void    StatusUpdate(const eStatus& status, const QString& message);
        void    BitsUpdate(const QString& message);
        void    PublishMessage(const QByteArray& buffer);
        void    ActuatorState( int level );

    private:
        void    PackBits();
        void    PrintBits();

    private:
        InputUpdate     _state;
        eOperationMode  _mode;
        QByteArray      _byteArray;
        QMutex          _lock;
        int             _actuatorLevel;
        bool            _updated;
        int             _sleepRate;

    protected:
       void    run(void) Q_DECL_OVERRIDE;
};

#endif // INPUTTHROTTLER_H
