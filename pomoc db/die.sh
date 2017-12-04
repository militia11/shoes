#!/bin/bash

function die {
	echo -e "\033[0;31m!!!!!!!!!"
	echo "! ERROR !"
	echo -e "!!!!!!!!!\033[0m"
	echo "There are some errors. Installation process wasn't successfull."
	exit 1
}
