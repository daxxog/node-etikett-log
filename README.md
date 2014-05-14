Node Client Library for logging to Etikett
==========================================

To install:
-----------
```
$ npm install etikett-log
```

To build:
---------

```
$ node-gyp configure
$ node-gyp rebuild
```

How to use:
-----------

```
var etikett = require('etikett-log');

etikett.log({ usr: 89, name: 'Kalle Anka' }, 89, 10, 25);
```
