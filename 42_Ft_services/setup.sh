# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 09:58:40 by kaye              #+#    #+#              #
#    Updated: 2021/05/12 19:59:51 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## COMMAND TO RUN SCRIPT
# ./setup.sh start/restart	: start
# ./setup.sh services		: install services
# ./setup.sh dashboard		: install dashboard
# ./setup.sh delsvc			: uninstall services
# ./setup.sh delete			: clean minikube
# ./setup.sh clean_all		: clean all files about ft_services

## ANSI COLOR CODES
BLACK="\033[1;30m"
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
CYAN="\033[1;36m"
NONE="\033[0m"
CLR_SCREEN="\033[2J\033[H"

# generate by the command "figlet"
echo "$CLR_SCREEN$CYAN\
 _____ _                           _
|  ___| |_     ___  ___ _ ____   _(_) ___ ___  ___
| |_  | __|   / __|/ _ \ '__\ \ / / |/ __/ _ \/ __|
|  _| | |_    \__ \  __/ |   \ V /| | (_|  __/\__ \\
|_|    \__|___|___/\___|_|    \_/ |_|\___\___||___/
         |_____|
$NONE"
echo "🖥  OS - "$PURPLE"$(uname)"$NONE" -"

### FUNCTION

## INSTALLATION OF KUBERNETES & MINIKUBE & DOCKER - LINUX
install_minikube_linux()
{
	## CONFIG FOR LINUX
	echo ""$RED"\n(If you are in the VM, please check if you are running with 2 cores)"$NONE""
	cat /etc/group | grep "docker" | grep $(whoami) 2>/dev/null 1>&2
	if [ $? -ne 0 ] ; then
		# run docker without sudo
		echo ""$RED"❗️ Please do"$NONE" "$YELLOW"\"sudo usermod -aG docker $(whoami); newgrp docker\""$NONE""
		exit
	fi

	# make sure docker is running
	echo ""$GREEN"\n🐳 restart docker ..."$NONE""
	if ! service docker restart 2>/dev/null ; then
		echo ""$RED"\n❗️ Some error during docker lauch, please relauch the script ..."$NONE"\n"
		exit
	fi

	# clean old minikube
	echo ""$CYAN"\n♻️  clean old minikube if exist ..."$NONE""
	minikube delete
}

## INSTALLATION OF KUBERNETES & MINIKUBE & DOCKER - MACOS
install_minikube_macos()
{
	# installation of brew
	if ! which brew 2>/dev/null 1>&2 ; then
		echo ""$GREEN"\n🍺 brew installing ..."$NONE""
		rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
	fi

	# installation of minikube (kubernetes-cli will installed during installation of minikube)
	if ! which minikube 2>/dev/null 1>&2 ; then
		echo ""$GREEN"\n🛳  minikube installing ..."$NONE""
		brew install minikube
	fi

	# check if /goinfre folder exist (at 42)
	if [ -d /goinfre ] ; then

		if ! cat $HOME/.zshrc | grep "export MINIKUBE_HOME=/goinfre/$USER" 2>/dev/null 1>&2 ; then

			# linking minikube folder to goinfre
			echo ""$GREEN"\n↔️  linking minikube folder to /goinfre/\$USER ..."$NONE""
			echo "export MINIKUBE_HOME=/goinfre/$USER" >> $HOME/.zshrc
		fi

			# update config
			echo ""$GREEN"\n⬆️  updating $HOME/.zshrc config ..."$NONE""
			source $HOME/.zshrc 2>/dev/null 1>&2

			# clean old minikube
			echo ""$CYAN"\n♻️  clean old minikube if exist ..."$NONE""
			minikube delete
	else
	
		# clean old minikube
		echo ""$CYAN"\n♻️  clean old minikube if exist ..."$NONE""
		minikube delete
	fi
}

## INSTALLATION OF METALLB
install_metallb()
{
	## Preparation

	# see what changes would be made, returns nonzero returncode if different
	kubectl get configmap kube-proxy -n kube-system -o yaml | \
	sed -e "s/strictARP: false/strictARP: true/" | \
	kubectl diff -f - -n kube-system

	# actually apply the changes, returns nonzero returncode on errors only
	kubectl get configmap kube-proxy -n kube-system -o yaml | \
	sed -e "s/strictARP: false/strictARP: true/" | \
	kubectl apply -f - -n kube-system

	## Installation By Manifest
	kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.6/manifests/namespace.yaml
	kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.6/manifests/metallb.yaml

	# On first install only
	kubectl create secret generic -n metallb-system memberlist --from-literal=secretkey="$(openssl rand -base64 128)"

	# applicate the yaml configuration
	if [ $(uname) = "Linux" ] ; then
		kubectl apply -f ./srcs/yaml/metallb-configmap_linux.yaml
	elif [ $(uname) = "Darwin" ] ; then
		kubectl apply -f ./srcs/yaml/metallb-configmap_macos.yaml
	fi
}

install_dashboard()
{
	# install kubernetes dashboard
	kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.2.0/aio/deploy/recommended.yaml 2>/dev/null 1>&2

	# create admin token
	if ! kubectl -n kube-system describe secret | grep admin-token 2>/dev/null 1>&2 ; then
		echo ""$GREEN"\n🛠  create admin token ..."$NONE"\n"
		kubectl create -f ./srcs/yaml/admin-token.yaml
		sleep 5
	fi

	# show token
	echo ""$GREEN$CLR_SCREEN"🛠  Plead copy the \"Token\" code to connect dashboard"$NONE"\n"
	kubectl -n kube-system describe secret $(kubectl -n kube-system get secret | awk '/^admin-token-/{print $1}') | awk '$1=="token:"{print $2}'

	# open dashboard
	echo ""$GREEN"\n🛠  open the dashboard ..."$NONE"\n"
	if [ $(uname) = "Linux" ] ; then
		xdg-open http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/
	elif [ $(uname) = "Darwin" ] ; then
		open http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/
	fi

	# starting dashboard proxy
	echo ""$GREEN"🛠  Please refresh the dashboard page when you see \"Starting to serve on [...] ...\""$NONE"\n"
	kubectl proxy

	# TIPS 1 : if the dashboard page shows nothing, try add "login" like [...]/proxy/#/login or just change browser
	# TIPS 2 : if you can't log in to the dashboard, try wipe off "login" like [...]/proxy/#/
}

## INSTALLATION OF SERVICES
setup_services()
{
	# use minikube docker, whitout this, minikube can't found images built locally
	eval $(minikube docker-env)

	echo ""
	for service in 'influxdb' 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps' 'grafana' 
	do
		echo "🛠  Building $GREEN$service$NONE image ..."
		docker build -t svc_$service ./srcs/config/$service 2>/dev/null 1>&2
		if [ $? -ne 0 ] ; then
			echo ""$RED"Error during building image !$NONE"
			exit
		fi
	done

	echo ""
	for service in 'influxdb' 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps' 'grafana' 
	do
		echo "🛠  Applicating $GREEN$service$NONE service ..."
		kubectl apply -f srcs/config/$service/$service-deployment.yaml 2>/dev/null 1>&2
		if [ $? -ne 0 ] ; then
			echo ""$RED"Error during applicating service !$NONE"
			exit
		fi
	done
}

## FT_SERVICES
ft_services()
{
	if [ $(uname) = "Linux" ] ; then

		# install minikube
		install_minikube_linux

		# run minikube
		echo ""$CYAN"\n🛳  minikube running ..."$NONE""
		minikube start --vm-driver=docker --memory=2g --cpus=2 --extra-config=apiserver.service-node-port-range=1-65535

	elif [ $(uname) = "Darwin" ] ; then

		# install minikube
		install_minikube_macos

		# run minikube
		echo ""$GREEN"\n🛳  minikube running ..."$NONE""
		minikube start --vm-driver=virtualbox --memory=2g --cpus=2 --extra-config=apiserver.service-node-port-range=1-65535

		if [ $? -ne 0 ] ; then
			echo ""$RED"❗️  FAILED ! Try the command \"minikube delete\" and relaunch the script."$NONE""
			exit
		fi
	fi

	# use minikube docker, whitout this, minikube can't found images built locally
	eval $(minikube docker-env)
	sleep 5

	# check if metallb exist
	kubectl get pods -n metallb-system 2>/dev/null 1>&2 | grep "controller" | grep "Running" 2>/dev/null 1>&2
	if [ $? -ne 0 ] ; then

		# install metallb with manifest
		echo ""$GREEN"\n🛠  install & configure metallb ..."$NONE""
		install_metallb 2>/dev/null 1>&2
	fi

	# create secret for password
	echo ""$GREEN"\n🛠  create secret config ..."$NONE""
	kubectl create -f ./srcs/yaml/secret.yaml

	# setup services
	setup_services

	# installation done
	echo ""$YELLOW"\n✅ INSTALLATION DONE ✅\n"$NONE""

	# set dashboard
	install_dashboard

	# reopen a new zsh because configuration of source ~/.zshrc isn't applicate on old zsh.
	# zsh
}

### SCRIPT

## FT_SERVICE START
if [ $# -lt 1 ] || [ $1 = 'start' ] || [ $1 = 'restart' ] ; then

	ft_services

## INSTALL SERVICES
elif [ $# -eq 1 ] && [ $1 = 'services' ] ; then

	setup_services

## INSTALL DASHBOARD
elif [ $# -eq 1 ] && [ $1 = 'dashboard' ] ; then

	install_dashboard

## UNINSTALL SERVICES
elif [ $# -eq 1 ] && [ $1 = 'delsvc' ] ; then

	echo ""
	for service in 'influxdb' 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps' 'grafana' 
	# for service in 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps'
	do
		if kubectl get svc | grep $service 2>/dev/null 1>&2 ; then
			echo ""$CYAN"♻️  Deleting $service service ...$NONE"
			kubectl delete -f srcs/config/$service/$service-deployment.yaml 2>/dev/null 1>&2
		fi
	done

	echo ""
	for service in 'influxdb' 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps' 'grafana'
	# for service in 'nginx' 'mysql' 'phpmyadmin' 'wordpress' 'ftps'
	do
		if docker image ls | grep $service 2>/dev/null 1>&2 ; then
			echo ""$CYAN"♻️  Deleting $service image ...$NONE"
			docker image rm svc_$service 2>/dev/null 1>&2
		fi
	done

## DELETE SERVICES & MINIKUBE
elif [ $# -eq 1 ] && [ $1 = 'delete' ] ; then

	# delete minikube
	if which minikube 2>/dev/null 1>&2 ; then
		echo ""$CYAN"\n♻️  clean minikube ..."$NONE""
		minikube delete
	fi

## CLEAN ALL FILES ABOUT FT_SERVICES
elif [ $# -eq 1 ] && [ $1 = 'clean_all' ] ; then

	# delete minikube
	if which minikube 2>/dev/null 1>&2 ; then
		echo ""$CYAN"\n♻️  clean minikube ..."$NONE""
		minikube delete
	fi

	# delete minikube folder
	echo ""$CYAN"\n♻️  clean minikube folder ..."$NONE""
	rm -rf $HOME/.kube
	rm -rf $HOME/.minikube

	# delete minikube folder in goinfre (at 42)
	if [ $(uname) = "Darwin" ] && [ -d /goinfre ] ; then

		echo ""$CYAN"\n♻️  clean minikube folder in goinfre (at 42)..."$NONE""
		unset MINIKUBE_HOME
		rm -rf /goinfre/$USER/.minikube
	fi

	# delete ssh
	echo ""$CYAN"\n♻️  clean ssh ..."$NONE""
	rm -rf $HOME/.ssh/known_hosts
fi
