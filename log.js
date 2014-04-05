var etikett = require('./build/Release/etikettlog');

if (!etikett.log('Jack is here HAHA', 89, 90, 98, 2000, 404, 501)) {
	console.log('Could not log');
}
