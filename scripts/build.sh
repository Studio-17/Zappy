#!/bin/bash

pwd
make -C project/server/
make -C project/server/ clean
make -C project/server/ re
