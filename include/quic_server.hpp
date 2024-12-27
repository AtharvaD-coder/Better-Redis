#ifndef QUIC_SERVER_HPP
#define QUIC_SERVER_HPP

#include <msquic.h>
#include <string>

class QuicServer {
public:
    QuicServer();
    ~QuicServer();
    void RunServer();

private:
    static QUIC_STATUS QUIC_API ServerListenerCallback(HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event);
    static QUIC_STATUS QUIC_API ServerConnectionCallback(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);
    static QUIC_STATUS QUIC_API ServerStreamCallback(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);

    HQUIC Registration;
    HQUIC Configuration;
    HQUIC Listener;
};

#endif
