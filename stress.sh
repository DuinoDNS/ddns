#!/bin/bash -u

HOST="@$1"
PORT="$2"

dig $HOST -p $PORT testab.de bla.de google.com test.de a.de &
dig $HOST -p $PORT testab.de bla.de google.com test.de a.de &
dig $HOST -p $PORT testab.de bla.de google.com test.de a.de &
