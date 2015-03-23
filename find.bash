#!/bin/bash
find .. -name "*.cpp" | xargs -i{} grep "$1" {} -Hn
