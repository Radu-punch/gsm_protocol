#ifndef __AT_COMMADN_PARSER__
#define __AT_COMMADN_PARSER__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINES_SIZE 100
#define MAX_AT_FLAG 100
typedef enum{
    NO_SPECIAL,
    SPECIAL_COMMAND,
    SMS_COMMAND
}AT_FLAG_SPECIAL;
typedef struct{
    uint8_t date[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINES_SIZE];
    uint8_t status;  //ok=1;error=2
    uint16_t count_line;
    //AT_FLAG_SPECIAL flags[MAX_AT_FLAG];
}AT_COMMAND_DATA;


//extern AT_FLAG_SPECIAL flag[MAX_AT_FLAG];
extern AT_COMMAND_DATA data;
//extern AT_FLAG_SPECIAL flag;

typedef enum{
STATE_MACHINE_NOT_READY,
STATE_MACHINE_READY_OK,
STATE_MACHINE_READY_ERROR
}STATE_MACHINE_RETURN_VALUE;

STATE_MACHINE_RETURN_VALUE at_command_parser(uint8_t char_crt,AT_FLAG_SPECIAL flag);
#endif // __AT_COMMADN_PARSER__
