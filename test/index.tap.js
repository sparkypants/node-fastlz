'use strict';

const test = require('tap').test;
const fastlz = require('../');

test('compressSync no args', (t) => {
  t.plan(1);
  t.throws(() => {
    fastlz.compressSync();
  }, 'TypeError', 'throws error when no args');
});

test('compressSync all args', (t) => {
  t.plan(1);
  const data = 'some data to be compressed';
  const source = Buffer.from('some data to be compressed', 'utf8');
  const compressedData = fastlz.compressSync(source, data.length);
  t.type(compressedData, Buffer, 'should return a buffer');
});
