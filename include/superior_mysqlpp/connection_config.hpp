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
        protected:
            bool _usingSocket;

            const std::string* _database = nullptr;
            const std::string* _user = nullptr;
            const std::string* _password = nullptr;
            const std::string* _target = nullptr;

            std::uint16_t _port;

            const struct SslConfiguration* _sslConfig;
            bool _hasSsl;

        public:
            ConnectionConfig(const SslConfiguration& sslConfig)
            {
                _sslConfig = &sslConfig;
                _hasSsl = true;
            }

            ConnectionConfig()
            {
                _sslConfig = nullptr;
                _hasSsl = false;
            }

            void setTcpConnectionDetails(const std::string& database, const std::string& user, const std::string& password, const std::string& host="localhost",
                    std::uint16_t port=3306)
            {
                _usingSocket = false;

                _database = &database;
                _user = &user;
                _password = &password;

                _target = &host;
                _port = port;
            }

            void setSocketConnectionDetails(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                _usingSocket = true;

                _database = &database;
                _user = &user;
                _password = &password;
                _target = &socket;
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
                return *(_database);
            }

            const std::string& getUser()
            {
                return *(_user);
            }

            const std::string& getPassword()
            {
                return *(_password);
            }

            const std::string& getTarget()
            {
                return *(_target);
            }

            ~ConnectionConfig() = default;
    };
}
