#!/bin/sh

set -e

now=$(date "+%d.%m  %H:%M")

curl -XPOST "$FLIPDOT_HOST/textBig" \
  --header "Content-Type: application/json" \
    -d "{ text: '$now' }"
    