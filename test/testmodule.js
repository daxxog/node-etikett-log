var etikett = require('../index.js');

var logs = [
	etikett.alias(1001, 1002, 1003),
	etikett.alias(1006, 1002, 1003, 654),
	etikett.alias(404, 500, 5000, 705),
	etikett.alias(1002, 404, 1000),
	etikett.alias(1002, 404, 1000, 800, 447),
	etikett.alias(1052, 402, 1500, 850, 139),
	etikett.alias(1022, 502),
	etikett.alias(800, 447),
	etikett.alias(1052, 402, 139),
	etikett.alias(1022, 502, 5504, 321)
];

var strings = [
	'Database error: invalid column',
	'User 6654 created new item',
	'URL not found on server',
	'Requested new log',
	'404 not found',
	'503 forbidden',
	'Item not found (item_id 4321)',
	'Too many arguments specified',
	'File not found /dev/null',
	'Server not started'
];

var randomLog = function () {
	var l = logs[Math.floor((Math.random()*10))];
	var s = strings[Math.floor((Math.random()*10))];
	l(s, 89);
};

var i = 0;
while (i++ < 10000) {
	//var t = Math.floor((Math.random()*10));
	//setTimeout(randomLog, t);
	randomLog();
}
