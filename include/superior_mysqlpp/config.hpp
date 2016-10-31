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
                sslConfig{_sslConfig},
                hasSsl{_hasSsl},
                usingSocket{_port == 0},
                database{_database},
                user{_user},
                password{_password},
                target{_target},
                port{_port}
            { }

            ConnectionConfig(const struct SslConfiguration& _sslConfig, const std::string& _database, const std::string& _user, const std::string& _password,
                    const std::string& _target, const std::uint16_t _port=0) : 
                ConnectionConfig{true, _sslConfig, _database, _user, _password, _target, _port}
            { }

            ConnectionConfig(const std::string& _database, const std::string& _user, const std::string& _password,
                    const std::string& _target, const std::uint16_t _port=0) :
                ConnectionConfig{false, SslConfiguration{}, _database, _user, _password, _target, _port}
            { }

        public:

            const std::string database;
            const std::string user;
            const std::string password;
            const std::string target;
            const std::uint16_t port = 0;

            const bool usingSocket = false;
            const bool hasSsl = false;

            const struct SslConfiguration sslConfig;

            static ConnectionConfig getTcpConnectionConfig(const SslConfiguration& sslConfig, const std::string& database,
                    const std::string& user, const std::string& password, const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig{sslConfig, database, user, password, host, port};
            }

            static ConnectionConfig getTcpConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig{database, user, password, host, port};
            }

            static ConnectionConfig getSocketConnectionConfig(const SslConfiguration& sslConfig, const std::string& database, 
                    const std::string& user, const std::string& password, const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig{sslConfig, database, user, password, socket};
            }

            static ConnectionConfig getSocketConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig{database, user, password, socket};
            }

            ConnectionConfig(const ConnectionConfig&) = default;
            virtual ~ConnectionConfig() = default;
    };
}
