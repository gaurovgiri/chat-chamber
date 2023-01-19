#include "db.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

sqlite3 *db;

static int callback(void *NotUsed, int argc, char **argv, char **azcolname)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azcolname[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void initDB()
{
    char **zerrMsg = 0;
    sqlite3_open("db/users.db", &db);
    char *sql = "CREATE TABLE IF NOT EXISTS users("
                "username TEXT PRIMARY KEY NOT NULL,"
                "password TEXT NOT NULL);";
    sqlite3_exec(db, sql, callback, 0, zerrMsg);
}

int loginUser(CLIENT info)
{
    char *query = (char *)"SELECT * FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, info.username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, info.password, -1, SQLITE_STATIC); // bcrypt(info.password)
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result == SQLITE_ROW)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int createUser(CLIENT info)
{
    char *query = (char *)"INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, info.username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, info.password, -1, SQLITE_STATIC); // bcrypt(info.password)

    result = sqlite3_step(stmt);

    if (result == SQLITE_CONSTRAINT)
    {
        return AUTH_FAILURE; // User Already Exists
    }
    else if (result != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return AUTH_FAILURE; // Failed to Execute Statement
    }
    sqlite3_finalize(stmt);
    return AUTH_SUCCESS;
}

void dbGetUser(ClientList *client, char *name)
{
    strcpy(client->username, name);
    client->role = ADMIN;
}

int dbValidate(char *invitationCode)
{
    if (strcmp(invitationCode, "correct_code") == 0)
    {
        return AUTH_SUCCESS;
    }
    else
    {
        return AUTH_FAILURE;
    }
}