#!/bin/sh
make && make install && sudo apachectl restart

php t.php
