//#include <stdio.h>
//#include <stdlib.h>
#include "parser.h"
#include<string.h>
//AT_FLAG_SPECIAL flag[MAX_AT_FLAG];

STATE_MACHINE_RETURN_VALUE at_command_parser(uint8_t char_crt,AT_FLAG_SPECIAL flag){
    static uint8_t state=0;
    static uint8_t idx_colon=0;
    uint8_t cnt = 0;
    //flag[MAX_AT_FLAG]=NO_SPECIAL;
    switch(state){
        case 0:
            if(char_crt=='\r'){
                state=1;
                data.count_line = 0;
                return STATE_MACHINE_NOT_READY;
            }
            else{
                return STATE_MACHINE_NOT_READY;
            }
        
        case 1:
            if(char_crt=='\n'){
                if(flag==SPECIAL_COMMAND){
                    state= 11;
                }else{
                    state=2;
                
                }
                return STATE_MACHINE_NOT_READY;
            }else{
                return STATE_MACHINE_READY_ERROR;
            }
        case 2:
            if(char_crt=='O'){
                state = 3;
                return STATE_MACHINE_NOT_READY;
            }else if(char_crt=='E'){
                state = 7;
                return STATE_MACHINE_NOT_READY;
            }else if(char_crt=='+'){
                if(flag==NO_SPECIAL){
                state= 11;
                }else if(flag==SMS_COMMAND){
                state = 16;

                return STATE_MACHINE_NOT_READY;
            
            }else{
                //state =11;
                //flag[cnt++]=SPECIAL_COMMAND;
                
                //data.date[data.count_line][idx_colon++]=char_crt;
                return STATE_MACHINE_READY_ERROR;
            } 

        case 3:
            if(char_crt=='K'){
                data.status=1;
                state = 4;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 4:
            if(char_crt=='\r'){
                state = 5;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 5:
            if(char_crt=='\n'){
                state=0;
               
                return STATE_MACHINE_READY_OK;}
                else {
                
                
                return STATE_MACHINE_READY_ERROR;
            }
        
            
        case 7:
            if(char_crt=='R'){
                state = 8;
                data.status=2;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 8:
            if(char_crt=='R'){
                state = 9;
                 return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 9:
            if(char_crt=='O'){
                state = 10;
                 return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 10:
            if(char_crt=='R'){
                state=4;
                return STATE_MACHINE_READY_ERROR;
            }
        case 11:
           // if((char_crt!='\r')&&(char_crt!='\n')){ 
            if(char_crt>=32&&char_crt<=126){
                state=11;
                if(data.count_line<AT_COMMAND_MAX_LINES){
                if(idx_colon < AT_COMMAND_MAX_LINES_SIZE-1){
                    data.date[data.count_line][idx_colon]=char_crt;
                    idx_colon++;
                    
                                    }
            }
                return STATE_MACHINE_NOT_READY;
            }else if(char_crt=='\r'){
                state = 12;
                if(data.count_line<AT_COMMAND_MAX_LINES&&idx_colon<AT_COMMAND_MAX_LINES_SIZE){
                    data.date[data.count_line][idx_colon]='\0';
                   // printf("s-a ajuns aici");
                    data.count_line++;
                    idx_colon=0;
            }
                return STATE_MACHINE_NOT_READY;
            }else {
                
                
                return STATE_MACHINE_READY_ERROR;
            }
        case 12:

            if(char_crt=='\n'){
                state=13;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;
        case 13:

            if(char_crt=='+'){
                //if(data.count_line < AT_COMMAND_MAX_LINES-1){
                    
           // }
                state=11;
                return STATE_MACHINE_NOT_READY;
            }else if(char_crt=='\r'){
                state=14;
                return STATE_MACHINE_NOT_READY;
            }else{
                
                 
                return STATE_MACHINE_READY_ERROR;
            }


        case 14:
           if(char_crt=='\n'){
                state=15;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;


        case 15:
            if(char_crt=='O'){
                state=3;
                 return STATE_MACHINE_NOT_READY;
            }else if(char_crt=='E'){
                state=7;
                return STATE_MACHINE_NOT_READY;
            }else return STATE_MACHINE_READY_ERROR;


        case 16:
            if(char_crt>=32&&char_crt<=126){
                state=16;
                if(data.count_line<AT_COMMAND_MAX_LINES){
                if(idx_colon < AT_COMMAND_MAX_LINES_SIZE-1){
                    data.date[data.count_line][idx_colon]=char_crt;
                    idx_colon++;}
                }
            return STATE_MACHINE_NOT_READY;
        }else if(char_crt=='\r'){
            state=17;
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_ERROR;
        }


        case 17:
            if(char_crt=='\n'){
                state=18;
                if(data.count_line<AT_COMMAND_MAX_LINES){
                if(idx_colon < AT_COMMAND_MAX_LINES_SIZE-1){
                   data.date[data.count_line][idx_colon]=char_crt;
                   idx_colon++;
       }
        }
                return STATE_MACHINE_NOT_READY;
    }else {
        return STATE_MACHINE_READY_ERROR;
    }

        case 18:
            if(char_crt>=32&&char_crt<=126){
                state=19;
                if(data.count_line<AT_COMMAND_MAX_LINES){
                if(idx_colon < AT_COMMAND_MAX_LINES_SIZE-1){
                    data.date[data.count_line][idx_colon]=char_crt;
                    idx_colon++;
       }
        }
    return STATE_MACHINE_NOT_READY;
    }else {
        return STATE_MACHINE_READY_ERROR;
    }

        case 19:
        if(char_crt>=32&&char_crt<=126){
                state=19;
                if(data.count_line<AT_COMMAND_MAX_LINES){
                if(idx_colon < AT_COMMAND_MAX_LINES_SIZE-1){
                    data.date[data.count_line][idx_colon]=char_crt;
                    idx_colon++;}
                }return STATE_MACHINE_NOT_READY;
        }else if(char_crt=='\r'){
             state = 20;
                if(data.count_line<AT_COMMAND_MAX_LINES&&idx_colon<AT_COMMAND_MAX_LINES_SIZE){
                    data.date[data.count_line][idx_colon]='\0';
                   // printf("s-a ajuns aici");
                    data.count_line++;
                    idx_colon=0;
            }
            return STATE_MACHINE_NOT_READY;
        }else{
            return STATE_MACHINE_READY_ERROR;
        }

        case 20:
        if(char_crt=='\n'){
            state=21;

        return STATE_MACHINE_NOT_READY;
        }else return STATE_MACHINE_READY_ERROR;

        case 21:
        if(char_crt=='\r'){
            state=23;

        return STATE_MACHINE_NOT_READY;
        }else return STATE_MACHINE_READY_ERROR;


        case 23:
        if(char_crt=='\n'){
            state=24;

        return STATE_MACHINE_NOT_READY;
        }else return STATE_MACHINE_READY_ERROR;


        case 24:
        if(char_crt=='+'){
            state=16;
            return STATE_MACHINE_NOT_READY;
        }else if(char_crt=='O'){
            state = 3;
            return STATE_MACHINE_NOT_READY;
        }else if(char_crt=='E'){
            state=7;
            return STATE_MACHINE_NOT_READY;
        }else {
            return STATE_MACHINE_READY_ERROR;
        }
}
}

    return STATE_MACHINE_READY_OK;
        
}




