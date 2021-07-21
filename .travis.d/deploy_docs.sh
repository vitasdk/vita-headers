#!/usr/bin/env bash
set -e

cd $TRAVIS_BUILD_DIR/docs
doxygen
cp search.js html/search/search.js
echo "<script id=\"searchdata\" type=\"text/xmldata\">" >> html/search.html
cat searchdata.xml >> html/search.html
echo "</script>" >> html/search.html