var etikett = require('../index.js');

if (etikett.log({ id: 89, cost: 2552 }, 89, 404, 300)) {
	console.log('OK');
} else {
	console.log('NOT OK');
}
