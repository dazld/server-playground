var net = require('net');

function doConnect(done){
	
	var client = net.connect({
		port: 3456
	}, function() { //'connect' listener
		console.log('client connected');
		client.write('ready:\r\n');
	});

	client.on('data', function(data) {
		console.log('rx: ',data.toString());
		// client.end();
	});

	client.on('error', function(err) {
		console.log('client error', err);
		done(doConnect);
	});

	client.on('end', function() {
		console.log('client disconnected');
		// done(doConnect);
	});


}

doConnect(doConnect);
