var etikettLog = require('./build/Release/etikettlog');

etikettLog.log = function () {
	var args = Array.prototype.slice.call(arguments, 0);
	args[0] = JSON.stringify(args[0]);
	return etikettLog.send.apply(etikettLog, args); 
};

etikettLog.alias = function () {
	var tags = Array.prototype.slice.call(arguments, 0);
	return function () {
		var args = Array.prototype.slice.call(arguments, 0);
		return etikettLog.log.apply(etikettLog, args.concat(tags)); 
	};
};

module.exports = etikettLog;
