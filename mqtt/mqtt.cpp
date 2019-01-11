#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "kidbright32.h"
#include "mqtt.h"

static const char *TAG = "MQTT_EXAMPLE";

Message MQTT::message = {nullptr, 0};
QueueTopic MQTT::sub_topic = {nullptr, nullptr};
State MQTT::state = none;
esp_mqtt_client_handle_t MQTT::client = NULL;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
			MQTT::state = connected;
        	printf("%s MQTT_EVENT_CONNECTED\n", TAG);
        	/*
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            
            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
            */
            break;

        case MQTT_EVENT_DISCONNECTED:
			MQTT::state = disconnected;
        	printf("%s MQTT_EVENT_DISCONNECTED\n", TAG);
        	/*
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            */
            break;

        case MQTT_EVENT_SUBSCRIBED:
        	printf("%s MQTT_EVENT_SUBSCRIBED\n", TAG);
        	/*
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            */
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
			printf("%s MQTT_EVENT_UNSUBSCRIBED\n", TAG);
			/*
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            */
            break;

        case MQTT_EVENT_PUBLISHED:
			printf("%s MQTT_EVENT_PUBLISHED\n", TAG);
        	/*
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            */
            break;
            
        case MQTT_EVENT_DATA:
			printf("%s MQTT_EVENT_DATA\n", TAG);
        	/*
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            */
        	char buffer_topic[64];
        	char buffer_data[64];
        	double buffer;
        	
        	
        	sprintf(buffer_topic, "%.*s", event->topic_len, event->topic);
        	sprintf(buffer_data, "%.*s", event->data_len, event->data);
            //printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            //printf("DATA=%.*s\r\n", event->data_len, event->data);
            
            buffer = atof(buffer_data);
            
            MQTT::message = {buffer_topic, buffer};
            
            printf("TOPIC=%s\r\n", MQTT::message.topic);
            printf("DATA=%1.0f\r\n",MQTT::message.data);

            break;

        case MQTT_EVENT_ERROR:
			printf("%s MQTT_EVENT_ERROR\n", TAG);
			/*
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            */
            break;
    }
    return ESP_OK;
}

MQTT::MQTT(void) {
	//
}

void MQTT::init(void) {
	MQTT::state = detect;
}

int MQTT::prop_count(void) {
	// not supported
	return 0;
}

bool MQTT::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MQTT::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MQTT::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MQTT::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MQTT::prop_write(int index, char *value) {
	// not supported
	return false;
}

void MQTT::process(Driver *drv) {
	switch (MQTT::state) {
		case detect:
			// clear error flag
			error = false;
			// set initialized flag
			initialized = true;
			printf("PROCESS DETECT\n");
			break;

		case connected:
			//printf("PROCESS CONNECTED\n");
			break;

		case disconnected:
			//printf("PROCESS CONNECTING\n");
			break;

		case subscribed:
			printf("PROCESS SUBSCRIBED\n");
			break;

		case unsubscribed:
			printf("PROCESS UNSUBSCRIBED\n");
			break;

		case published:
			printf("PROCESS PUBLISHED\n");
			break;

		case data:
			printf("PROCESS DATA\n");
			break;

		case none:
			printf("PROCESS NONE\n");
			break;
	}
}

void MQTT::connect(char *host) {
    esp_mqtt_client_config_t mqtt_cfg = {
        mqtt_event_handler,
        host,
    };

   	this->mqtt_cfg = mqtt_cfg;

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&(this->mqtt_cfg));
    MQTT::client = client;

    esp_mqtt_client_start(this->client);
	printf("CONNECTING %s\n", host);
	while (MQTT::state != connected);
}

void MQTT::subscribe(char *topic, int qos) {
    if (MQTT::state == connected) {
    	printf("BLOCKLY SUB\n");
    	/*
		Topic *ptr_topic = (Topic*) malloc(sizeof (Topic));

		ptr_topic->topic = topic;
		ptr_topic->qos = qos;
		ptr_topic->next_topic = nullptr;

		if(MQTT::sub_topic.head == nullptr){
			MQTT::sub_topic.head = ptr_topic;
			MQTT::sub_topic.tail = ptr_topic;
		}
		else {
			MQTT::sub_topic.tail->next_topic = ptr_topic;
			MQTT::sub_topic.tail = ptr_topic;
		}
		*/
		esp_mqtt_client_subscribe(this->client, topic, qos);
    }
}

void MQTT::unsubscribe(char *topic) {
    if (MQTT::state == connected){
        printf("BLOCKLY UNSUB\n");
        esp_mqtt_client_unsubscribe(this->client, topic);
    }
}

void MQTT::publish(char *topic, char *data, int len, int qos, int retain) {
	if (MQTT::state == connected){
		printf("BLOCKLY PUB\n");
		esp_mqtt_client_publish(this->client, topic, data, len, qos, retain);
	}
}

void MQTT::publish(char *topic, double &data, int len, int qos, int retain) {
	char buffer[64];
	sprintf(buffer, "%f", data);
	if (MQTT::state == connected){
		printf("BLOCKLY PUB\n");
		esp_mqtt_client_publish(this->client, topic, buffer, len, qos, retain);
	}
}



double MQTT::getMessage() const {
	printf("GET MESSAGE %0.0f\n", MQTT::message.data);
	return MQTT::message.data;
}