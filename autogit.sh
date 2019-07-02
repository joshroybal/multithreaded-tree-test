#!/bin/sh
set -v
git init
git add .
git remote add origin git@github.com:joshroybal/multithreaded-tree-test
git pull origin master
git commit . -m "upload source code"
git push origin master
