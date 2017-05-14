#!/usr/bin/env bash
set -e

cd $TRAVIS_BUILD_DIR/docs
$HOME/doxygen/doxygen*/bin/doxygen

cd $TRAVIS_BUILD_DIR
git fetch origin gh-pages:origin/gh-pages && git checkout origin/gh-pages -b gh-pages || git checkout --orphan gh-pages
git reset
ls | grep -v 'docs' | xargs rm -rf
git checkout master docs/CNAME
mv docs/CNAME .
mv docs/html/* .
rm -rf docs
git add *
if [[ $(git status -s | grep -v "docs/CNAME" | wc -l) -eq "0" ]]; then
    exit
fi
git commit -am "Generated documents from TravisCI for build $TRAVIS_BUILD_NUMBER"
git push -q https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git gh-pages:gh-pages -f 2> /dev/null
