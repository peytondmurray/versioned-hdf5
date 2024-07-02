#!/bin/bash
set -xe

git fetch origin
git fetch origin --tags
git checkout master
git pull origin master
git checkout benchmarks -- .asv/ 2>/dev/null || echo ".asv/ doesn't exist in the benchmarks branch yet."

pip install '.[bench]'

asv machine --yes

echo $(git tag) $(git rev-list 1.7.0..HEAD) | sed -e 's/\s\+/\n/g' > commits.txt
asv run --skip-existing --show-stderr HASHFILE:commits.txt
asv show

git checkout benchmarks
git add -f .asv/
git commit -m "Updated benchmarks"
git push origin benchmarks
git checkout master
