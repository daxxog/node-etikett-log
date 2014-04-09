var etikett = require('../index.js');

if (etikett.log('Testing', 89)) {
	console.log('OK');
} else {
	console.log('NOT OK');
}

var log = etikett.alias(1001, 1002, 1003);
if (log('Testing', 89, 90)) {
	console.log('OK');
} else {
	console.log('NOT OK');
}
