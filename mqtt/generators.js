Blockly.JavaScript['mqtt_blink'] = function(block) {
	return `DEV_IO.MQTT().blinkLED();\n`;
};

Blockly.JavaScript['mqtt_connect'] = function(block) {
    var value_host = Blockly.JavaScript.valueToCode(block, 'host', Blockly.JavaScript.ORDER_ATOMIC);
	return `DEV_IO.MQTT().connect(${value_host});\n`;
};

Blockly.JavaScript['mqtt_sub'] = function(block) {
  var value_topic = Blockly.JavaScript.valueToCode(block, 'topic', Blockly.JavaScript.ORDER_ATOMIC);
  var value_qos = Blockly.JavaScript.valueToCode(block, 'qos', Blockly.JavaScript.ORDER_ATOMIC);
  return `DEV_IO.MQTT().subscribe(${value_topic}, (int)(${value_qos}));\n`;
};

Blockly.JavaScript['mqtt_unsub'] = function(block) {
  var value_topic = Blockly.JavaScript.valueToCode(block, 'topic', Blockly.JavaScript.ORDER_ATOMIC);
  return code;
};

Blockly.JavaScript['mqtt_stop'] = function(block) {
	return 'DEV_IO.MQTT().stop();\n';
};

Blockly.JavaScript['mqtt_pub'] = function(block) {
  var value_msg = Blockly.JavaScript.valueToCode(block, 'msg', Blockly.JavaScript.ORDER_ATOMIC);
  var value_topic = Blockly.JavaScript.valueToCode(block, 'topic', Blockly.JavaScript.ORDER_ATOMIC);
  return `DEV_IO.MQTT().publish(${value_topic}, ${value_msg});\n`;
};
