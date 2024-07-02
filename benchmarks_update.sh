#!/bin/bash
set -xe

git fetch origin
git fetch --tags
git checkout master
git pull origin master
git checkout benchmarks -- .asv/ 2>/dev/null || echo ".asv/ doesn't exist in the benchmarks branch yet."

pip install '.[bench]'

asv machine --yes
for ref in $(git tag) $(git rev-list 1.7.0..HEAD); do
    asv run --skip-existing --show-stderr $ref^
done

asv show

git checkout benchmarks
git add -f .asv/
git commit -m "Updated benchmarks"
git push origin benchmarks
git checkout master
