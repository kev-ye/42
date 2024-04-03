ifconfig | grep "ether" | sed "s/ether //" | cut -f2 | sed "s/ //"
