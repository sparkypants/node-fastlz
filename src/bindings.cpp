#include <iostream>
#include <nan.h>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "fastlz.h"

NAN_METHOD(CompressSync) {
  if (info.Length() == 2 && node::Buffer::HasInstance(info[0]) && info[1]->IsUint32()) {
    v8::Local<v8::Object> sourceObject = info[0]->ToObject();
    void* source = static_cast<void*>(node::Buffer::Data(sourceObject));

    uint32_t dataLength = info[1]->Uint32Value();

    // Ensure the new buffer is at least big enough to hold the compressed data
    // per the requirements by fastlz
    int destinationSize = std::max(66, static_cast<int>(std::ceil(dataLength * 1.05)));
    void* destination = std::malloc(destinationSize);

    int compressedSize = fastlz_compress(source, dataLength, destination);

    // Reallocate the buffer so it is strictly big enough.
    char* compressedData = static_cast<char*>(realloc(destination, compressedSize));

    // Turn it into a node::Buffer which takes ownership of the memory and will
    // call free() on the internal buffer we allocated when it is garbage
    // collected.
    v8::Local<v8::Object> compressedBuffer = Nan::NewBuffer(compressedData, compressedSize).ToLocalChecked();
    info.GetReturnValue().Set(compressedBuffer);
  } else {
    Nan::ThrowTypeError("usage: source buffer, source data length, destination buffer");
  }
  return;
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("compressSync").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(CompressSync)).ToLocalChecked());
}

NODE_MODULE(FastLZ, InitAll)
