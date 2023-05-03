#include "dumessengersocket.h"


DuMessengerSocket::DuMessengerSocket(quintptr handle, QObject *parent)
    :QTcpSocket(parent)
{
    setSocketDescriptor(handle);

    connect(this, &DuMessengerSocket::readyRead, [&]() {
        emit DuReadyRead(this);
    });

    connect(this, &DuMessengerSocket::stateChanged, [&](int S) {
        emit DuStateChanged(this, S);
    });

}

