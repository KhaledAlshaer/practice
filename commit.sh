#!/bin/bash


if [ $# -ne 1 ]
then
	echo "this script needs exactly one argument (commit message) please rerun the script with your message"
else
	git add .&&git commit -m "$1"&&git push
fi
