# node-fastlz

[![Build Status](https://travis-ci.org/sparkypants/node-fastlz.svg?branch=master)](https://travis-ci.org/sparkypants/node-fastlz)

This is the start of some bindings to [FastLZ](http://fastlz.org/). FastLZ is an
implementation of lz77 which may not get the best compression ratio, but is
relatively CPU efficient.

## status

This library is a work in progress. I'm releasing it as 1.0.0 because it is
going into production. But it only supports synchronous compression at the
moment. We'll be fleshing out the API as needed (decompression and async) but
those will wait on us actually needing those capabilities.

These bindings have only been tested with Node.js 5.x and 6.x. If you need an
older version of node, and that version is still supported by the node core
team, patches are welcome to get it working.

## usage

`fastlz.compressSync(sourceBuffer, sourceDataLength) -> compressedBuffer`

`sourceBuffer` is the data you want compressed. `sourceDataLength` is the length
of the data starting at 0 in the `sourceBuffer`. `compressedBuffer` is a
minimally sized buffer of the compressed data.

### example

```
const fastlz = require('fastlz');

const dataToCompress = Buffer.from('this string is gunna be smaller!', 'utf8');
const compressedData = fastlz.compressSync(dataToCompress, dataToCompress.length);
```

## license

These bindings are distributed as ISC, which is compatible with the MIT license
of FastLZ. You can find both licenses in `LICENSE`.
