#ifndef PASSWORD_H
#define PASSWORD_H

typedef struct {
    char *service;
    char *email;
    char *username;
    char *password;
} PasswordEntry;

PasswordEntry *password_create(void);

#endif