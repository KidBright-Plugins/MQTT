# KidBright MQTT Plug-in
This is a plugin used with the KidBright board for the MQTT.

## Blocks
 - Connect to a MQTT server
 - Subscribe to a specified topic
 - Unsubscribe to a specified topic
 - Publish a message to a specified topic
 - Get a message from subscribed topics
### Connect to a MQTT server
![Optional Text](../master/docs/images/connect.png)

The block takes one argument which is a string of MQTT server

### Subscribe to a specified topic
![Optional Text](../master/docs/images/sub.png)

The block takes two arguments, first the topic to be subscribed as a string, second the qos as the number.

This block must be placed after the connection block.
![Optional Text](../master/docs/images/connect_sub.png)

### Publish a message to a specified topic
![Optional Text](../master/docs/images/pub.png)

The block takes two arguments as inputs, first the message to be publised, and the topic, both must be a string.

This block should be used in the Forever block.
![Optional Text](../master/docs/images/forever_pub.png)
