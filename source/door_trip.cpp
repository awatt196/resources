// door_trip (from Sharpir) sensor resource implementation
 
#include "mbed.h"
#include "nsdl_support.h"
#include "sensor_ctl.h"
#include "node_cfg.h"
 
#define DOOR_TRIP_RES_ID    "/sen/door/trip"
#define DOOR_TRIP_RES_RT    "Door Trip"


#if NODE_DOOR_TRIP_STATION
extern bool current_door_trip_value;
static char door_trip_val[2];
static uint8_t max_age = 0; 
static uint8_t content_type = 50;
 
static uint8_t obs_number = 0;
static uint8_t *obs_token_ptr = NULL;
static uint8_t obs_token_len = 0;


//This is to be called from main program loop... it only sends report if door tripped.
void door_trip_report() {
    if(obs_number != 0){
        obs_number++;
        snprintf(door_trip_val,2,"%d" ,current_door_trip_value);
        if(sn_nsdl_send_observation_notification(obs_token_ptr, obs_token_len, (uint8_t*)door_trip_val, 1, &obs_number, 1, COAP_MSG_TYPE_NON_CONFIRMABLE, 0) == 0) {
            pc.printf("Door Trip Observation Sending Failed\r\n");
        } else {
            pc.printf("Door Trip Observation Sent\r\n");
        }
    }
} 


 
/* Only GET method allowed */
static uint8_t door_trip_resource_cb(sn_coap_hdr_s *received_coap_ptr, sn_nsdl_addr_s *address, sn_proto_info_s * proto)
{
    sn_coap_hdr_s *coap_res_ptr = 0;
    snprintf(door_trip_val,2,"%d" ,current_door_trip_value);
    pc.printf("door_trip callback\r\n");
    pc.printf("door_trip: %s\r\n", door_trip_val);
 
    if(received_coap_ptr->msg_code == COAP_MSG_CODE_REQUEST_GET)
    {
        coap_res_ptr = sn_coap_build_response(received_coap_ptr, COAP_MSG_CODE_RESPONSE_CONTENT);
 
        coap_res_ptr->payload_len = strlen(door_trip_val);
        coap_res_ptr->payload_ptr = (uint8_t*)door_trip_val;
        
        coap_res_ptr->content_type_ptr = &content_type;
        coap_res_ptr->content_type_len = sizeof(content_type);
        

        if(received_coap_ptr->token_ptr){
            pc.printf("   Token included\r\n");
            if(obs_token_ptr)
            {
                free(obs_token_ptr);
                obs_token_ptr = 0;
            }
            obs_token_ptr = (uint8_t*)malloc(received_coap_ptr->token_len);
            if(obs_token_ptr){
                memcpy(obs_token_ptr, received_coap_ptr->token_ptr, received_coap_ptr->token_len);
                obs_token_len = received_coap_ptr->token_len;
            }
        }
    
        if(received_coap_ptr->options_list_ptr->observe){
            coap_res_ptr->options_list_ptr = (sn_coap_options_list_s*)malloc(sizeof(sn_coap_options_list_s));
            memset(coap_res_ptr->options_list_ptr, 0, sizeof(sn_coap_options_list_s));
            coap_res_ptr->options_list_ptr->observe_ptr = &obs_number;
            coap_res_ptr->options_list_ptr->observe_len = 1;
            obs_number++;
        }
        pc.printf("   Send observation %d... \r\n", obs_number);
 
        sn_nsdl_send_coap_message(address, coap_res_ptr);
        nsdl_free(coap_res_ptr->options_list_ptr);
        coap_res_ptr->options_list_ptr = NULL;
        coap_res_ptr->content_type_ptr = NULL;// parser_release below tries to free this memory
 
    }
 
    sn_coap_parser_release_allocated_coap_msg_mem(coap_res_ptr);
 
    return 0;
}
 
int create_door_trip_resource(sn_nsdl_resource_info_s *resource_ptr)
{
    obs_number++;
    nsdl_create_dynamic_resource(resource_ptr, sizeof(DOOR_TRIP_RES_ID)-1, (uint8_t*)DOOR_TRIP_RES_ID, sizeof(DOOR_TRIP_RES_RT)-1, (uint8_t*)DOOR_TRIP_RES_RT, 1, &door_trip_resource_cb, (SN_GRS_GET_ALLOWED));
    return 0;
}
#endif
