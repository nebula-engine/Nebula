#!/bin/bash

cd components/core
git add --all
git commit -m 'auto'
git push origin master
cd ../..

cd components/physx
git add --all
git commit -m 'auto'
git push origin master
cd ../..

cd components/python
git add --all
git commit -m 'auto'
git push origin master
cd ../..

cd components/final
git add --all
git commit -m 'auto'
git push origin master
cd ../..

cd components/ext
git add --all
git commit -m 'auto'
git push origin master
cd ../..


cd external/Galaxy/components/console
git add --all
git commit -m 'auto'
git push origin master
cd ../../../..

cd external/Galaxy/components/std
git add --all
git commit -m 'auto'
git push origin master
cd ../../../..

cd external/Galaxy/components/log
git add --all
git commit -m 'auto'
git push origin master
cd ../../../..

cd external/Galaxy
git add --all
git commit -m 'auto'
git push origin master
cd ../..



