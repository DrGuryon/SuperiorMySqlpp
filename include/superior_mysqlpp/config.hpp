/*
 * Author: Jiří Kozlovský
 */

#pragma once

#include <string>

namespace SuperiorMySqlpp
{
    struct SslConfiguration
    {
        const char* keyPath = nullptr;
        const char* certificatePath = nullptr;
        const char* certificationAuthorityPath = nullptr;
        const char* trustedCertificateDirPath = nullptr;
        const char* allowableCiphers = nullptr;
    };

    class ConnectionConfig {
        private:
            ConnectionConfig(const bool _hasSsl, const struct SslConfiguration& _sslConfig, const std::string& _database, const std::string& _user, const std::string& _password,
                    const std::string& _target, const std::uint16_t _port=0) : 
                hasSsl{_hasSsl},
                sslConfig{_sslConfig},
                usingSocket{_port == 0},
                database{_database},
                user{_user},
                password{_password},
                target{_target},
                port{_port}
            { }

        public:

            const bool hasSsl;
            const struct SslConfiguration sslConfig;

            const bool usingSocket;

            const std::string database;
            const std::string user;
            const std::string password;
            const std::string target;
            const std::uint16_t port;


            static ConnectionConfig getSslTcpConnectionConfig(const SslConfiguration& sslConfig, const std::string& database,
                    const std::string& user, const std::string& password, const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig{true, sslConfig, database, user, password, host, port};
            }

            static ConnectionConfig getTcpConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig{false, SslConfiguration{}, database, user, password, host, port};
            }

            static ConnectionConfig getSslSocketConnectionConfig(const SslConfiguration& sslConfig, const std::string& database, 
                    const std::string& user, const std::string& password, const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig{true, sslConfig, database, user, password, socket};
            }

            static ConnectionConfig getSocketConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig{false, SslConfiguration{}, database, user, password, socket};
            }

            ConnectionConfig(const ConnectionConfig&) = default;
            virtual ~ConnectionConfig() = default;
    };
}
