/*Blockly.Blocks["mqtt_connect"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MQTT_CONNECT_TITLE);
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MQTT_CONNECT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MQTT_CONNECT_HELPURL);
	}
};
*/

/*
Blockly.Blocks["mqtt_stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MQTT_STOP_TITLE);
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MQTT_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MQTT_STOP_HELPURL);
	}
};
*/

Blockly.Blocks['mqtt_connect'] = {
  init: function() {
        this.appendDummyInput()
            .appendField(Blockly.Msg.MQTT_CONNECT_TITLE);
        this.appendValueInput("host")
            .setCheck("String")
            .appendField(Blockly.Msg.MQTT_CONNECT_HOST);
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(230);
        this.setTooltip(Blockly.Msg.MQTT_CONNECT_TOOLTIP);
        this.setHelpUrl(Blockly.Msg.MQTT_CONNECT_HELPURL);
    }
};

Blockly.Blocks['mqtt_sub'] = {
    init: function() {
        this.appendDummyInput()
            .appendField(Blockly.Msg.MQTT_SUB_TITLE);
        this.appendValueInput("topic")
            .setCheck("String")
            .appendField(Blockly.Msg.MQTT_TOPIC);
        this.appendValueInput("qos")
            .setCheck("Number")
            .appendField(Blockly.Msg.MQTT_QOS);
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(230);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['mqtt_unsub'] = {
    init: function() {
        this.appendDummyInput()
            .appendField(Blockly.Msg.MQTT_UNSUB_TITLE);
        this.appendValueInput("topic")
            .setCheck("String")
            .appendField(Blockly.Msg.MQTT_TOPIC);
        this.setInputsInline(true);
        this.setColour(230);
        this.setTooltip("");
        this.setHelpUrl("");
    }
};

Blockly.Blocks['mqtt_pub'] = {
  init: function() {
      this.appendDummyInput()
          .appendField(Blockly.Msg.MQTT_PUB_TITLE_1);
      this.appendValueInput("msg")
          .appendField(Blockly.Msg.MQTT_MSG);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MQTT_PUB_TITLE_2);
      this.appendValueInput("topic")
          .setCheck("String")
          .appendField(Blockly.Msg.MQTT_TOPIC);
      this.setInputsInline(true);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setColour(230);
      this.setTooltip("");
      this.setHelpUrl("");
  }
};

Blockly.Blocks['mqtt_message'] = {
    init: function() {
        this.appendDummyInput()
            .appendField(Blockly.Msg.MQTT_MESSAGE_TITLE);
        this.setInputsInline(true);
        this.setOutput(true, 'Number');
        this.setColour(230);
        this.setTooltip(Blockly.Msg.MQTT_MESSAGE_TOOLTIP);
        this.setHelpUrl(Blockly.Msg.MQTT_CONNECT_HELPURL);
    }
};
