// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This header is private to the ProtobolBuffers library and must NOT be
// included by any sources outside this library. The contents of this file are
// subject to change at any time without notice.

#import "UbiXGPBCodedInputStream.h"

@class UbiXGPBUnknownFieldSet;
@class UbiXGPBFieldDescriptor;

typedef struct UbiXGPBCodedInputStreamState {
  const uint8_t *bytes;
  size_t bufferSize;
  size_t bufferPos;

  // For parsing subsections of an input stream you can put a hard limit on
  // how much should be read. Normally the limit is the end of the stream,
  // but you can adjust it to anywhere, and if you hit it you will be at the
  // end of the stream, until you adjust the limit.
  size_t currentLimit;
  int32_t lastTag;
  NSUInteger recursionDepth;
} UbiXGPBCodedInputStreamState;

@interface UbiXGPBCodedInputStream () {
 @package
  struct UbiXGPBCodedInputStreamState state_;
  NSData *buffer_;
}

// Group support is deprecated, so we hide this interface from users, but
// support for older data.
- (void)readGroup:(int32_t)fieldNumber
              message:(UbiXGPBMessage *)message
    extensionRegistry:(UbiXGPBExtensionRegistry *)extensionRegistry;

// Reads a group field value from the stream and merges it into the given
// UnknownFieldSet.
- (void)readUnknownGroup:(int32_t)fieldNumber
                 message:(UbiXGPBUnknownFieldSet *)message;

// Reads a map entry.
- (void)readMapEntry:(id)mapDictionary
    extensionRegistry:(UbiXGPBExtensionRegistry *)extensionRegistry
                field:(UbiXGPBFieldDescriptor *)field
        parentMessage:(UbiXGPBMessage *)parentMessage;
@end

CF_EXTERN_C_BEGIN

int32_t UbiXGPBCodedInputStreamReadTag(UbiXGPBCodedInputStreamState *state);

double UbiXGPBCodedInputStreamReadDouble(UbiXGPBCodedInputStreamState *state);
float UbiXGPBCodedInputStreamReadFloat(UbiXGPBCodedInputStreamState *state);
uint64_t UbiXGPBCodedInputStreamReadUInt64(UbiXGPBCodedInputStreamState *state);
uint32_t UbiXGPBCodedInputStreamReadUInt32(UbiXGPBCodedInputStreamState *state);
int64_t UbiXGPBCodedInputStreamReadInt64(UbiXGPBCodedInputStreamState *state);
int32_t UbiXGPBCodedInputStreamReadInt32(UbiXGPBCodedInputStreamState *state);
uint64_t UbiXGPBCodedInputStreamReadFixed64(UbiXGPBCodedInputStreamState *state);
uint32_t UbiXGPBCodedInputStreamReadFixed32(UbiXGPBCodedInputStreamState *state);
int32_t UbiXGPBCodedInputStreamReadEnum(UbiXGPBCodedInputStreamState *state);
int32_t UbiXGPBCodedInputStreamReadSFixed32(UbiXGPBCodedInputStreamState *state);
int64_t UbiXGPBCodedInputStreamReadSFixed64(UbiXGPBCodedInputStreamState *state);
int32_t UbiXGPBCodedInputStreamReadSInt32(UbiXGPBCodedInputStreamState *state);
int64_t UbiXGPBCodedInputStreamReadSInt64(UbiXGPBCodedInputStreamState *state);
BOOL UbiXGPBCodedInputStreamReadBool(UbiXGPBCodedInputStreamState *state);
NSString *UbiXGPBCodedInputStreamReadRetainedString(UbiXGPBCodedInputStreamState *state)
    __attribute((ns_returns_retained));
NSData *UbiXGPBCodedInputStreamReadRetainedBytes(UbiXGPBCodedInputStreamState *state)
    __attribute((ns_returns_retained));
NSData *UbiXGPBCodedInputStreamReadRetainedBytesNoCopy(
    UbiXGPBCodedInputStreamState *state) __attribute((ns_returns_retained));

size_t UbiXGPBCodedInputStreamPushLimit(UbiXGPBCodedInputStreamState *state,
                                    size_t byteLimit);
void UbiXGPBCodedInputStreamPopLimit(UbiXGPBCodedInputStreamState *state,
                                 size_t oldLimit);
size_t UbiXGPBCodedInputStreamBytesUntilLimit(UbiXGPBCodedInputStreamState *state);
BOOL UbiXGPBCodedInputStreamIsAtEnd(UbiXGPBCodedInputStreamState *state);
void UbiXGPBCodedInputStreamCheckLastTagWas(UbiXGPBCodedInputStreamState *state,
                                        int32_t value);

CF_EXTERN_C_END
