#!/usr/bin/env bash
NANOPB="protoc-gen-nanopb=/home/randy/Arduino/libraries/nanopb/generator/protoc-gen-nanopb"
PROTO_PATH="/home/randy/alarm/"
protoc --nanopb_out=door/ --plugin=$NANOPB --proto_path=$PROTO_PATH /home/randy/alarm/msg.proto
