#!/usr/bin/php
<?php
function fuck()
{
	file_put_content("/tmp/fuck",__FUNCTION__);
}

Febr_Call("fuck");
echo "succes\n";
