/*
 * Author: Jiří Kozlovský
 */

#pragma once

#include <string>
#include <tuple>

#include <superior_mysqlpp/connection_def.hpp>



namespace SuperiorMySqlpp
{
    class ConnectionConfig {
        private:
            bool _usingSocket = false;
            bool _hasSsl = true;

            std::string _database;
            std::string _user;
            std::string _password;
            std::string _target;

            std::uint16_t _port;

            const struct SslConfiguration* _sslConfig;

            void setTcpConnectionDetails(const std::string database, const std::string& user, const std::string& password, const std::string& host="localhost",
                    std::uint16_t port=3306)
            {
                _database = database;
                _user = user;
                _password = password;

                _target = host;
                _port = port;
            }

            void setSocketConnectionDetails(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                _usingSocket = true;

                _database = database;
                _user = user;
                _password = password;
                _target = socket;
            }

        public:
            ConnectionConfig(const SslConfiguration& sslConfig) : _sslConfig(&sslConfig), _hasSsl(true) {};

            ConnectionConfig() : _sslConfig(nullptr), _hasSsl(false) {};

            static ConnectionConfig getTcpConnectionConfig(const SslConfiguration* sslConfig, const std::string& database,
                    const std::string& user, const std::string& password, const std::string& host="localhost", std::uint16_t port=3306)
            {
                    ConnectionConfig tcpConfig = ConnectionConfig();
                    tcpConfig.setTcpConnectionDetails(database, user, password, host, port);

                    tcpConfig._sslConfig = sslConfig;

                    return tcpConfig;
            }

            static ConnectionConfig getTcpConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& host="localhost", std::uint16_t port=3306)
            {
                ConnectionConfig tcpConfig = ConnectionConfig::getTcpConnectionConfig(nullptr, database, user, password, host, port);
                tcpConfig._hasSsl = false;

                return tcpConfig;
            }

            static ConnectionConfig getSocketConnectionConfig(const SslConfiguration* sslConfig, const std::string& database, 
                    const std::string& user, const std::string& password, const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                ConnectionConfig socketConfig = ConnectionConfig();
                socketConfig.setSocketConnectionDetails(database, user, password, socket);

                socketConfig._sslConfig = sslConfig;

                return socketConfig;
            }

            static ConnectionConfig getSocketConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                ConnectionConfig socketConfig = ConnectionConfig::getSocketConnectionConfig(nullptr, database, user, password, socket);
                socketConfig._hasSsl = false;

                return socketConfig;
            }

            const bool isUsingSocket()
            {
                return _usingSocket;
            }
            
            const bool hasSsl()
            {
                return _hasSsl;
            }

            const SslConfiguration& getSslConfig()
            {
                return *(_sslConfig);
            }

            const std::uint16_t getTcpPort()
            {
                return _port;
            }

            const std::string& getDatabase()
            {
                return _database;
            }

            const std::string& getUser()
            {
                return _user;
            }

            const std::string& getPassword()
            {
                return _password;
            }

            const std::string& getTarget()
            {
                return _target;
            }

            virtual ~ConnectionConfig() = default;
    };
}
