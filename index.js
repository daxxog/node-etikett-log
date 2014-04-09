var etikettLog = require('./build/Release/etikettlog');

var DEBUG = 0;
var INFO = 1;
var WARNING = 3;
var ERROR = 4;

etikettLog.alias = function () {
	var tags = Array.prototype.slice.call(arguments, 0);
	return function () {
		var args = Array.prototype.slice.call(arguments, 0);
		return etikettLog.log.apply(etikettLog, args.concat(tags)); 
	};
};

etikettLog.info = function () {
	return function () {
		etikettLog.log.apply(etikettLog, Array.prototype.slice.call(arguments, 0).push(INFO)); 
	};
};

etikettLog.error = function () {
	return function () {
		etikettLog.log.apply(etikettLog, Array.prototype.slice.call(arguments, 0).push(ERROR)); 
	};
};

module.exports = etikettLog;
