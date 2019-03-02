module.exports = function(RED) {
    function CelsiusToFahrenheit(config) {
        RED.nodes.createNode(this,config);
        var node = this;
        node.on('input', function(msg) {
            msg.payload = (msg.payload * (9 / 5)) + 32;
            node.send(msg);
        });
    }
    RED.nodes.registerType("celsius-to-fahrenheit", CelsiusToFahrenheit);
}
