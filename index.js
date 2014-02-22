var net = require('net');
var maxHeap = 0;
var maxRss = 0;
function doConnect(done){
	
	var client = net.connect({
		port: 3456
	}, function() { //'connect' listener
		// console.log('client connected');
		// client.write('ready:\r\n');
	});

	client.on('data', function(data) {
		// console.log('rx: ',data.toString());
		// client.end();
	});

	client.on('error', function(err) {
		// console.log('client error', err);
		// done(doConnect);
	});

	client.on('end', function() {
		// console.log('client disconnected');
		var usage = process.memoryUsage();
		if (usage.heapUsed > maxHeap) {
			maxHeap = usage.heapUsed;
			console.log(maxHeap);
		};
		var cb = done.bind(null, doConnect);
		process.nextTick(cb);
	});


}

doConnect(doConnect);
