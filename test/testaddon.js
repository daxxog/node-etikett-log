var etikett = require('../build/Release/etikettlog');

if (etikett.log('Testing', 89)) {
	console.log('OK');
} else {
	console.log('NOT OK');
}
