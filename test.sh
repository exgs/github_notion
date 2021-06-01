#!/bin/bash
sh ./tesh2.sh

if [ "$?" -ne "0" ]; then
  echo "Sorry, we had a problem there!"
fi