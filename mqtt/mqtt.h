#ifndef __MQTT_H__
#define __MQTT_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "mqtt_client.h"
#include "esp_log.h"
#include "string.h"

enum State {
	none,
	detect,
	connected,
	disconnected,
	subscribed,
	unsubscribed,
	published,
	data,
};

struct Message{
    char *topic;
    double data;
};

struct Topic{
	char *topic;
	int qos;
	Topic *next_topic;
};

struct QueueTopic {
	Topic *head;
	Topic *tail;
};


class MQTT : public Device {
	private:
        esp_mqtt_client_config_t mqtt_cfg;

	public:

        static Message message;
	    static QueueTopic sub_topic;    // Subscribing topic queue
		static State state;				// MQTT state
        static esp_mqtt_client_handle_t client;	// MQTT client

		TickType_t tickcnt;

		// constructor
		MQTT(void);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);

		// method
		// Blockly call-function
        void connect(char *host);
        void subscribe(char *topic, int qos=0);
        void unsubscribe(char *topic);
        void publish(char *topic, char *data, int len=0, int qos=0, int retain=0);
        void publish(char *topic, double &data, int len=0, int qos=0, int retain=0);
        double getMessage() const ;
};

#endif
