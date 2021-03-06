/* Header for OracleAnalyzerOnline class
   Copyright (C) 2018-2020 Adam Leszczynski (aleszczynski@bersler.com)

This file is part of OpenLogReplicator.

OpenLogReplicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

OpenLogReplicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenLogReplicator; see the file LICENSE;  If not see
<http://www.gnu.org/licenses/>.  */

#include "OracleAnalyzer.h"

#ifndef ORACLEANALYZERONLINE_H_
#define ORACLEANALYZERONLINE_H_

using namespace std;

namespace OpenLogReplicator {

    class DatabaseConnection;
    class DatabaseEnvironment;

    class OracleAnalyzerOnline : public OracleAnalyzer {
    protected:
        static const char* SQL_GET_ARCHIVE_LOG_LIST;
        static const char* SQL_GET_DATABASE_INFORMATION;
        static const char* SQL_GET_DATABASE_SCN;
        static const char* SQL_GET_CON_INFO;
        static const char* SQL_GET_SCN_FROM_SEQUENCE;
        static const char* SQL_GET_SCN_FROM_SEQUENCE_STANDBY;
        static const char* SQL_GET_SCN_FROM_TIME;
        static const char* SQL_GET_SCN_FROM_TIME_RELATIVE;
        static const char* SQL_GET_SEQUENCE_FROM_SCN;
        static const char* SQL_GET_SEQUENCE_FROM_SCN_STANDBY;
        static const char* SQL_GET_LOGFILE_LIST;
        static const char* SQL_GET_TABLE_LIST;
        static const char* SQL_GET_COLUMN_LIST;
        static const char* SQL_GET_COLUMN_LIST11;
        static const char* SQL_GET_PARTITION_LIST;
        static const char* SQL_GET_SUPPLEMNTAL_LOG_TABLE;
        static const char* SQL_GET_PARAMETER;
        static const char* SQL_GET_PROPERTY;

        bool isStandby;
        string user;
        string password;
        string connectString;

        virtual void start(void);
        virtual void initialize(void);
        virtual void checkConnection(void);
        void closeConnection(void);
        string getParameterValue(const char *parameter);
        string getPropertyValue(const char *property);
        void checkTableForGrants(string tableName);
        virtual const char* getModeName(void);
        virtual void refreshSchema(void);
        void addTable(string &mask, vector<string> &keys, string &keysStr, uint64_t options);

    public:
        DatabaseEnvironment *env;
        DatabaseConnection *conn;
        bool keepConnection;

        OracleAnalyzerOnline(OutputBuffer *outputBuffer, const char *alias, const char *database, uint64_t trace,
                uint64_t trace2, uint64_t dumpRedoLog, uint64_t dumpData, uint64_t flags, uint64_t disableChecks,
                uint64_t redoReadSleep, uint64_t archReadSleep, uint64_t memoryMinMb, uint64_t memoryMaxMb,
                const char *logArchiveFormat, const char *user, const char *password, const char *connectString, bool isStandby);
        virtual ~OracleAnalyzerOnline();

        static void archGetLogOnline(OracleAnalyzer *oracleAnalyzer);
    };
}

#endif
