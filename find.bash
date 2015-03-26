#!/bin/bash
find .. -name "*.hpp" | xargs -i{} grep "$1" {} -Hn
find .. -name "*.cpp" | xargs -i{} grep "$1" {} -Hn

