#include <../include/quic_server.hpp>
#include <iostream>
#include <msquic.h>

QuicServer::QuicServer() : Registration(nullptr), Configuration(nullptr), Listener(nullptr) {
    MsQuicOpen(&MsQuic);
    
    QUIC_REGISTRATION_CONFIG RegConfig = {"quic_server", QUIC_EXECUTION_PROFILE_LOW_LATENCY};
    MsQuic->RegistrationOpen(&RegConfig, &Registration);
    
    QUIC_SETTINGS Settings = {0};
    Settings.IdleTimeoutMs = 30000;
    Settings.IsSet.IdleTimeoutMs = TRUE;
    Settings.IsSet.PeerUnidiStreamCount = TRUE;

    MsQuic->ConfigurationOpen(
        Registration,
        &Alpn,
        1,
        &Settings,
        sizeof(Settings),
        nullptr,
        &Configuration
    );
    MsQuic->ConfigurationLoadCredential(Configuration, &CredConfig);
}

QuicServer::~QuicServer() {
    if (Listener) MsQuic->ListenerClose(Listener);
    if (Configuration) MsQuic->ConfigurationClose(Configuration);
    if (Registration) MsQuic->RegistrationClose(Registration);
    MsQuicClose(MsQuic);
}

void QuicServer::RunServer() {
    MsQuic->ListenerOpen(Registration, ServerListenerCallback, this, &Listener);
    MsQuic->ListenerStart(Listener, nullptr);
    std::cout << "Server is running. Press Enter to exit..." << std::endl;
    std::cin.get();
}

QUIC_STATUS QUIC_API QuicServer::ServerListenerCallback(
    HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event) {
    switch (Event->Type) {
        case QUIC_LISTENER_EVENT_NEW_CONNECTION: {
            MsQuic->SetCallbackHandler(
                Event->NEW_CONNECTION.Connection,
                (void*)ServerConnectionCallback,
                Context
            );
            MsQuic->ConnectionSetConfiguration(Event->NEW_CONNECTION.Connection, Configuration);
            break;
        }
        default:
            break;
    }
    return QUIC_STATUS_SUCCESS;
}

QUIC_STATUS QUIC_API QuicServer::ServerConnectionCallback(
    HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event) {
    switch (Event->Type) {
        case QUIC_CONNECTION_EVENT_PEER_STREAM_STARTED: {
            MsQuic->SetCallbackHandler(
                Event->PEER_STREAM_STARTED.Stream,
                (void*)ServerStreamCallback,
                Context
            );
            break;
        }
        default:
            break;
    }
    return QUIC_STATUS_SUCCESS;
}

QUIC_STATUS QUIC_API QuicServer::ServerStreamCallback(
    HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event) {
    switch (Event->Type) {
        case QUIC_STREAM_EVENT_RECEIVE: {
            // Data received; process it and respond.
            std::string request(reinterpret_cast<char*>(Event->RECEIVE.Buffers[0].Buffer), Event->RECEIVE.Buffers[0].Length);
            std::cout << "Request: " << request << std::endl;

            std::string response = "Response from server";  
            MsQuic->StreamSend(Stream, (QUIC_BUFFER*)&response, 1, QUIC_SEND_FLAG_FIN, nullptr);
            break;
        }
        case QUIC_STREAM_EVENT_SHUTDOWN_COMPLETE:
            MsQuic->StreamClose(Stream);
            break;
        default:
            break;
    }
    return QUIC_STATUS_SUCCESS;
}
