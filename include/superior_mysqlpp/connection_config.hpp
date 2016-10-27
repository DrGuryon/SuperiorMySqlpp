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
            ConnectionConfig(const struct SslConfiguration* _sslConfig, const std::string& _database, const std::string& _user, const std::string& _password,
                    const std::string& _target, const std::uint16_t _port=0) : 
                hasSsl(true), usingSocket(_port == 0), port(_port), sslConfig(_sslConfig), database(_database), user(_user), password(_password), target(_target) {}

            ConnectionConfig(const std::string& _database, const std::string& _user, const std::string& _password,
                    const std::string& _target, const std::uint16_t _port=0) :
                hasSsl(false), usingSocket(_port == 0), port(_port), database(_database), user(_user), password(_password), target(_target) {}

        public:

            const std::string database;
            const std::string user;
            const std::string password;
            const std::string target;
            const std::uint16_t port = 0;

            const bool usingSocket = false;
            const bool hasSsl = false;

            const struct SslConfiguration* sslConfig;

            static ConnectionConfig getTcpConnectionConfig(const SslConfiguration* sslConfig, const std::string& database,
                    const std::string& user, const std::string& password, const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig(sslConfig, database, user, password, host, port);
            }

            static ConnectionConfig getTcpConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& host="localhost", std::uint16_t port=3306)
            {
                    return ConnectionConfig(database, user, password, host, port);
            }

            static ConnectionConfig getSocketConnectionConfig(const SslConfiguration* sslConfig, const std::string& database, 
                    const std::string& user, const std::string& password, const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig(sslConfig, database, user, password, socket);
            }

            static ConnectionConfig getSocketConnectionConfig(const std::string& database, const std::string& user, const std::string& password,
                    const std::string& socket="/var/run/mysqld/mysqld.sock")
            {
                    return ConnectionConfig(database, user, password, socket);
            }

            ConnectionConfig(const ConnectionConfig&) = default;
            virtual ~ConnectionConfig() = default;
    };
}
