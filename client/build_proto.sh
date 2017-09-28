#!/usr/bin/env bash
NANOPB="protoc-gen-nanopb=/home/randy/Arduino/libraries/nanopb/generator/protoc-gen-nanopb"
protoc --nanopb_out=. --plugin=$NANOPB ../msg.proto
